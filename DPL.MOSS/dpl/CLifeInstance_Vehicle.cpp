#include "CLifeInstance_Vehicle.h"

void CLifeInstance_Vehicle::SetMustangHandling(bool bOn)
{
	((void(__thiscall*)(CLifeInstance_Vehicle*, bool))0x480730)(this, bOn);
}

Vector4 CLifeInstance_Vehicle::position(unsigned int gameStepIndex)
{
	Vector4 returnStorage = Vector4();

	((Vector4*(__thiscall*)(CLifeInstance_Vehicle*, Vector4*, unsigned int))0x48041c)(this, &returnStorage, gameStepIndex);
	return returnStorage;
}

Vector4 CLifeInstance_Vehicle::GetPosition()
{
	void* Singleton_Time = *(void**)(0x70c5b0); // CGameTime *
	unsigned int gameStepIndex = *(int*)Singleton_Time + 0x4; // Singleton_Time->m_nGameFrame

	return position(gameStepIndex);
}

void CLifeInstance_Vehicle::SetSpoolPosition(Vector4* pos)
{
	// this->m_SpoolHandler->m_ref->list
	//void* spoolHandler = (void*)((int)this + 0x5C);
	//void* spoolHandler_dependencyList = *(void**)((int)spoolHandler + 0x4);

	void* spoolHandler_dependencyList = *(void**)((int)this + 0x60);

	if (spoolHandler_dependencyList == NULL)
		return;

	Vector4* positionalStuff_pos = (Vector4*)((int)spoolHandler_dependencyList + 0xA0);

	positionalStuff_pos->X = pos->X;
	positionalStuff_pos->Y = pos->Y;
	positionalStuff_pos->Z = pos->Z;
	positionalStuff_pos->W = pos->W;
}

CSpoolableMissionObject* CLifeInstance_Vehicle::GetSpoolHandler()
{
	return (CSpoolableMissionObject*)((int)this + 0x5C);
}