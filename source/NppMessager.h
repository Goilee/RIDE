#pragma once


class NppMessager
{
	HWND npp_handle;
public:
	NppMessager(HWND npp_handle);
	~NppMessager();

	void setNppHandle(HWND npp_handle);
	LRESULT sendWMsetText(LPCTSTR title);
	LRESULT sendGetFullCurrentPath(size_t path_len, LPTSTR path);
	LRESULT sendGetCurrentScintilla(int *ptr_sci_id);
	LRESULT sendDoOpen(LPTSTR full_path);
	LRESULT sendCloseAllFiles();
	LRESULT sendGetNumberAllOpenedFiles();
	LRESULT sendSaveAllFiles();
private:
	LRESULT sendNppMessage(UINT message, WPARAM w_param, LPARAM l_param);
};

