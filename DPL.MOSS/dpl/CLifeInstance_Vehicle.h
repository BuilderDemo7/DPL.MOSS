#pragma once
#include "AutoPtr.h"
#include "Matrix.h"
#include "Vector4.h"
#include "Vehicle.h"
#include "CSpoolableMissionObject.h"

class CLifeInstance_Vehicle
{
public:
	char __padding0[0x70];
	CVehicle* m_piVehicle;

	void SetMustangHandling(bool bOn);

	Vector4 position(unsigned int gameStepIndex);
	Vector4 GetPosition();

	void SetSpoolPosition(Vector4* pos);

	CSpoolableMissionObject* GetSpoolHandler();

	// vtable + 0x9c -> position()
};