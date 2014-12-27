#ifndef _MUSICBOT_H_
#define _MUSICBOT_H_

#include <string>
#include <vector>
#include "public_errors.h"
#include "public_errors_rare.h"
#include "public_definitions.h"
#include "public_rare_definitions.h"
#include "ts3_functions.h"

class MusicBot
{
private:
	bool enabled;
	std::string vlcPath;
	anyID myID;
	uint64 myChannel;
	uint64 schID;

	MusicBot();

	int processCommand(std::string command);
	int onTextMessage(anyID fromID, std::string message);
	void onClientMove(anyID clientID, uint64 toChannel, std::string moveMessage);

	void setVlcPath(std::string path);
	std::string getVlcPath();

	void setChannelID(uint64 cID);
	uint64 getChannelID();

	void setSchID(uint64 sID);

	bool enable();
	bool disable();
	bool getState();

	~MusicBot();
};

#endif