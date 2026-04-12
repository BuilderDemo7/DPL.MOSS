#include "CLifeSystem.h"

CLifePlayer* CLifeSystem::GetPlayer()
{
    return pPlayer;
}

CLifeSystem* CLifeSystem::GetInstance()
{
    return *(CLifeSystem**)0x70C7C4;
}

void CLifeSystem::SetPopulationDensity(int type, float value)
{
	((void(__thiscall*)(CLifeSystem*, int, float))0x471bff)(this, type, value);
}

void CLifeSystem::RegisterPlayerActor(CLifeActor* pActor)
{
	((void(__thiscall*)(CLifeSystem*, CLifeActor*))0x47199f)(this, pActor);
}

void CLifeSystem::SetSpoolCentre(float x, float z)
{
	((void(__thiscall*)(CLifeSystem*, float, float))0x473029)(this, x, z);
}