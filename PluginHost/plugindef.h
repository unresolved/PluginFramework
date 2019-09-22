#ifndef PLUGINDEF_H
#define PLUGINDEF_H

#include <windows.h>

class PluginHost
{
public:
	virtual BOOL RegisterPlugin(HMODULE hModule, PCCH pszPluginName);
	virtual BOOL UnregisterPlugin(HMODULE hModule);
	virtual BOOL UnregisterPlugin(PCCH pszPluginName);

	virtual BOOL RegisterEventHandler(HMODULE hModule, PCCH pszHandlerName, PVOID pHandler);
	virtual BOOL RegisterEventHandler(PCCH pszPluginName, PCCH pszHandlerName, PVOID pHandler);
	virtual BOOL UnregisterEventHandler(HMODULE hModule, PCCH pszName);
	virtual BOOL UnregisterEventHandler(PCCH pszPluginName, PCCH pszName);
	virtual BOOL CallEventHandler(HMODULE hModule, PCCH pszHandlerName, ...);
	virtual BOOL CallEventHandler(PCCH pszPluginName, PCCH pszHandlerName, ...);

	virtual BOOL CheckPluginExists(PCCH pszPluginName);
	virtual HMODULE GetPluginModuleHandler(PCCH pszPluginName);
	virtual PCCH GetPluginModuleName(HMODULE hModule);
};

typedef PluginHost* PPLUGINHOST;

// #define PLUGIN_DEV

#ifdef PLUGIN_DEV

#define DLLAPI extern "C" __declspec(dllexport)

DLLAPI BOOL PluginEntry(PluginHost* pInstance);

#endif // PLUGIN_DEV

#endif // PLUGINDEF_H