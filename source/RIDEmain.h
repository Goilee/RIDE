#pragma once

#include "RIDEcore.h"
#include "Settings.h"


class RIDEmain :
	public RIDEcore
{
private:
	Settings settings;
public:
	RIDEmain();
	~RIDEmain();

	void beNotified(SCNotification *ptr_notification);
	LRESULT messageProc(UINT message, WPARAM w_param, LPARAM l_param);
	FuncItem* getFuncsArray(int *ptr_funcs_number);
	void onDllProcessAttach(HMODULE h_module);
	void onDllProcessDetach();
	Settings getSettings();
private:
	void init();
	void cleanUp();
};

