#pragma once
#include "CLifeEventDataManager.h"
#include "Matrix.h"

class CLifeActor
{
public:
	int GetVTableAddress();

	void Create(); // calls the v-table Create()
	Matrix GetMatrix(); // calls the v-table GetMatrix()
};