#include "stdafx.h"
#include "RIDEmain.h"
#include "SettingsDlg.h"
#include "resource.h"
#include "RIDEmenu.h"

#include <iostream>


extern RIDEmain plugin;

namespace
{
	DWORD onOK(HWND h_dlg)
	{
		// получаем handle для строки-ввода
		HWND h_edit = GetDlgItem(h_dlg, IDC_MFCEDITBROWSE);
		if (!h_edit)
		{
			RIDEmenu::showMessage(_T("Error in onOK(): GetDlgItem() returned NULL."));
			return -1;
		}

		// считываем из строки текст
		TCHAR text[MAX_PATH];
		GetWindowText(h_edit, text, MAX_PATH);

		// сохраняем в параметры (там создается папка)
		DWORD error = plugin.getSettings().setProjectsPath(text);
		if (error == ERROR_PATH_NOT_FOUND)
		{
			MessageBox(plugin.getNppData()._nppHandle,
				_T("Некорректный путь."),
				_T("Настройки"),
				MB_OK);
		}
		else
		{
			RIDEmenu::showMessage(_T("Unknown error: failed to create directory."));
		}
		return error;
	}
}

INT_PTR settingsDlgProc(HWND h_dlg, UINT message, WPARAM w_param, LPARAM l_param)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		// получаем handle для строки-ввода
		HWND h_edit = GetDlgItem(h_dlg, IDC_PATH_EDIT);
		if (!h_edit)
		{
			RIDEmenu::showMessage(_T("Error in onOK(): GetDlgItem() returned NULL."));
			return TRUE;
		}

		LPCTSTR path = plugin.getSettings().getProjectsPath();
		SetWindowText(h_edit, path);
		return TRUE;
	}

	case WM_COMMAND:
		switch (w_param)
		{
		case IDB_OK:
		{
			DWORD error = onOK(h_dlg);
			EndDialog(h_dlg, TRUE);
			if (error != NO_ERROR)
			{
				doModalSettingsDlg();
			}
			return TRUE;
		}
		case IDB_CANCEL:
			EndDialog(h_dlg, TRUE);
			return TRUE;
		}
		break;

	case WM_CLOSE:
		EndDialog(h_dlg, FALSE);
		return TRUE;
	}

	return FALSE;
}

void doModalSettingsDlg()
{
	DialogBox(plugin.getDllModule(),
		MAKEINTRESOURCE(IDD_SETTINGS),
		plugin.getNppData()._nppHandle,
		(DLGPROC)settingsDlgProc);
}
