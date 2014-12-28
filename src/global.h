#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <string>
#include "musicbot.h"
#include "ts3_functions.h"

struct Localization {

	/* COMMANDS / */

	std::string COMMAND_ACTIVATE;
	std::string COMMAND_DEACTIVATE;
	std::string COMMAND_CONNECT;

	/* INFOS */

	std::string BOT_ACTIVATED_SUCESS;
	std::string BOT_ACTIVATED_FAIL;
	std::string BOT_DEACTIVATED_SUCESS;
	std::string BOT_DEACTIVATED_FAIL;
	std::string BOT_CONNECT_SUCESS;
	std::string BOT_CONNECT_FAIL;
	std::string BOT_ALREADY_CONNECTED;

	/* COMMANDS ! */

	std::string USER_COMMAND_YOUTUBE;
	std::string USER_COMMAND_HELP;
	std::string USER_COMMAND_PLAYING;
	std::string USER_COMMAND_LENGTH;
	std::string USER_COMMAND_NEXT;
	std::string USER_COMMAND_PREV;
	std::string USER_COMMAND_PAUSE;
	std::string USER_COMMAND_PLAY;
	std::string USER_COMMAND_GOTO;

	/* INFOS */

	std::string BOT_PARAMETER_MISSING;
	std::string BOT_INVALID_PARAMETER;
	std::string BOT_ADDED_TO_PLAYLIST;
	std::string BOT_HELP_WHEN_ENABLED;
	std::string BOT_HELP_WHEN_DISABLED;
	std::string BOT_TELNET_NOT_CONNECTED;
	std::string BOT_TRY_AGAIN;
	std::string BOT_MINUTES;
	std::string BOT_SECONDS;
	std::string BOT_AND;
	std::string BOT_ERROR;

	/* SETTINGS GUI*/

	std::string GUI_WINDOWTITLE;
	std::string GUI_LABEL_VLC_EXE_PATH;
	std::string GUI_LABEL_MUSIC_CHANNEL;
	std::string GUI_BUTTON_USE_CURRENT_CHANNEL;
	std::string GUI_LABEL_LANGUAGE;
	std::string GUI_LAVEL_RC_PORT;
	std::string GUI_BUTTON_CONNECT_TO_VLC;
	std::string GUI_BUTTON_CONNECTED;
	std::string GUI_BUTTON_DEACTIVATE_BOT;
	std::string GUI_BUTTON_ACTIVATE_BOT;
};

namespace Global
{
	extern TS3Functions ts3Functions;
	
	extern MusicBot musicbot;

	extern Localization languages[2];
	extern int curLanguage;
	enum { LANG_PT_BR = 0, LANG_EN_US };

	std::string getConfigFilePath();
	void loadSettings();
	void generateLocaleStrings();

}


#endif