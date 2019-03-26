#pragma once

#include "TString.h"

#define FUNCS_NUMBER 4

class RIDEmenu
{
private:
	RIDEmenu();
public:
	static TString about_text;

	static FuncItem func_items[FUNCS_NUMBER];
	static void aboutBox();
	static void newProject();
	static void settingsDlg();

	// для отладки
	static LRESULT showMessage(LPCTSTR message);
};
