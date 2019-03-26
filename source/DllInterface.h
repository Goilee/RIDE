#pragma once


class DllInterface
{
protected:
	unsigned int attach_count = 0;
	HMODULE h_dll_module;
public:
	DllInterface();
	virtual ~DllInterface();

	virtual void onDllProcessAttach(HMODULE h_module) = 0;
	virtual void onDllProcessDetach() = 0;
	virtual HMODULE getDllModule() = 0;
};
