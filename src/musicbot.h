#ifndef _MUSICBOT_H_
#define _MUSICBOT_H_

#include <string>
#include <vector>
#include "public_errors.h"
#include "public_errors_rare.h"
#include "public_definitions.h"
#include "public_rare_definitions.h"
#include "ts3_functions.h"
#include "telnet.h"

class MusicBot
{
private:
	bool enabled;
	std::string vlcPath;
	anyID myID;
	uint64 myChannelID;
	uint64 schID;
	TelnetClient telnet;
	std::string rcHost;
	int rcPort;
	
	std::vector<anyID> votesNext;
	std::vector<anyID> votesPrev;
	int connectedClients;

	bool commandsEnabled[10];
	bool voteEnabled;
	float pVoteNeeded;

	enum {TN_NONE = 0, TN_GET_TITLE, TN_GET_LENGTH, TN_GET_TIME} waitingFor;
	HANDLE thread;
	bool endThread;
	static MusicBot* mb;

	static DWORD WINAPI telnetThread(LPVOID lpParam);
	

public:
	MusicBot();

	int processCommand(std::string command);
	int onTextMessage(anyID fromID, std::string message);
	void onClientMove(anyID clientID, uint64 toChannel);

	void setVlcPath(std::string path);
	std::string getVlcPath();

	void setHostPort(std::string host, int port);

	void setChannelID(uint64 cID);
	uint64 getChannelID();

	void setSchID(uint64 sID);
	uint64 getSchID();

	anyID getMyID();
	bool setMyID();

	void setVote(bool vote);
	bool getVote();

	void setCommandsEnabled(bool commands[10]);
	bool* getCommandsEnabled();

	void setPVoteNeeded(float p);
	float getPVoteNeeded();

	bool telnetConnnect(std::string host, int port);
	bool telnetIsConnected();
	bool enable();
	bool disable();
	bool isEnabled();
	bool isConnected();

	bool telnetSimpleCommand(std::string cmd);
	
	
	bool startThread();
	void requestEndThread();
	

	~MusicBot();
};

#endif
