/*
* TeamSpeak 3 musicbot Plugin
*
* Copyright (c) 2014-2014 Brodi's Dev
*/

#ifdef _WIN32
#pragma warning (disable : 4100)  /* Disable Unreferenced parameter warning */
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "public_errors.h"
#include "public_errors_rare.h"
#include "public_definitions.h"
#include "public_rare_definitions.h"
#include "ts3_functions.h"
#include "plugin.h"

#include "global.h"
#include "settingsdialog.h"
#include <sstream>

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

const char* ts3plugin_name() {
	return "Musicbot dos Brodi";
}

const char* ts3plugin_version() {
    return "0.6.4";
}

int ts3plugin_apiVersion() {
	return PLUGIN_API_VERSION;
}

const char* ts3plugin_author() {
    return "Brodi\'s Dev";
}

const char* ts3plugin_description() {
    return "This is a musicbot plugin, it has commands to add music from youtube to playlist, change music, pause and many other functions.";
}

void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
    ts3Functions = funcs;
}

int ts3plugin_init() {
    printf("PLUGIN: init\n");

	generateLocaleStrings();

	uint64 serverConnectionHandlerID = ts3Functions.getCurrentServerConnectionHandlerID();
	if (serverConnectionHandlerID != 0) {
		musicbot.setSchID(serverConnectionHandlerID);
	}

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

	return PLUGIN_OFFERS_CONFIGURE_QT_THREAD;
}

void ts3plugin_configure(void* handle, void* qParentWidget) {
	printf("PLUGIN: configure\n");
	SettingsDialog settings;
	settings.SetupUi();
	settings.exec();

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

	printf("PLUGIN: process command: '%s'\n", command);

	return musicbot.processCommand(command);;  /* Plugin handled command */
}

void ts3plugin_freeMemory(void* data) {
	free(data);
}

/* Client changed current server connection handler */
void ts3plugin_currentServerConnectionChanged(uint64 serverConnectionHandlerID) {
	printf("PLUGIN: currentServerConnectionChanged %llu (%llu)\n", (long long unsigned int)serverConnectionHandlerID, (long long unsigned int)ts3Functions.getCurrentServerConnectionHandlerID());
	musicbot.setSchID(serverConnectionHandlerID);
	stringstream a;
	a << "oldServerConnectionHandlerID: " << serverConnectionHandlerID << endl;
	a << "newServerConnectionHandlerID: " << ts3Functions.getCurrentServerConnectionHandlerID() << endl;
	ts3Functions.printMessageToCurrentTab(a.str().c_str());
}

void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber) {
	switch (newStatus) {
	case STATUS_DISCONNECTED: {
		musicbot.setSchID(0);
		stringstream a;
		a << "oldServerConnectionHandlerID: " << serverConnectionHandlerID << endl;
		a << "newServerConnectionHandlerID: " << ts3Functions.getCurrentServerConnectionHandlerID() << endl;
		ts3Functions.printMessageToCurrentTab(a.str().c_str());
		break;
	}
	case STATUS_CONNECTION_ESTABLISHED:
		musicbot.setSchID(serverConnectionHandlerID);
		break;
	}
}

int ts3plugin_onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message, int ffIgnored) {
    printf("PLUGIN: onTextMessageEvent %llu %d %d %s %s %d\n", (long long unsigned int)serverConnectionHandlerID, targetMode, fromID, fromName, message, ffIgnored);

	if (ffIgnored) {
		return 0; /* Client will ignore the message anyways, so return value here doesn't matter */
	}
	
	return musicbot.onTextMessage(fromID, message);;  /* 0 = handle normally, 1 = client will ignore the text message */
}

void ts3plugin_onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage) {
	
	musicbot.onClientMove(clientID, newChannelID);

}