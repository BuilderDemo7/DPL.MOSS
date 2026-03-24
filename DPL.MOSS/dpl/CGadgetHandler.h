#pragma once
#include "EGadgetType.h"

class CGadgetHandler
{
public:
	unsigned short GetGadgetModelHandle(EGadgetType gadget);
	static CGadgetHandler* GetInstance();
};

