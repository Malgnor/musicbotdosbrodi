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
	} else if (command == "conectar"){
		if (telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, "Ja esta conectado.", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
		bool sucesso = telnet.conectar(rcHost, rcPort);
		string msg;
		if (sucesso)
			msg = "Sucesso!";
		else
			msg = "Falha!";

		if (ts3Functions.requestSendChannelTextMsg(schID, msg.c_str(), myChannelID, NULL) != ERROR_ok){
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
			msg += "Comandos dispon\303\255veis: \n";
			msg += "!youtube link - Coloca o link na playlist\n";
			msg += "!atual - Mostra a m\303\272sica atual\n";
			msg += "!duracao - Mostra duracao da m\303\272sica atual\n";
			msg += "!proximo - Pula para a proxima m\303\272sica\n";
			msg += "!anterior - Pula para a m\303\272sica anterior\n";
			msg += "!pausar - Pausa/despausa m\303\272sica atual\n";
			msg += "!play - Toca m\303\272sica atual\n";
			msg += "!irpara xx - Vai para o momento xx segundos da m\303\272sica\n";
			msg += "!irpara x:y - Vai para o momento x minutos e y segundos da m\303\272sica\n";
			msg += "!ajuda - Mostra essa mensagem novamente\n";
		}
		if (ts3Functions.requestSendPrivateTextMsg(schID, msg.c_str(), fromID, NULL) != ERROR_ok){
			ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
		}
		return 0;
	} else if (message.find("!atual") != -1){
		if (!telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, "Telnet nao esta conectado!", myChannelID, NULL) != ERROR_ok){
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
						if (ts3Functions.requestSendChannelTextMsg(schID, "Tente novamente!", myChannelID, NULL) != ERROR_ok){
							ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
						}
						return 0;
					}
				}
			}
		}
		return 0;
	} else if (message.find("!duracao") != -1){
		if (!telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, "Telnet nao esta conectado!", myChannelID, NULL) != ERROR_ok){
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
							d << m << " minutos";
						if (m > 0 && s > 0)
							d << " e ";
						if (s > 0)
							d << (s < 10 ? "0" : "") << s << " segundos";
						if (ts3Functions.requestSendChannelTextMsg(schID, d.str().c_str(), myChannelID, NULL) != ERROR_ok){
							ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
						}
						return 0;
					} catch(exception e) {
						return 0;
					}
				}
			} else {
				if (ts3Functions.requestSendChannelTextMsg(schID, "Erro!", myChannelID, NULL) != ERROR_ok){
					ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
				}
				return 0;
			}
		}
	} else if (message.find("!proximo") != -1){
		if (!telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, "Telnet nao esta conectado!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
		if (telnet.enviar("next\r\n") > 0){
			Sleep(100);
			string resposta = "";
			if (telnet.receber(resposta, 2048) > 0){
				return 0;
			}
		} else {
			if (ts3Functions.requestSendChannelTextMsg(schID, "Erro!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
	} else if (message.find("!anterior") != -1){
		if (!telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, "Telnet nao esta conectado!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
		if (telnet.enviar("prev\r\n") > 0){
			Sleep(100);
			string resposta = "";
			if (telnet.receber(resposta, 2048) > 0){
				return 0;
			}
		} else {
			if (ts3Functions.requestSendChannelTextMsg(schID, "Erro!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
	} else if (message.find("!pausar") != -1){
		if (!telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, "Telnet nao esta conectado!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
		if (telnet.enviar("pause\r\n") > 0){
			Sleep(100);
			string resposta = "";
			if (telnet.receber(resposta, 2048) > 0){
				return 0;
			}
		} else {
			if (ts3Functions.requestSendChannelTextMsg(schID, "Erro!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
	} else if (message.find("!play") != -1){
		if (!telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, "Telnet nao esta conectado!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
		if (telnet.enviar("play\r\n") > 0){
			Sleep(100);
			string resposta = "";
			if (telnet.receber(resposta, 2048) > 0){
				return 0;
			}
		} else {
			if (ts3Functions.requestSendChannelTextMsg(schID, "Erro!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
	} else if (message.find("!irpara") != -1){
		if (!telnet.estaConectado()){
			if (ts3Functions.requestSendChannelTextMsg(schID, "Telnet nao esta conectado!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}
		if (message.length() <= 9){
			if (ts3Functions.requestSendChannelTextMsg(schID, "Faltou par\303\242metro!", myChannelID, NULL) != ERROR_ok){
				ts3Functions.logMessage("Error requesting send text message", LogLevel_ERROR, "Plugin", schID);
			}
			return 0;
		}

		string param = message;
		param.erase(0, 8);
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
			if (ts3Functions.requestSendChannelTextMsg(schID, "Erro!", myChannelID, NULL) != ERROR_ok){
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

	string msg = "Bem-Vindo ao meu canal de m\303\272sica!\n";
	if (!enabled){
		msg += "Atualmente estou desativado.\n";
		msg += "Entre em contato com algum admin para mais info.";
	} else {
		msg += "Comandos dispon\303\255veis: \n";
		msg += "!youtube link - Coloca o link na playlist\n";
		msg += "!atual - Mostra a m\303\272sica atual\n";
		msg += "!duracao - Mostra duracao da m\303\272sica atual\n";
		msg += "!proximo - Pula para a proxima m\303\272sica\n";
		msg += "!anterior - Pula para a m\303\272sica anterior\n";
		msg += "!pausar - Pausa/despausa m\303\272sica atual\n";
		msg += "!play - Toca m\303\272sica atual\n";
		msg += "!irpara xx - Vai para o momento xx segundos da m\303\272sica\n";
		msg += "!irpara x:y - Vai para o momento x minutos e y segundos da m\303\272sica\n";
		msg += "!ajuda - Mostra essa mensagem novamente\n";
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

MusicBot::~MusicBot(){}