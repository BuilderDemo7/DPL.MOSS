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