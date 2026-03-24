#include "CGadgetHandler.h"

CGadgetHandler* CGadgetHandler::GetInstance()
{
	return *(CGadgetHandler**)0x70c7d0;
}

unsigned short CGadgetHandler::GetGadgetModelHandle(EGadgetType gadget)
{
	return ((unsigned short(__thiscall*)(CGadgetHandler*, EGadgetType))0x455c16)(this, gadget);
}