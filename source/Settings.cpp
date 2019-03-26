#include "stdafx.h"
#include "Settings.h"
#include "RIDEmenu.h"
#include "TString.h"

Settings::Settings()
{
}


Settings::~Settings()
{
}

LPCTSTR Settings::getProjectsPath()
{
	return this->projects_path;
}

DWORD Settings::setProjectsPath(LPCTSTR c_path)
{
	TString path(c_path);
	size_t pos = path.find('\\');
	while (pos != TString::npos)
	{
		CreateDirectory(path.substr(0, pos + 1).c_str(), NULL);
		pos = path.find('\\', pos + 1);
	}
	if (CreateDirectory(c_path, NULL) == 0 && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		return GetLastError();
	}
	this->projects_path = projects_path;
	return NO_ERROR;
}
