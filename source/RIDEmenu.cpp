#include "stdafx.h"
#include "TString.h"
#include "RIDEmenu.h"
#include "RIDEmain.h"
#include "NewProjectDlg.h"
#include "SettingsDlg.h"
#include "resource.h"


extern RIDEmain plugin;

TString RIDEmenu::about_text = _T("- ������ \"Notepad++\" �� \"RIDE\" � ��������� ����.\n") \
_T("- ������ \"������� ������\" ������� ����� ������� � ���� main.rcs.") \
_T("��� ���� ����� ���������� � ���������� �������� ������ - ���� ����������� �� ������� ��.\n") \
_T("- ������ \"���������\" ��������� ���� �������������� ����������.\n") \
_T("\n") \
_T("TODO:\n") \
_T("- ������ \"����� ����\" ��� �������� ����� � ����� �������. ������ ���� ����� ������ ��� ������ � ��������.\n") \
_T("- ������ \"�������� ������������\" ��� ��������� ������ ������� ����� ������� �����������.\n") \
_T("- ������ \"������� ����������\".\n") \
_T("- ������� ��� ������ �� ������.\n") \
_T("- ������ ������ �������.\n") \
_T("- ��������������.");

/* FuncItem:
	char _itemName[64] - name to display
	*void() _pfunc - pointer to the routine to execute
	int _cmdId - a command index
	bool _init2check - if the item is checked at startup
	Shortcut *_pShKey - a pointer to a structure describing the key bound
*/
FuncItem RIDEmenu::func_items[FUNCS_NUMBER] =
{
	{ _T("New project"), &RIDEmenu::newProject, 1, false, NULL },
	{ _T("Settings"), &RIDEmenu::settingsDlg, 2, false, NULL },
	{ _T(""), NULL, -1, false, NULL },
	{ _T("About"), &RIDEmenu::aboutBox, 0, false, NULL }
};

void RIDEmenu::aboutBox()
{
	/*TCHAR dll_file[MAX_PATH];
	GetModuleFileName(plugin.getDllModule(), dll_file, sizeof(dll_file));

	TString about_file(dll_file);
	about_file = about_file.substr(0, about_file.rfind('\\') + 1) + RIDEmenu::about_filename;

	TIfStream fin(about_file.c_str());
	TString str;
	TString about_text;
	while (std::getline(fin, str))
	{
		about_text += str;
	}
	fin.close();*/

	MessageBox(plugin.getNppData()._nppHandle,
		RIDEmenu::about_text.c_str(),
		_T("��� ������ RIDE"),
		MB_OK);
}

void RIDEmenu::settingsDlg()
{
	doModalSettingsDlg();
}

void RIDEmenu::newProject()
{
	doModalNewProjectDlg();
}

LRESULT RIDEmenu::showMessage(LPCTSTR message)
{
	return MessageBox(plugin.getNppData()._nppHandle, message, _T("���������� ����������"), MB_OK);
}
