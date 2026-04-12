#pragma once
#include "CLifeSystem_AIChaseCoordinator.h"

CLifeSystem_AIChaseCoordinator* CLifeSystem_AIChaseCoordinator::GetInstance()
{
	return *(CLifeSystem_AIChaseCoordinator**)0x70c7c0;
}

TPursuerPointer CLifeSystem_AIChaseCoordinator::GetPursuer(CLifeActor* pActor)
{
	return ((TPursuerPointer(__thiscall*)(CLifeSystem_AIChaseCoordinator*, CLifeActor*))0x4a4cd4)(this, pActor);
}

void CLifeSystem_AIChaseCoordinator::StartRandomWander(TPursuerPointer pursuerObject)
{
	((void(__thiscall*)(CLifeSystem_AIChaseCoordinator*, TPursuerPointer))0x4a4f6c)(this, pursuerObject);
}

void CLifeSystem_AIChaseCoordinator::StopRandomWander(TPursuerPointer* pursuerObject)
{
	((void(__thiscall*)(CLifeSystem_AIChaseCoordinator*, TPursuerPointer*))0x4a51b3)(this, pursuerObject);
}