#pragma once

class Settings
{
private:
	const size_t project_name_max_length = 50;
	LPCTSTR projects_path = _T("C:\\\\RIDE projects\\");
public:
	Settings();
	~Settings();
	LPCTSTR getProjectsPath();
	DWORD setProjectsPath(LPCTSTR projects_path);
};
