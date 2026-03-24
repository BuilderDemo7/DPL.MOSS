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