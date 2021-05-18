#include <Windows.h>
#include "main.h"
#include "script.h"
#include <cstdio>
#include <iostream>

FILE * stream = NULL;
BOOL WINAPI DllMain( HINSTANCE inst, DWORD reason, LPVOID /*resv */ )
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(inst);
		scriptRegister(inst, Load);
		presentCallbackRegister((PresentCallback)OnPresent);
		break;

	case DLL_PROCESS_DETACH:
		Unload();
		presentCallbackUnregister((PresentCallback)OnPresent);
		scriptUnregister(inst);
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;
	}

    return TRUE;
}