#include "global.h"
#include <QtCore\qsettings.h>
#include "langs.h"

namespace Global
{

	TS3Functions ts3Functions;

	MusicBot musicbot;

	Localization languages[2];
	int curLanguage = LANG_EN_US;

	std::string getConfigFilePath(){
		char* configPath = (char*)malloc(512);
		ts3Functions.getConfigPath(configPath, 512);
		std::string path = configPath;
		free(configPath);
		path.append("MusicBotdosBrodi.ini");
		return path;
	}

	void loadSettings(){
		QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
		musicbot.setVlcPath(cfg.value("vlcPath", "\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\"").toString().toStdString());
		std::string host = cfg.value("rcHost", "127.0.0.1").toString().toStdString();
		int port = cfg.value("rcPort", 32323).toInt();
		musicbot.setHostPort(host, port);
		if (musicbot.isConnected()){
			std::string channel = cfg.value("channelName", "Default Channel").toString().toStdString();
			uint64 schID = musicbot.getSchID();
			uint64* canais;
			if (ts3Functions.getChannelList(schID, &canais) != ERROR_ok){
				ts3Functions.logMessage("Error requesting channel list", LogLevel_ERROR, "Plugin", schID);
				return;
			}
			unsigned int i = 0;
			while (canais[i]){
				char* nomeCanal;
				if (ts3Functions.getChannelVariableAsString(schID, canais[i], 0, &nomeCanal) != ERROR_ok){
					ts3Functions.logMessage("Error requesting channel name", LogLevel_ERROR, "Plugin", schID);
					return;
				}
				std::string nome = nomeCanal;
				if (nome == channel){
					musicbot.setChannelID(canais[i]);
					delete[] nomeCanal;
					break;
				}
				delete[] nomeCanal;
				i++;
			}
		}
	}

	void generateLocaleStrings(){
		generateENUSStrings();
		generatePTBRStrings();
	}

}