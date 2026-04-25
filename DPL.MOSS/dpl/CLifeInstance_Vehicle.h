#pragma once
#include "AutoPtr.h"
#include "Matrix.h"
#include "Vector4.h"
#include "Vehicle.h"

class CLifeInstance_Vehicle
{
public:
	char __padding0[0x70];
	CVehicle* m_piVehicle;

	void SetMustangHandling(bool bOn);

	Vector4 position(unsigned int gameStepIndex);
	Vector4 GetPosition();

	// vtable + 0x9c -> position()
};