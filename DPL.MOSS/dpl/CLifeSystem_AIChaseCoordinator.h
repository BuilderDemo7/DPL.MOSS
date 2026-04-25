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
	uint8_t m_ui8PermittedRoadTypeFlags;
	char __padding1[0x3];

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

class AIChaseTargetClass
{
public:
	CCharacter* m_piTargetCharacter;
	void* m_piTargetMovingObject;

	char __padding0[0x18];

	float m_rAttractionStrength;
	uint8_t m_ui8BehaviourFlags;

	char __padding1[0x8];
};

class AIChaseAntiTargetClass
{
public:
};

class CLife_AITarget
{
public:
	AIChaseTargetClass* GetAIObject();

	int field0;
	AIChaseTargetClass* m_pAITargetObject;
	int field8;
	int fieldC;
};

class CLifeActor_AIChaseTarget : CLife_AITarget
{
public:
};

class CLife_AIAntiTarget
{
public:
};

typedef CLife_AIPursuer* TPursuerPointer;
typedef CLifeActor_AIChaseTarget* TTargetPointer;
typedef CLife_AIAntiTarget* TAntiTargetPointer;

class CLifeSystem_AIChaseCoordinator
{
public:
	static CLifeSystem_AIChaseCoordinator* GetInstance();

	TPursuerPointer GetPursuer(CLifeActor* pActor);
	TTargetPointer GetTargetCharacter(CLifeActor* pActor);
	TAntiTargetPointer GetAntiTarget(CLifeActor* pActor);

	void StartRandomWander(TPursuerPointer pursuerObject);
	void StopRandomWander(TPursuerPointer* pursuerObject);

	void LinkPursuerToTarget(TPursuerPointer pursuerObject, TTargetPointer targetObject);
	void UnlinkPursuerFromTarget(TPursuerPointer* pursuerObject, TTargetPointer* targetObject);

	int field0;
};