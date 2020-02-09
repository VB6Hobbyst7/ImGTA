#include <Windows.h>
#include "main.h"
#include "script.h"

BOOL WINAPI DllMain( HINSTANCE inst, DWORD reason, LPVOID /*resv */ )
{
    if ( reason == DLL_PROCESS_ATTACH )
    {
        scriptRegister( inst, Load );
        presentCallbackRegister( ( PresentCallback )OnPresent );
        return TRUE;
    }
    else if ( reason == DLL_PROCESS_DETACH )
    {
        presentCallbackUnregister( ( PresentCallback )OnPresent );
        scriptUnregister( inst );
        Unload();
        return TRUE;
    }
    return FALSE;
}