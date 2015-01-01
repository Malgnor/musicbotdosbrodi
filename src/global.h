#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <string>
#include "musicbot.h"
#include "ts3_functions.h"

#define PLUGIN_API_VERSION 20
#define PLUGIN_NAME "Musicbot dos Brodi"
#define PLUGIN_VERSION "0.7.1"
#define PLUGIN_AUTHOR "Brodi\'s Dev"
#define PLUGIN_DESCRIPTION "This is a musicbot plugin, it has commands to add music from youtube to playlist, change music, pause and many other functions."

#define COMMANDS_QTD 10

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

	std::string USER_COMMAND_YOUTUBE;	// 0
	std::string USER_COMMAND_HELP;		// 1
	std::string USER_COMMAND_PLAYING;	// 2
	std::string USER_COMMAND_LENGTH;	// 3
	std::string USER_COMMAND_NEXT;		// 4
	std::string USER_COMMAND_PREV;		// 5
	std::string USER_COMMAND_PAUSE;		// 6
	std::string USER_COMMAND_PLAY;		// 7
	std::string USER_COMMAND_GOTO;		// 8
	std::string USER_COMMAND_TIME;		// 9

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
	std::string BOT_NECESSARY_VOTES;
	std::string BOT_NOT_PLAYING;

	/* SETTINGS GUI*/

	std::string GUI_TITLE_SETTINGS;
	std::string GUI_LABEL_VLC_EXE_PATH;
	std::string GUI_LABEL_MUSIC_CHANNEL;
	std::string GUI_BUTTON_USE_CURRENT_CHANNEL;
	std::string GUI_LABEL_LANGUAGE;
	std::string GUI_LABEL_RC_PORT;
	std::string GUI_BUTTON_CONNECT_TO_VLC;
	std::string GUI_BUTTON_CONNECTED;
	std::string GUI_BUTTON_DEACTIVATE_BOT;
	std::string GUI_BUTTON_ACTIVATE_BOT;
	std::string GUI_CHB_COMMAND_BY_VOTES;
	std::string GUI_PREFFIX_NECESSARY_VOTES;
	std::string GUI_BUTTON_ENABLE_DISABLE_COMMANDS;
	std::string GUI_TITLE_COMMANDS;
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