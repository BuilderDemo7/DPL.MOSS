#pragma once
#include "CCharacter.h"
#include "Vehicle.h"
#include "Vector4.h"

enum AIFelonySystemPatrolCarTypeEnum {
	E_PATROLCARTYPE_COP = 0,
	E_PATROLCARTYPE_GOON = 1,
	E_PATROLCARTYPE_NUM_OF = 2,
	E_PATROLCARTYPE_NONE = 3
};

class CVehicle;
class CCharacter;

class AIFelonySystemPatrolDataClass
{
public:
	uint8_t __placeholder[0x3b4];
	bool AddChaseCarVehicleType(int inVehicleType, bool inIsSecondaryVehicleType);
};

class AIFelonySystemFelonyManagerClass {
public:
	uint8_t __padding0[0xe63];
	AIFelonySystemPatrolDataClass m_PatrolDataArray[2];
	
	void SetChaseCarMaxChasers(int inChaseCarMaxChasers, int inPatrolCarType = 0);
	void SetVehicleFelonyLevel(CVehicle* pVehicle, int CarType, float Value);
	void SetFelonyLevel(CCharacter* pCharacter, int CarType, float Value);
	float GetFelonyLevel(CCharacter* pCharacter, int CarType);
	void CreatePatrolCharacterOnFoot(Vector4* Position, AIFelonySystemPatrolCarTypeEnum CarType, float Angle);
	void CreatePatrolVehicleUnit(Vector4* position, float angle, bool snapToTerrain, bool useSecondaryVehicleType, AIFelonySystemPatrolCarTypeEnum CarType);
	void CreatePatrolHelicopterUnit(Vector4* Position, AIFelonySystemPatrolCarTypeEnum CarType, float Angle);
};

AIFelonySystemFelonyManagerClass* GetFelonyManager();