#pragma once
#include "CCharacter.h"
#include "Vehicle.h"
#include "Vector4.h"
#include "EWeapons.h"

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

	void Initialise(int inChaseCarCharacterRole, float inChaseCarPatrolDensity, unsigned char inChaseCarMaxChasers, float inChaseCarArmourLevel, AIFelonySystemPatrolCarTypeEnum inPatrolCarType);

	bool AddChaseCarVehicleType(int inVehicleType, bool inIsSecondaryVehicleType);
	bool AddChaseCarWeaponType(EWeapons inWeapon);
};

class AIFelonySystemFelonyManagerClass {
public:
	uint8_t __padding0[0xe64];
	AIFelonySystemPatrolDataClass m_PatrolDataArray[2];
	
	void AddChaseCarVehicleType(int inVehicleType, bool inIsSecondaryVehicleType, AIFelonySystemPatrolCarTypeEnum inPatrolCarType);
	void RemoveChaseCarVehicleType(int inVehicleType, bool inIsSecondaryVehicleType, AIFelonySystemPatrolCarTypeEnum inPatrolCarType);
	//void RemoveAllChaseCarVehicleTypes(bool inIsSecondaryVehicleType, AIFelonySystemPatrolCarTypeEnum inPatrolCarType);
	void AddChaseCarCharacterType(int inCharacterType, AIFelonySystemPatrolCarTypeEnum inPatrolCarType);
	void RemoveChaseCarCharacterType(int inCharacterType, AIFelonySystemPatrolCarTypeEnum inPatrolCarType);

	void AddChaseCarWeaponType(EWeapons inWeapon, AIFelonySystemPatrolCarTypeEnum inPatrolCarType);
	void DeleteAllChaseEntities(AIFelonySystemPatrolCarTypeEnum inPatrolCarType);

	void EnableCops(bool cops);

	void SetChaseCarPatrolDensity(float inChaseCarPatrolDensity, AIFelonySystemPatrolCarTypeEnum inPatrolCarType);

	void SetChaseCarMaxChasers(int inChaseCarMaxChasers, int inPatrolCarType = 0);
	float GetVehicleFelonyLevel(CVehicle* pVehicle, int CarType);
	void SetVehicleFelonyLevel(CVehicle* pVehicle, int CarType, float Value);
	void SetFelonyLevel(CCharacter* pCharacter, int CarType, float Value);
	float GetFelonyLevel(CCharacter* pCharacter, int CarType);
	void CreatePatrolCharacterOnFoot(Vector4* Position, AIFelonySystemPatrolCarTypeEnum CarType, float Angle);
	void CreatePatrolVehicleUnit(Vector4* position, float angle, bool snapToTerrain, bool useSecondaryVehicleType, AIFelonySystemPatrolCarTypeEnum CarType);
	void CreatePatrolHelicopterUnit(Vector4* Position, AIFelonySystemPatrolCarTypeEnum CarType, float Angle);
};

AIFelonySystemFelonyManagerClass* GetFelonyManager();