#include "stdafx.h"
#include "SciMessager.h"

#define SCI_MAIN 0
#define SCI_SECOND 1

SciMessager::SciMessager(NppMessager *npp_messager, HWND h_main_sci, HWND h_second_sci) :
	npp_messager(npp_messager),
	h_main_sci(h_main_sci), h_second_sci(h_second_sci)
{
}

SciMessager::~SciMessager()
{
}

void SciMessager::setSciHandles(HWND h_main_sci, HWND h_second_sci)
{
	this->h_main_sci = h_main_sci;
	this->h_second_sci = h_second_sci;
}

LRESULT SciMessager::sendSciMessage(UINT message, WPARAM w_param, LPARAM l_param)
{
	int current_sci = -1;
	this->npp_messager->sendGetCurrentScintilla(&current_sci);
	if (current_sci == -1)
	{
		return FALSE;
	}

	HWND h_sci;
	if (current_sci == SCI_MAIN)
	{
		h_sci = this->h_main_sci;
	}
	else
	{
		h_sci = this->h_second_sci;
	}

	return SendMessage(h_sci, message, w_param, l_param);
}