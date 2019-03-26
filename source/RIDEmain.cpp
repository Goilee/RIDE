#include "stdafx.h"
#include "RIDEmain.h"
#include "RIDEmenu.h"
#include "TString.h"


RIDEmain::RIDEmain() :
	settings(Settings())
{
}

RIDEmain::~RIDEmain()
{
}

Settings RIDEmain::getSettings()
{
	return this->settings;
}

void RIDEmain::beNotified(SCNotification *ptr_sci_notification)
{
	switch (ptr_sci_notification->nmhdr.code)
	{
	case NPPN_BUFFERACTIVATED:  /* ����� Notepad++ --> RIDE � ��������� ����
								�� ��� NPPN_FILEOPENED, �.�. ����� �������� ����� ������� ��� ��� �������� ���������

								��� �������� NPPN_BUFFERACTIVATED?
								*/
		TCHAR file_name[MAX_PATH];
		this->npp_messager->sendGetFullCurrentPath(MAX_PATH, file_name);

		TString title(file_name);
		title += _T(" - RIDE");
		this->npp_messager->sendWMsetText(title.c_str());
		break;
	}
}

LRESULT RIDEmain::messageProc(UINT message, WPARAM w_param, LPARAM l_param)
{
	return TRUE;
}

FuncItem * RIDEmain::getFuncsArray(int *ptr_funcs_number)
{
	*ptr_funcs_number = FUNCS_NUMBER;
	return RIDEmenu::func_items;
}

void RIDEmain::init()
{
}

void RIDEmain::cleanUp()
{
}

void RIDEmain::onDllProcessAttach(HMODULE h_module)
{
	this->h_dll_module = h_module;  /* TODO ��� ������, ���� ������ ���������?
									   "������� ������ � ����� ���������� "Windows ��� ��������������",
									   ����������, ��� ��� ������� �������� DLL_PROCESS_ATTACH ���������� ���� �������."
									   � ����������� � ��������� �������� ��� NPP �������, ��� ��� ������� �����������.
									   */
	if (this->attach_count == 0)
	{
		this->init();
	}
	this->attach_count += 1;
}

void RIDEmain::onDllProcessDetach()
{
	this->attach_count -= 1;
	if (this->attach_count == 0)
	{
		this->cleanUp();
	}
}