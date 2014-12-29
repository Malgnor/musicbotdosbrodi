#include "musicbot.h"
#include "global.h"

#include <QtCore\qstring.h>
#include <sstream>

using namespace std;
using namespace Global;

MusicBot::MusicBot() : enabled(false), vlcPath(""), myID(0), myChannelID(1), schID(0), rcHost("127.0.0.1"), rcPort(32323)
{
	telnet.inicializar();
}

bool MusicBot::telnetConnnect(string host, int port){
	return telnet.conectar(host, port);
}

bool MusicBot::telnetIsConnected(){
	return telnet.estaConectado();
}

int MusicBot::processCommand(string command){
	if (myID == 0){
		if (!setMyID())
			return 0;
	}

	if (command == languages[curLanguage].COMMAND_ACTIVATE){
		if (enable()){
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_ACTIVATED_SUCESS.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}

		if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_ACTIVATED_FAIL.c_str(), myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
		return 0;
	} else if (command == languages[curLanguage].COMMAND_DEACTIVATE){
		if (disable()){
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_DEACTIVATED_SUCESS.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}

		if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_DEACTIVATED_FAIL.c_str(), myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
		return 0;
	} else if (command == languages[curLanguage].COMMAND_CONNECT){
		if (telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_ALREADY_CONNECTED.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
		bool sucesso = telnet.conectar(rcHost, rcPort);

		if (sucesso){
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_CONNECT_SUCESS.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
		}
		else{
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_CONNECT_FAIL.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
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

	uint64 fromChannelID;

	if (ts3Functions.getChannelOfClient(schID, fromID, &fromChannelID) != ERROR_ok) {
		ts3Functions.logMessage("Error querying own client channel id", LogLevel_ERROR, "Plugin", schID);
		return 0;
	}

	if (fromChannelID != myChannelID || message[0] != '!')
		return 0;
	
	if (message.find(languages[curLanguage].USER_COMMAND_HELP) != -1){
		if (!enabled){
			if (ts3Functions.requestSendPrivateTextMsg(schID, languages[curLanguage].BOT_HELP_WHEN_DISABLED.c_str(), fromID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
		} else {
			if (ts3Functions.requestSendPrivateTextMsg(schID, languages[curLanguage].BOT_HELP_WHEN_ENABLED.c_str(), fromID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
		}

		return 0;
	}

	if (!enabled) return 0;

	if (message.find(languages[curLanguage].USER_COMMAND_YOUTUBE) != -1){
		if (message.length() <= languages[curLanguage].USER_COMMAND_YOUTUBE.length()+2){
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_PARAMETER_MISSING.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}

		string param = message;
		param.erase(0, languages[curLanguage].USER_COMMAND_YOUTUBE.length()+1);

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
			atual += languages[curLanguage].BOT_ADDED_TO_PLAYLIST;
			
			if (ts3Functions.requestSendChannelTextMsg(schID, atual.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}

			return 0;
		} else {
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_INVALID_PARAMETER.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
	} else if (message.find(languages[curLanguage].USER_COMMAND_PLAYING) != -1){
		if (!telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_TELNET_NOT_CONNECTED.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
		if (telnet.enviar("get_title\r\n") > 0){
			Sleep(100);
			string resposta = "";
			if (telnet.receber(resposta, 2048) > 0){
				if (telnet.enviar("get_title\r\n") > 0){
					Sleep(100);
					resposta = "";
					if (telnet.receber(resposta, 2048) > 0){
						int l = (int)resposta.find("\n");
						string b = resposta;
						if (resposta.length() - l > 1 && l != -1){
							while (true){
								int k = (int)resposta.find("\n", l + 1);
								if (k == -1 || resposta.length() - k == 1){
									break;
								}
								l = k;
							}
							b = resposta.substr(l + 1);
						}

						if (ts3Functions.requestSendChannelTextMsg(schID, b.c_str(), myChannelID, NULL) != ERROR_ok){
							ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
						}
						return 0;

					} else {
						if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_TRY_AGAIN.c_str(), myChannelID, NULL) != ERROR_ok){
							ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
						}
						return 0;
					}
				}
			}
		}
		return 0;
	} else if (message.find(languages[curLanguage].USER_COMMAND_LENGTH) != -1){
		if (!telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_TELNET_NOT_CONNECTED.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
		while (telnet.enviar("get_length\r\n") > 0){
			Sleep(100);
			string resposta = "";
			if (telnet.receber(resposta, 2048) > 0){
				int l = (int)resposta.find("\n");
				string b = resposta;
				if (resposta.length() - l > 1 && l != -1){
					while (true){
						int k = (int)resposta.find("\n", l + 1);
						if (k == -1 || resposta.length() - k == 1){
							break;
						}
						l = k;
					}
					b = resposta.substr(l + 1);
				}

				if (!(b.find("(") != -1 || b.find(")") != -1 || b.find(":") != -1 || b.find(" ") != -1)){
					try{
						int duracao = stoi(resposta);
						int s = duracao % 60;
						int m = duracao / 60;
						stringstream d;
						if (m > 0)
							d << m << " " << languages[curLanguage].BOT_MINUTES;
						if (m > 0 && s > 0)
							d << " " << languages[curLanguage].BOT_AND << " ";
						if (s > 0)
							d << (s < 10 ? "0" : "") << s << " " << languages[curLanguage].BOT_SECONDS;
						if (ts3Functions.requestSendChannelTextMsg(schID, d.str().c_str(), myChannelID, NULL) != ERROR_ok){
							ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
						}
						return 0;
					} catch(exception e) {
						if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_TRY_AGAIN.c_str(), myChannelID, NULL) != ERROR_ok){
							ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
						}
						return 0;
					}
				}
			} else {
				if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_ERROR.c_str(), myChannelID, NULL) != ERROR_ok){
					ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
				}
				return 0;
			}
		}
	} else if (message.find(languages[curLanguage].USER_COMMAND_NEXT) != -1){
		telnetSimpleCommand("next\r\n");
	} else if (message.find(languages[curLanguage].USER_COMMAND_PREV) != -1){
		telnetSimpleCommand("prev\r\n");
	} else if (message.find(languages[curLanguage].USER_COMMAND_PAUSE) != -1){
		telnetSimpleCommand("pause\r\n");
	} else if (message.find(languages[curLanguage].USER_COMMAND_PLAY) != -1){
		telnetSimpleCommand("play\r\n");
	} else if (message.find(languages[curLanguage].USER_COMMAND_GOTO) != -1){
		if (!telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_TELNET_NOT_CONNECTED.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
		if (message.length() <= languages[curLanguage].USER_COMMAND_GOTO.length()+2){
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_PARAMETER_MISSING.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}

		string param = message;
		param.erase(0, languages[curLanguage].USER_COMMAND_GOTO.length()+1);
		string msg = "seek ";
		int a;
		if ( (a = (int)param.find(":")) != -1){
			string s = param.substr(a + 1);
			string m = "0";
			int t = (int)(param.length() - s.length() - 1);
			if (t > 0)
				m = param.substr(0, t);
			try{
				int total = stoi(m) * 60 + stoi(s);
				stringstream b;
				b << total;
				msg += b.str();
			} catch(exception e) {
			}
		} else {
			msg += param;
		}
		msg += "\r\n";
		if (telnet.enviar(msg) > 0){
			Sleep(100);
			string resposta = "";
			if (telnet.receber(resposta, 2048) > 0){
				return 0;
			}
		} else {
			if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_ERROR.c_str(), myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
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

	if (!enabled){
		if (ts3Functions.requestSendPrivateTextMsg(schID, languages[curLanguage].BOT_HELP_WHEN_DISABLED.c_str(), clientID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
	} else {
		if (ts3Functions.requestSendPrivateTextMsg(schID, languages[curLanguage].BOT_HELP_WHEN_ENABLED.c_str(), clientID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
	}

}

void MusicBot::setVlcPath(string path){
	vlcPath = path;
}

string MusicBot::getVlcPath(){
	return vlcPath;
}

void MusicBot::setHostPort(string host, int port)
{
	rcHost = host;
	rcPort = port;
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

uint64 MusicBot::getSchID(){
	return schID;
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

bool MusicBot::isEnabled(){
	return enabled;
}

bool MusicBot::isConnected(){
	return (schID != 0);
}

bool MusicBot::telnetConnnect(string host, int port){
	return telnet.conectar(host, port);
}

bool MusicBot::telnetIsConnected(){
	return telnet.estaConectado();
}

int MusicBot::telnetSimpleCommand(string cmd){
	if (!telnet.estaConectado()){
		if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_TELNET_NOT_CONNECTED.c_str(), myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
		return 0;
	}
	if (telnet.enviar(cmd) > 0){
		Sleep(100);
		string resposta = "";
		if (telnet.receber(resposta, 2048) > 0){
			return 0;
		}
	} else {
		if (ts3Functions.requestSendChannelTextMsg(schID, languages[curLanguage].BOT_ERROR.c_str(), myChannelID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
		return 0;
	}
}

MusicBot::~MusicBot(){}