#include "global.h"
#include <QtCore\qsettings.h>

namespace Global
{

	TS3Functions ts3Functions;

	MusicBot musicbot;

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
		musicbot.setChannelID(cfg.value("channelId", 0).toInt());
	}

}