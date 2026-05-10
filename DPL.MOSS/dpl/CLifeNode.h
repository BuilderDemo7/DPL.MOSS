#pragma once
#include "eNodeFireWire.h"

class CLifeNode
{
public:
	int GetVTableAddress();

	void OnEnable(bool* enabled, eNodeFireWire* wireToFire); // calls vtable func
	//void OnEnable(); // calls vtable func
	void OnDisable(); // calls vtable func

	bool IsEnabled();

	void OnUpdate(bool* enabled, eNodeFireWire* wireToFire);
};