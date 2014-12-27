#include "musicbot.h"
#include "global.h"

#include <QtCore\qstring.h>

using namespace std;
using namespace Global;

MusicBot::MusicBot() : enabled(false), vlcPath(""), myID(0), myChannelID(0), schID(0)
{}

int MusicBot::processCommand(string command){
	if (myID == 0){
		if (!setMyID())
			return 0;
	}

	if (command == "ativar"){
		if (enable()){
			if (ts3Functions.requestSendChannelTextMsg(schID, "O bot agora est\303\241 ativado!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}

		if (ts3Functions.requestSendChannelTextMsg(schID, "O bot n\305\241o foi ativado!", myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
		return 0;
	} else if (command == "desativar"){
		if (disable()){
			if (ts3Functions.requestSendChannelTextMsg(schID, "O bot agora est\303\241 desativado!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}

		if (ts3Functions.requestSendChannelTextMsg(schID, "O bot n\305\241o foi desativado!", myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
		return 0;
	}

	return 0;
}

int MusicBot::onTextMessage(anyID fromID, string message){
	if (myID == 0){
		if (!setMyID())
			return 0;
	}

	if (!enabled) return 0;

	uint64 fromChannelID;

	if (ts3Functions.getChannelOfClient(schID, fromID, &fromChannelID) != ERROR_ok) {
		ts3Functions.logMessage("Error querying own client channel id", LogLevel_ERROR, "Plugin", schID);
		return 0;
	}

	if (myID == fromID || fromChannelID != myChannelID || message[0] != '!')
		return 0;

	if (message.find("!youtube") != -1){
		if (message.length() <= 10){
			if (ts3Functions.requestSendChannelTextMsg(schID, "Faltou par\303\242metro!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}

		string param = message;
		param.erase(0, 9);

		if (param.find("[URL]") != -1){

			string link = param;

			param.erase(0, 5);
			param.erase(param.end() - 6, param.end());

			string cmd = "start \"\" /b ";
			cmd += vlcPath;
			cmd += " ";
			cmd += param;

			system(cmd.c_str());

			string atual = link;
			atual += " foi adicionado na playlist.";
			
			if (ts3Functions.requestSendChannelTextMsg(schID, atual.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}

			return 0;
		} else {
			if (ts3Functions.requestSendChannelTextMsg(schID, "Par\303\242metro inv\303\241lido!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
	} else if (message.find("!ajuda") != -1){
		string msg = "Bem-Vindo ao meu canal de m\303\272sica!\n";
		if (!enabled){
			msg += "Atualmente estou desativado.\n";
			msg += "Entre em contato com algum admin para mais info.";
		} else {
			msg += "Comandos disponiveis: \n";
			msg += "!youtube link - Coloca o link na playlist\n";
			msg += "!atual - Mostra a m\303\272sica atual\n";
			msg += "!ajuda - Mostra essa mensagem novamente";
		}
		if (ts3Functions.requestSendPrivateTextMsg(schID, msg.c_str(), fromID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
		return 0;
	} else if (message.find("!atual") != -1){
		if (ts3Functions.requestSendChannelTextMsg(schID, "Comando desativado no momento!", myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
		return 0;
	}

	return 0;
}

void MusicBot::onClientMove(anyID clientID, uint64 toChannel){
	if (myID == 0){
		if (!setMyID())
			return;
	}

	if (myChannelID != toChannel)
		return;

	string msg = "Bem-Vindo ao meu canal de m\303\272sica!\n";
	if (!enabled){
		msg += "Atualmente estou desativado.\n";
		msg += "Entre em contato com algum admin para mais info.";
	} else {
		msg += "Comandos disponiveis: \n";
		msg += "!youtube link - Coloca o link na playlist\n";
		msg += "!atual - Mostra a m\303\272sica atual\n";
		msg += "!ajuda - Mostra essa mensagem novamente";
	}

	if (ts3Functions.requestSendPrivateTextMsg(schID, msg.c_str(), clientID, NULL) != ERROR_ok){
		ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
	}
}

void MusicBot::setVlcPath(string path){
	vlcPath = path;
}

string MusicBot::getVlcPath(){
	return vlcPath;
}

void MusicBot::setChannelID(uint64 cID){
	myChannelID = cID;
}

uint64 MusicBot::getChannelID(){
	return myChannelID;
}

void MusicBot::setSchID(uint64 sID){
	schID = sID;
}

anyID MusicBot::getMyID(){
	return myID;
}

bool MusicBot::setMyID(){
	if (schID == 0) return false;

	if (ts3Functions.getClientID(schID, &myID) != ERROR_ok) {
		ts3Functions.logMessage("Error querying own client id", LogLevel_ERROR, "Plugin", schID);
		return false;
	}

	return true;
}

bool MusicBot::enable(){

	if (myID == 0){
		if (!setMyID())
			return enabled == true;
	}

	if (vlcPath != ""){
		uint64 cID;
		if (ts3Functions.getChannelOfClient(schID, myID, &cID) != ERROR_ok) {
			ts3Functions.logMessage("Error querying own client channel id", LogLevel_ERROR, "Plugin", schID);
		} else {
			if (myChannelID == cID){
				enabled = true;
			} else {
				if (ts3Functions.requestClientMove(schID, myID, myChannelID, "", NULL) != ERROR_ok) {
					ts3Functions.logMessage("Error moving client", LogLevel_ERROR, "Plugin", schID);
				} else {
					enabled = true;
				}
			}
		}
	}

	return enabled == true;
}

bool MusicBot::disable(){
	enabled = false;
	return enabled == false;
}

bool MusicBot::getState(){
	return enabled;
}

MusicBot::~MusicBot(){}