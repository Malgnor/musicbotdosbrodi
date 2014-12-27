/*
* TeamSpeak 3 musicbot Plugin
*
* Copyright (c) 2014-2014 Brodi's Dev
*/

#ifdef _WIN32
#pragma warning (disable : 4100)  /* Disable Unreferenced parameter warning */
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "public_errors.h"
#include "public_errors_rare.h"
#include "public_definitions.h"
#include "public_rare_definitions.h"
#include "ts3_functions.h"
#include "plugin.h"

#include "global.h"
#include "dialog.h"

using namespace std;
using namespace Global;

#ifdef _WIN32
#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
#define snprintf sprintf_s
#else
#define _strcpy(dest, destSize, src) { strncpy(dest, src, destSize-1); (dest)[destSize-1] = '\0'; }
#endif

#define PLUGIN_API_VERSION 20

#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

static char* pluginID = NULL;

static bool botEnabled = false;
static string linkAtual = "";

#ifdef _WIN32
/* Helper function to convert wchar_T to Utf-8 encoded strings on Windows */
static int wcharToUtf8(const wchar_t* str, char** result) {
	int outlen = WideCharToMultiByte(CP_UTF8, 0, str, -1, 0, 0, 0, 0);
	*result = (char*)malloc(outlen);
	if(WideCharToMultiByte(CP_UTF8, 0, str, -1, *result, outlen, 0, 0) == 0) {
		*result = NULL;
		return -1;
	}
	return 0;
}
#endif

const char* ts3plugin_name() {
#ifdef _WIN32
	/* TeamSpeak expects UTF-8 encoded characters. Following demonstrates a possibility how to convert UTF-16 wchar_t into UTF-8. */
	static char* result = NULL;  /* Static variable so it's allocated only once */
	if(!result) {
		const wchar_t* name = L"Musicbot dos Brodi";
		if(wcharToUtf8(name, &result) == -1) {
			result = "Musicbot dos Brodi";
		}
	}
	return result;
#else
	return "Musicbot dos Brodi";
#endif
}

const char* ts3plugin_version() {
    return "0.3";
}

int ts3plugin_apiVersion() {
	return PLUGIN_API_VERSION;
}

const char* ts3plugin_author() {
    return "Brodi\'s Dev";
}

const char* ts3plugin_description() {
    return "";
}

void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
    ts3Functions = funcs;
}

int ts3plugin_init() {
    printf("PLUGIN: init\n");
	
	loadSettings();
    return 0;  /* 0 = success, 1 = failure, -2 = failure but client will not show a "failed to load" warning */
	/* -2 is a very special case and should only be used if a plugin displays a dialog (e.g. overlay) asking the user to disable
	 * the plugin again, avoiding the show another dialog by the client telling the user the plugin failed to load.
	 * For normal case, if a plugin really failed to load because of an error, the correct return value is 1. */
}

void ts3plugin_shutdown() {

    printf("PLUGIN: shutdown\n");

	if(pluginID) {
		free(pluginID);
		pluginID = NULL;
	}
}

int ts3plugin_offersConfigure() {
	printf("PLUGIN: offersConfigure\n");
	/*
	* Return values:
	* PLUGIN_OFFERS_NO_CONFIGURE         - Plugin does not implement ts3plugin_configure
	* PLUGIN_OFFERS_CONFIGURE_NEW_THREAD - Plugin does implement ts3plugin_configure and requests to run this function in an own thread
	* PLUGIN_OFFERS_CONFIGURE_QT_THREAD  - Plugin does implement ts3plugin_configure and requests to run this function in the Qt GUI thread
	*/
	return PLUGIN_OFFERS_CONFIGURE_QT_THREAD;  /* In this case ts3plugin_configure does not need to be implemented */
}

/* Plugin might offer a configuration window. If ts3plugin_offersConfigure returns 0, this function does not need to be implemented. */
void ts3plugin_configure(void* handle, void* qParentWidget) {
	printf("PLUGIN: configure\n");
	Dialog oi;
	oi.SetupUi();
	oi.exec();

}

void ts3plugin_registerPluginID(const char* id) {
	const size_t sz = strlen(id) + 1;
	pluginID = (char*)malloc(sz * sizeof(char));
	_strcpy(pluginID, sz, id);  /* The id buffer will invalidate after exiting this function */
	printf("PLUGIN: registerPluginID: %s\n", pluginID);
}

const char* ts3plugin_commandKeyword() {
	return "musicbot";
}

/* Plugin processes console command. Return 0 if plugin handled the command, 1 if not handled. */
int ts3plugin_processCommand(uint64 serverConnectionHandlerID, const char* command) {

	enum { CMD_NONE = 0, CMD_ENABLE, CMD_DISABLE } cmd = CMD_NONE;
	
	printf("PLUGIN: process command: '%s'\n", command);

	if(!strcmp(command, "enable")) {
		cmd = CMD_ENABLE;
	} else if (!strcmp(command, "disable")) {
		cmd = CMD_DISABLE;
	}

	switch(cmd) {
		case CMD_NONE:
			return 1;
		case CMD_ENABLE:
		{
			anyID myID;
			if (ts3Functions.getClientID(serverConnectionHandlerID, &myID) != ERROR_ok) {
				ts3Functions.logMessage("Error querying own client id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
				return 0;
			}

			uint64 myChannelID;

			if (ts3Functions.getChannelOfClient(serverConnectionHandlerID, myID, &myChannelID) != ERROR_ok) {
				ts3Functions.logMessage("Error querying own client channel id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
				return 0;
			}

			if (vlcPath == ""){
							   
				if (ts3Functions.requestSendChannelTextMsg(serverConnectionHandlerID, "O path do VLC ainda nao foi configurado!", myChannelID, NULL) != ERROR_ok){
					ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
				}

				break;
			}
			botEnabled = true;

			if (ts3Functions.requestSendChannelTextMsg(serverConnectionHandlerID, "O bot agora esta ativado!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
			}
			break;
		}

		case CMD_DISABLE:
		{
			botEnabled = false;
			anyID myID;
			if (ts3Functions.getClientID(serverConnectionHandlerID, &myID) != ERROR_ok) {
				ts3Functions.logMessage("Error querying own client id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
				return 0;
			}

			uint64 myChannelID;

			if (ts3Functions.getChannelOfClient(serverConnectionHandlerID, myID, &myChannelID) != ERROR_ok) {
				ts3Functions.logMessage("Error querying own client channel id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
				return 0;
			}

			if (ts3Functions.requestSendChannelTextMsg(serverConnectionHandlerID, "O bot agora esta desativado!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
			}
			break;
		}

	return 0;  /* Plugin handled command */
}

void ts3plugin_freeMemory(void* data) {
	free(data);
}

/* Client changed current server connection handler */
void ts3plugin_currentServerConnectionChanged(uint64 serverConnectionHandlerID) {
	printf("PLUGIN: currentServerConnectionChanged %llu (%llu)\n", (long long unsigned int)serverConnectionHandlerID, (long long unsigned int)ts3Functions.getCurrentServerConnectionHandlerID());
}

int ts3plugin_onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message, int ffIgnored) {
    printf("PLUGIN: onTextMessageEvent %llu %d %d %s %s %d\n", (long long unsigned int)serverConnectionHandlerID, targetMode, fromID, fromName, message, ffIgnored);

	if(ffIgnored) {
		return 0; /* Client will ignore the message anyways, so return value here doesn't matter */
	}

	anyID myID;
	if (ts3Functions.getClientID(serverConnectionHandlerID, &myID) != ERROR_ok) {
		ts3Functions.logMessage("Error querying own client id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		return 0;
	}

	uint64 myChannelID;
	uint64 fromChannelID;

	if (ts3Functions.getChannelOfClient(serverConnectionHandlerID, myID, &myChannelID) != ERROR_ok) {
		ts3Functions.logMessage("Error querying own client channel id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		return 0;
	}
	if (ts3Functions.getChannelOfClient(serverConnectionHandlerID, fromID, &fromChannelID) != ERROR_ok) {
		ts3Functions.logMessage("Error querying own client channel id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		return 0;
	}

	if (myChannelID != fromChannelID || myID == fromID)
		return 0;

	if (!botEnabled){
		if (ts3Functions.requestSendChannelTextMsg(serverConnectionHandlerID, "Atualmente estou desativado!", myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		}
		return 0;
	}

	char buf[COMMAND_BUFSIZE];
	char* s, *param = NULL;
	int i = 0;
	enum {CMD_NONE, CMD_VLC, CMD_ATUAL, CMD_AJUDA} cmd = CMD_NONE;

#ifdef _WIN32
	char* context = NULL;
#endif

	strcpy_s(buf, COMMAND_BUFSIZE, message);
#ifdef _WIN32
	s = strtok_s(buf, " ", &context);
#else
	s = strtok(buf, " ");
#endif

	while (s != NULL){
		if (i == 0){
			if (!strcmp(s, "!vlc")){
				cmd = CMD_VLC;
			} else if (!strcmp(s, "!atual")){
				cmd = CMD_ATUAL;
			} else if (!strcmp(s, "!ajuda")){
				cmd = CMD_AJUDA;
			}
		} else
			param = s;

#ifdef _WIN32
		s = strtok_s(NULL, " ", &context);
#else
		s = strtok(NULL, " ");
#endif
		i++;
	}
	
	string msg, newParam, atual, url;
	switch (cmd)
	{
	case CMD_NONE:

		if (ts3Functions.requestSendChannelTextMsg(serverConnectionHandlerID, "Comando invalido!", myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		}

		break;
	case CMD_VLC:

		if (!param){
			if (ts3Functions.requestSendChannelTextMsg(serverConnectionHandlerID, "Faltou parametro!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
			}
			return 0;
		}

		newParam = "start \"\" /b ";
		newParam += vlcPath;
		newParam += " ";
		if (!strncmp(param, "[URL]", 5))
		{
			url = param;
			url.erase(0, 5);
			url.erase(url.end() - 6, url.end());
			newParam += url;

		} else {
			if (ts3Functions.requestSendChannelTextMsg(serverConnectionHandlerID, "Parametro invalido!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
			}
			return 0;
		}

		system(newParam.c_str());


		atual = "Tocando: ";
		linkAtual = param;
		atual += linkAtual;
		
		if (ts3Functions.requestSendChannelTextMsg(serverConnectionHandlerID, atual.c_str(), myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		}

		break;
	case CMD_ATUAL:
		if (linkAtual == "")
		{
			atual = "Nada tocando no momento.";
		}
		else
		{
			atual = "Tocando: ";
			atual += linkAtual;
		}

		if (ts3Functions.requestSendChannelTextMsg(serverConnectionHandlerID, atual.c_str(), myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		}

		break;
	case CMD_AJUDA:
		msg = "Bem-Vindo ao meu canal de musica!\n";
		if (!botEnabled){
			msg += "Atualmente estou desativado.\n";
			msg += "Entre em contato com algum admin para mais info.";
		} else {
			msg += "Comandos disponiveis: \n";
			msg += "!vlc link - Coloca o link na playlist\n";
			msg += "!atual - Mostra o link atual\n";
			msg += "!ajuda - Mostra essa mensagem novamente";
		}
		if (ts3Functions.requestSendPrivateTextMsg(serverConnectionHandlerID, msg.c_str(), fromID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		}
		break;
	}
	
    return 0;  /* 0 = handle normally, 1 = client will ignore the text message */
}

void ts3plugin_onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage) {
	
	anyID myID;
	if (ts3Functions.getClientID(serverConnectionHandlerID, &myID) != ERROR_ok) {
		ts3Functions.logMessage("Error querying own client id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		return;
	}

	uint64 myChannelID;

	if (ts3Functions.getChannelOfClient(serverConnectionHandlerID, myID, &myChannelID) != ERROR_ok) {
		ts3Functions.logMessage("Error querying own client channel id", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
		return;
	}
	if (myChannelID != newChannelID){
		return;
	}

	string msg = "Bem-Vindo ao meu canal de musica!\n";
	if (!botEnabled){
		msg += "Atualmente estou desativado.\n";
		msg += "Entre em contato com algum admin para mais info.";
	} else {
		msg += "Comandos disponiveis: \n";
		msg += "!vlc link - Coloca o link na playlist\n";
		msg += "!atual - Mostra o link atual\n";
		msg += "!ajuda - Mostra essa mensagem novamente";
	}

	if (ts3Functions.requestSendPrivateTextMsg(serverConnectionHandlerID, msg.c_str(), clientID, NULL) != ERROR_ok){
		ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", serverConnectionHandlerID);
	}

}