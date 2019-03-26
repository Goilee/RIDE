#include "stdafx.h"
#include "TString.h"
#include "RIDEmenu.h"
#include "RIDEmain.h"
#include "NewProjectDlg.h"
#include "SettingsDlg.h"
#include "resource.h"


extern RIDEmain plugin;

TString RIDEmenu::about_text = _T("- Меняет \"Notepad++\" на \"RIDE\" в заголовке окна.\n") \
_T("- Кнопка \"Создать проект\" создает папку проекта и файл main.rcs.") \
_T("При этом криво спрашивает о сохранении открытых файлов - есть возможность не закрыть их.\n") \
_T("- Кнопка \"Настройки\" открывает окно редактирования параметров.\n") \
_T("\n") \
_T("TODO:\n") \
_T("- Кнопка \"Новый файл\" для создания файла в папке проекта. Должна быть видна только при работе с проектом.\n") \
_T("- Кнопка \"Вызывать препроцессор\" для обработки файлов проекта перед отдачей транслятору.\n") \
_T("- Кнопка \"Вызвать транслятор\".\n") \
_T("- Вывести все кнопки на тулбар.\n") \
_T("- Дерево файлов проекта.\n") \
_T("- Автодополнение.");

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
		_T("Что делает RIDE"),
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
	return MessageBox(plugin.getNppData()._nppHandle, message, _T("Отладочная информация"), MB_OK);
}
