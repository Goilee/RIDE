#pragma once


class NppPluginInterface
{
public:
	NppPluginInterface();
	virtual ~NppPluginInterface();

	virtual void setNppData(NppData) = 0;
	virtual LPCTSTR getPluginName() = 0;
	virtual FuncItem* getFuncsArray(int *ptr_funcs_number) = 0;
	virtual void beNotified(SCNotification *ptr_notification) = 0;
	virtual LRESULT messageProc(UINT message, WPARAM w_param, LPARAM l_param) = 0;
};
