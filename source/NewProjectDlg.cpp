#include "stdafx.h"
#include "NewProjectDlg.h"
#include "RIDEmenu.h"
#include "RIDEmain.h"
#include "resource.h"
#include "TString.h"

#define PROJECT_NAME_MAX_LENGTH 50

extern RIDEmain plugin;

#define GETDLGITEM_NULL 1
#define MESSAGE_BOX_TITLE _T("Создание нового окна")

namespace
{
	DWORD onOK(HWND h_dlg)
	{
		// получаем handle для строки-ввода
		HWND h_edit = GetDlgItem(h_dlg, IDC_EDIT);
		if (!h_edit)
		{
			RIDEmenu::showMessage(_T("Error in onOK(): GetDlgItem() returned NULL."));
			return GETDLGITEM_NULL;
		}

		// считываем из строки текст
		TCHAR text[PROJECT_NAME_MAX_LENGTH];
		GetWindowText(h_edit, text, PROJECT_NAME_MAX_LENGTH);

		// создаем папку
		TString dir_path(plugin.getSettings().getProjectsPath());
		dir_path += text;

		// создаем папку
		if (!CreateDirectory(dir_path.c_str(), NULL))
		{
			DWORD error = GetLastError();
			switch (error)
			{
			case ERROR_ALREADY_EXISTS:
				MessageBox(plugin.getNppData()._nppHandle,
					_T("Проект с таким именем уже существует."),
					MESSAGE_BOX_TITLE,
					MB_OK);
				break;
			case ERROR_PATH_NOT_FOUND:
				RIDEmenu::showMessage(_T("Error in onOk(): path not found."));
				break;
			default:
				RIDEmenu::showMessage(_T("Error in onOk(): CreateDirectory() returned 0."));
				break;
			}
			return error;
		}

		// создаем файл main.rcs
		TString file_path(dir_path + _T("\\main.rcs"));
		HANDLE h_file = CreateFile(file_path.c_str(), NULL, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h_file == INVALID_HANDLE_VALUE)
		{
			DWORD error = GetLastError();
			switch (error)
			{
			case ERROR_FILE_EXISTS:
				RIDEmenu::showMessage(_T("Error in onOK(): file \'main.rcs\' already exists."));
				break;
			default:
				RIDEmenu::showMessage(_T("Error in onOk(): CreateFile() returned INVALID_HANDLE_VALUE."));
				break;
			}
			return error;
		}
		else
		{
			CloseHandle(h_file);
		}

		// TODO починить эту ветку
		// если открыт файл без имени, NPP предложит выбрать путь сохранения
		// пользователь может нажать "отмена" и файл не сохранится
		// тогда при закрытии NPP еще раз предложит сохранить (плохо!)
		// если пользователь снова нажмет "отмена", то файл просто не закроется (плохо!)
		//
		// предупреждаем пользователя о закрытии файлов
		int button_pressed = MessageBox(plugin.getNppData()._nppHandle,
			_T("Сохранить и закрыть все открытые файлы?"),
			MESSAGE_BOX_TITLE,
			MB_OKCANCEL | MB_ICONWARNING);
		switch (button_pressed)
		{
		case IDOK:
			plugin.npp_messager->sendSaveAllFiles();
			plugin.npp_messager->sendCloseAllFiles();
			plugin.npp_messager->sendDoOpen((LPTSTR)file_path.c_str());
			break;
		case IDCANCEL:
			// отменяем изменения
			DeleteFile(file_path.c_str());
			RemoveDirectory(dir_path.c_str());
			break;
		}
		return NO_ERROR;
	}
}

INT_PTR newProjectDlgProc(HWND h_dlg, UINT message, WPARAM w_param, LPARAM l_param)
{
	switch (message)
	{
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (w_param)
		{
		case IDB_OK:
		{
			DWORD error = onOK(h_dlg);
			EndDialog(h_dlg, TRUE);
			if (error)
			{
				doModalNewProjectDlg();
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

void doModalNewProjectDlg()
{
	DialogBox(plugin.getDllModule(),
		MAKEINTRESOURCE(IDD_NEWPROJECT),
		plugin.getNppData()._nppHandle,
		(DLGPROC)newProjectDlgProc);
}
