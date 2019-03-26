#include "stdafx.h"
#include "NppMessager.h"
#include "Notepad_plus_msgs.h"
#include "menuCmdID.h"


NppMessager::NppMessager(HWND npp_handle) :
	npp_handle(npp_handle)
{
}

NppMessager::~NppMessager()
{
}

void NppMessager::setNppHandle(HWND npp_handle)
{
	this->npp_handle = npp_handle;
}

LRESULT NppMessager::sendGetFullCurrentPath(size_t path_len, LPTSTR path)
{
	return this->sendNppMessage(NPPM_GETFULLCURRENTPATH, path_len, (LPARAM)path);
}

LRESULT NppMessager::sendWMsetText(LPCTSTR title)
{
	return this->sendNppMessage(WM_SETTEXT, NULL, (LPARAM)title);
}

LRESULT NppMessager::sendGetCurrentScintilla(int *ptr_sci_id)
{
	return this->sendNppMessage(NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)ptr_sci_id);
}

LRESULT NppMessager::sendDoOpen(LPTSTR full_path)
{
	return this->sendNppMessage(NPPM_DOOPEN, 0, (LPARAM)full_path);
}

LRESULT NppMessager::sendCloseAllFiles()
{
	return this->sendNppMessage(NPPM_MENUCOMMAND, 0, IDM_FILE_CLOSEALL);
}

LRESULT NppMessager::sendGetNumberAllOpenedFiles()
{
	return this->sendNppMessage(NPPM_GETNBOPENFILES, 0, ALL_OPEN_FILES);
}

LRESULT NppMessager::sendSaveAllFiles()
{
	return this->sendNppMessage(NPPM_SAVEALLFILES, 0, 0);
}

LRESULT NppMessager::sendNppMessage(UINT message, WPARAM w_param, LPARAM l_param)
{
#ifdef UNICODE
	return SendMessageW(this->npp_handle, message, w_param, l_param);
#else
	return SendMessage(this->npp_handle, message, w_param, l_param);
#endif
}