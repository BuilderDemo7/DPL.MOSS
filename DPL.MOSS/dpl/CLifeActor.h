#pragma once
#include "CLifeEventDataManager.h"
#include "Matrix.h"
#include "Factory.h"
#include "CSpoolableMissionObject.h"

class CLifeActor
{
public:
	int GetVTableAddress();

	CSpoolableMissionObject* CreateInstance(); // calls the v-table CreateInstance()
	void Create(); // calls the v-table Create()
	void Delete(); // calls the v-table Delete()
	EFactoryType hamsterFactoryType(); 
	Matrix GetMatrix(); // calls the v-table GetMatrix()
};