#pragma once
#include "CLifeSystem_AIChaseCoordinator.h"

CLifeSystem_AIChaseCoordinator* CLifeSystem_AIChaseCoordinator::GetInstance()
{
	return *(CLifeSystem_AIChaseCoordinator**)0x70c7c0;
}

TPursuerPointer CLifeSystem_AIChaseCoordinator::GetPursuer(CLifeActor* pActor)
{
	TPursuerPointer returnStorage = NULL;

	((TPursuerPointer(__thiscall*)(CLifeSystem_AIChaseCoordinator*, TPursuerPointer*, CLifeActor*))0x4a4cd4)(this, &returnStorage, pActor);

	return returnStorage;
}

TTargetPointer CLifeSystem_AIChaseCoordinator::GetTargetCharacter(CLifeActor* pActor)
{
	TTargetPointer returnStorage = NULL;

	((TTargetPointer*(__thiscall*)(CLifeSystem_AIChaseCoordinator*, TTargetPointer*, CLifeActor*))0x4a4d4c)(this, &returnStorage, pActor);

	return returnStorage;
}

void CLifeSystem_AIChaseCoordinator::StartRandomWander(TPursuerPointer pursuerObject)
{
	((void(__thiscall*)(CLifeSystem_AIChaseCoordinator*, TPursuerPointer))0x4a4f6c)(this, pursuerObject);
}

void CLifeSystem_AIChaseCoordinator::StopRandomWander(TPursuerPointer* pursuerObject)
{
	((void(__thiscall*)(CLifeSystem_AIChaseCoordinator*, TPursuerPointer*))0x4a51b3)(this, pursuerObject);
}

void CLifeSystem_AIChaseCoordinator::LinkPursuerToTarget(TPursuerPointer pursuerObject, TTargetPointer targetObject)
{
	((void(__thiscall*)(CLifeSystem_AIChaseCoordinator*, TPursuerPointer, TTargetPointer))0x4a4e69)(this, pursuerObject, targetObject);
}

void CLifeSystem_AIChaseCoordinator::UnlinkPursuerFromTarget(TPursuerPointer* pursuerObject, TTargetPointer* targetObject)
{
	((void(__thiscall*)(CLifeSystem_AIChaseCoordinator*, TPursuerPointer*, TTargetPointer*))0x4a51f2)(this, pursuerObject, targetObject);
}

AIChaseTargetClass* CLife_AITarget::GetAIObject()
{
	return m_pAITargetObject;

	//AIChaseTargetClass* returnStorage = NULL;

	//((AIChaseTargetClass*(__thiscall*)(CLife_AITarget*, AIChaseTargetClass**))0x4a55ae)(this, &returnStorage);

	//return returnStorage;
}