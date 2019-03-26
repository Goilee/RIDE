#pragma once

#include "NppPluginInterface.h"
#include "DllInterface.h"
#include "NppMessager.h"
#include "SciMessager.h"

class RIDEcore :
	public NppPluginInterface,
	public DllInterface
{
protected:
	NppData npp_data;
public:
	NppMessager *npp_messager;
	SciMessager *sci_messager;

	RIDEcore();
	virtual ~RIDEcore();

	void setNppData(NppData npp_data);
	NppData getNppData();
	LPCTSTR getPluginName();
	HMODULE getDllModule();
};

