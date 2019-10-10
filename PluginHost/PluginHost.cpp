#include "pch.h"

using namespace std;

constexpr auto PLUGINHOST_VERSION = "1.0.0-SNAPSHOT";

#include "plugindef.h"

#include "wcmbconv.h"
#include "ErrorCodesDef.h"

int main(int argc, char* argv[])
{

	// 这里把当前活动代码设置成为系统默认代码页
	char szBuf[5]; // .XXX\0
	sprintf(szBuf, ".%d", GetACP());

	setlocale(LC_CTYPE, szBuf);

	cout << "Plugin Host [version " << PLUGINHOST_VERSION << "]" << endl;
	cout << "Copyright (c) 2019 Sacred Realm. All Rights Reserved." << endl << endl;

	cout << "Command line: " << endl << GetCommandLineA() << endl << endl;

	if (argc < 2)
	{
		cout << "usage: PluginHost.exe [file] <arguments>..." << endl;
		return ERROR_MISSING_ARUMENT;
	}

	HMODULE hModule = LoadLibrary(char2wchar(argv[1]));
	if (!hModule)
	{
		goto ErrorExit;
	}
	else
	{
		typedef BOOL(*PPLUGINENTRY)(PPLUGINHOST);
		PPLUGINENTRY pPluginEntry = (PPLUGINENTRY)GetProcAddress(hModule, "PluginEntry");
		if (pPluginEntry == NULL)
		{
			goto ErrorExit;
		}
		else
		{
			PluginHost pluginHost;
			pPluginEntry(&pluginHost);
		}
		
	}

	return S_NORMAL;

ErrorExit:
	{
		TCHAR szBuf[128];
		LPVOID lpMsgBuf;
		DWORD dw = GetLastError();
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)& lpMsgBuf, 0, NULL);
		wsprintf(
			szBuf,
			_T("Cloud not load \"%s\" (code: %d): %s"),
			char2wchar(argv[1]), dw, lpMsgBuf);
		LocalFree(lpMsgBuf);
		wcout << szBuf << endl;
		return dw;
	}
}

// 以下代码是 PluginHost 对插件的服务接口的实现

BOOL PluginHost::RegisterPlugin(HMODULE hModule, PCCH pszPluginName)
{
	cout << "RegisterPlugin: hModule: 0x" << hModule << ", pszPluginName: " << pszPluginName << endl;
	return 0;
}

BOOL PluginHost::UnregisterPlugin(HMODULE hModule)
{
	cout << "UnregisterPlugin: hModule: 0x" << hModule << endl;
	return 0;
}

BOOL PluginHost::UnregisterPlugin(PCCH pszPluginName)
{
	cout << "UnregisterPlugin: pszPluginName: " << pszPluginName << endl;
	return 0;
}

BOOL PluginHost::RegisterEventHandler(HMODULE hModule, PCCH pszHandlerName, PVOID pHandler)
{
	cout << "UnregisterPlugin: hModule: 0x" << hModule << ", pszHandlerName: " << pszHandlerName
		<< ", pHandler: 0x" << pHandler << endl;
	return 0;
}

BOOL PluginHost::RegisterEventHandler(PCCH pszPluginName, PCCH pszHandlerName, PVOID pHandler)
{
	cout << "RegisterEventHandler: pszPluginName: " << pszPluginName << ", pszHandlerName: "
		<< pszHandlerName << ", pHandler: 0x" << pHandler << endl;
	return 0;
}

BOOL PluginHost::UnregisterEventHandler(HMODULE hModule, PCCH pszName)
{
	cout << "UnregisterEventHandler: hModule: 0x" << hModule << ", pszName: " << pszName << endl;
	return 0;
}

BOOL PluginHost::UnregisterEventHandler(PCCH pszPluginName, PCCH pszName)
{
	cout << "UnregisterEventHandler: pszPluginName: " << pszPluginName << ", pszName: " << pszName << endl;
	return 0;
}

BOOL PluginHost::CallEventHandler(HMODULE hModule, PCCH pszHandlerName, ...)
{
	cout << "CallEventHandler: hModule: 0x" << hModule << ", pszHandlerName: " << pszHandlerName << endl;
	return 0;
}

BOOL PluginHost::CallEventHandler(PCCH pszPluginName, PCCH pszHandlerName, ...)
{
	cout << "CallEventHandler: pszPluginName: " << pszPluginName << ", pszHandlerName: " << pszHandlerName << endl;
	return 0;
}

BOOL PluginHost::CheckPluginExists(PCCH pszPluginName)
{
	cout << "CheckPluginExists: pszPluginName: " << pszPluginName << endl;
	return 0;
}

HMODULE PluginHost::GetPluginModuleHandler(PCCH pszPluginName)
{
	cout << "GetPluginModuleHandler: pszPluginName: " << pszPluginName << endl;
	return HMODULE();
}

PCCH PluginHost::GetPluginModuleName(HMODULE hModule)
{
	cout << "GetPluginModuleName: hModule: 0x" << hModule << endl;
	return PCCH();
}
