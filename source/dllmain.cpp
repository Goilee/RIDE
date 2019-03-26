// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "stdafx.h"
#include "RIDEmain.h"


RIDEmain plugin = RIDEmain();

BOOL APIENTRY DllMain( HMODULE h_dll_module,
                       DWORD  ul_reason_for_call,
                       LPVOID lp_reserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		plugin.onDllProcessAttach(h_dll_module);
		break;
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		plugin.onDllProcessDetach();
        break;
    }
    return TRUE;
}

void setInfo(NppData npp_data)
{
	plugin.setNppData(npp_data);
}

LPCTSTR getName()
{
	return plugin.getPluginName();
}

FuncItem* getFuncsArray(int *ptr_funcs_number)
{
	return plugin.getFuncsArray(ptr_funcs_number);
}

void beNotified(SCNotification *ptr_sci_notification)
{
	plugin.beNotified(ptr_sci_notification);
}

LRESULT messageProc(UINT message, WPARAM w_param, LPARAM l_param)
{
	return plugin.messageProc(message, w_param, l_param);
	isUnicode();
}

#ifdef UNICODE
BOOL isUnicode()
{
	return true;
}
#endif
