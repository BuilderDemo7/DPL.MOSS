#include "CGadgetHandler.h"

CGadgetHandler* CGadgetHandler::GetInstance()
{
	return *(CGadgetHandler**)0x70c7d0;
}

unsigned short CGadgetHandler::GetGadgetModelHandle(EGadgetType gadget)
{
	unsigned int returnStorage = 0;

	return *((unsigned short*(__thiscall*)(CGadgetHandler*, unsigned int*, EGadgetType))0x455c16)(this, &returnStorage, gadget);
}