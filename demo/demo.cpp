#include "framework.h"
#include "demo.h"

using namespace std;

BOOL MyEventHandler(LPVOID lpArgName1, LPVOID lpReserved);

DLLAPI BOOL PluginEntry(PPLUGINHOST pInstance)
{
	if (pInstance->CheckPluginExists("easyauth") == FALSE)
	{
		cout << "easyauth: not exists" << endl;
		// return FALSE;
	}
	// 中文字符
	BOOL ret = FALSE;
	BOOL bResult = pInstance->CallEventHandler("easyauth", "EnvSupported", ret);
	if (bResult == FALSE)
	{
		MessageBox(NULL,
			L"Could not enable plugin: failed to connect easyauth plugin.",
			L"Demo Plugin", MB_ICONERROR);
		pInstance->CallEventHandler("", "DoNotCallAgainInit", GetModuleHandle(NULL));
		return FALSE;
	}
	if (ret == FALSE)
	{
		MessageBox(NULL,
			L"Could not enable plugin: easyauth not supported this environment.",
			L"Demo Plugin", MB_ICONERROR);
		pInstance->CallEventHandler("", "DoNotCallAgainInit", GetModuleHandle(NULL));
		return FALSE;
	}
	pInstance->RegisterPlugin(GetModuleHandle(NULL), "demo");
	pInstance->RegisterEventHandler("demo", "MyHandler", MyEventHandler);
	return TRUE;
}

BOOL MyEventHandler(LPVOID lpArgName1, LPVOID lpReserved)
{
	return FALSE;
}