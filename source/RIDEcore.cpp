#include "stdafx.h"
#include "RIDEcore.h"


RIDEcore::RIDEcore() :
	npp_messager(nullptr),
	sci_messager(nullptr)
{
}

RIDEcore::~RIDEcore()
{
	if (this->sci_messager)
	{
		delete this->sci_messager;
	}
	if (this->npp_messager)
	{
		delete this->npp_messager;
	}
}

void RIDEcore::setNppData(NppData npp_data)
{
	this->npp_data = npp_data;

	if (this->npp_messager == nullptr)
	{
		this->npp_messager = new NppMessager(this->npp_data._nppHandle);
	}
	else
	{
		this->npp_messager->setNppHandle(this->npp_data._nppHandle);
	}

	if (this->sci_messager == nullptr)
	{
		this->sci_messager = new SciMessager(this->npp_messager, this->npp_data._scintillaMainHandle, this->npp_data._scintillaSecondHandle);
	}
	else
	{
		this->sci_messager->setSciHandles(this->npp_data._scintillaMainHandle, this->npp_data._scintillaSecondHandle);
	}
}

NppData RIDEcore::getNppData()
{
	return this->npp_data;
}

LPCTSTR RIDEcore::getPluginName()
{
	return _T("RIDE");
}

HMODULE RIDEcore::getDllModule()
{
	return this->h_dll_module;
}