#pragma once
#include "CLifeActor.h"
#include "CCharacter.h"
#include "eCheatSettings.h"

#pragma pack(push, 1)
class AIChasePursuerClass
{
public:
	CCharacter* m_piPursuerCharacter;
	void* m_piPursuerVirtualVehicle;
	void* m_piPursuerHelicopter;
	int ePursuerType;
	int eChaseCarType;
	int m_ePursuerStatus;
	bool m_bCanChase;
	bool m_bAtTarget;
	bool m_bDriveAsCiv;

	char __padding0[0x9];

	float m_rDesiredChaseSpeed;
	float m_rDesiredChaseDistance;

	char __padding1[0x4];

	float m_rAccelerationMultiplier;
	float m_rTractionMultiplier;
	float m_rHOGMultiplier;
	eCheatSettings m_eCheatSettings;
};
#pragma pack(pop)

class CLife_AIPursuer
{
public:
	void* vtable;
	int field0x4;
	AIChasePursuerClass* m_pPursuer;
	int field0xC;
};

typedef CLife_AIPursuer* TPursuerPointer;

class CLifeSystem_AIChaseCoordinator
{
public:
	static CLifeSystem_AIChaseCoordinator* GetInstance();

	TPursuerPointer GetPursuer(CLifeActor* pActor);
	void StartRandomWander(TPursuerPointer pursuerObject);
	void StopRandomWander(TPursuerPointer* pursuerObject);
};