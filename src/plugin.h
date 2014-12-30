/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/
#ifndef PLUGIN_H
#define PLUGIN_H

#ifdef WIN32
#define PLUGINS_EXPORTDLL __declspec(dllexport)
#else
#define PLUGINS_EXPORTDLL __attribute__ ((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/* Required functions */
	PLUGINS_EXPORTDLL const char* ts3plugin_name();
	PLUGINS_EXPORTDLL const char* ts3plugin_version();
	PLUGINS_EXPORTDLL int ts3plugin_apiVersion();
	PLUGINS_EXPORTDLL const char* ts3plugin_author();
	PLUGINS_EXPORTDLL const char* ts3plugin_description();
	PLUGINS_EXPORTDLL void ts3plugin_setFunctionPointers(const struct TS3Functions funcs);
	PLUGINS_EXPORTDLL int ts3plugin_init();
	PLUGINS_EXPORTDLL void ts3plugin_shutdown();

	PLUGINS_EXPORTDLL int ts3plugin_offersConfigure();
	PLUGINS_EXPORTDLL void ts3plugin_configure(void* handle, void* qParentWidget);
	PLUGINS_EXPORTDLL void ts3plugin_registerPluginID(const char* id);
	PLUGINS_EXPORTDLL const char* ts3plugin_commandKeyword();
	PLUGINS_EXPORTDLL int ts3plugin_processCommand(uint64 serverConnectionHandlerID, const char* command);
	PLUGINS_EXPORTDLL void ts3plugin_freeMemory(void* data);

	/* Clientlib */
	PLUGINS_EXPORTDLL void ts3plugin_currentServerConnectionChanged(uint64 serverConnectionHandlerID);
	PLUGINS_EXPORTDLL void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber);
	PLUGINS_EXPORTDLL int  ts3plugin_onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message, int ffIgnored);
	PLUGINS_EXPORTDLL void ts3plugin_onClientMoveEvent(uint64 serverConnectionHandlerID, anyID clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage);

#ifdef __cplusplus
}
#endif

#endif
