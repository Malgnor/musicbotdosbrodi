#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <string>
#include "musicbot.h"
#include "ts3_functions.h"

namespace Global
{
	extern TS3Functions ts3Functions;
	
	extern MusicBot musicbot;

	std::string getConfigFilePath();
	void loadSettings();
}
#endif