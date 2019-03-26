#pragma once

#include "NppMessager.h"

class SciMessager
{
private:
	HWND h_main_sci;
	HWND h_second_sci;
	NppMessager *npp_messager;
public:
	SciMessager(NppMessager *npp_messager, HWND h_main_sci, HWND h_second_sci);
	~SciMessager();

	void setSciHandles(HWND h_main_sci, HWND h_second_sci);

private:
	LRESULT sendSciMessage(UINT message, WPARAM w_param, LPARAM l_param);
};
