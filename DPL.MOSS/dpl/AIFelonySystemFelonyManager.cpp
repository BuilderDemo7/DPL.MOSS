#include "AIFelonySystemFelonyManager.h"

AIFelonySystemFelonyManagerClass* GetFelonyManager()
{
    return *(AIFelonySystemFelonyManagerClass**)(0x70C5C8);
}

/*
void __thiscall
SetChaseCarMaxChasers__32AIFelonySystemFelonyManagerClassUc31AIFelonySystemPatrolCarTypeEnum
		  (AIFelonySystemFelonyManagerClass *this,uint8 inChaseCarMaxChasers,int inPatrolCarType)
*/
void AIFelonySystemFelonyManagerClass::SetChaseCarMaxChasers(int inChaseCarMaxChasers, int inPatrolCarType)
{
	((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, int, int))0x430783)(this, inChaseCarMaxChasers, inPatrolCarType);
}

float AIFelonySystemFelonyManagerClass::GetVehicleFelonyLevel(CVehicle* pVehicle, int CarType)
{
	return ((float(__thiscall*)(AIFelonySystemFelonyManagerClass*, CVehicle*, int CarType))0x430bce)(this, pVehicle, CarType);
}

void AIFelonySystemFelonyManagerClass::SetVehicleFelonyLevel(CVehicle* pVehicle, int CarType, float Value)
{
    ((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, CVehicle*, float, int))0x430FF9)(this, pVehicle, Value, CarType);
}

void AIFelonySystemFelonyManagerClass::SetFelonyLevel(CCharacter* pCharacter, int CarType, float Value)
{
    ((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, CCharacter*, float, int))0x430A18)(this, pCharacter, Value, CarType);
}

float AIFelonySystemFelonyManagerClass::GetFelonyLevel(CCharacter* pCharacter, int CarType)
{
	return ((float(__thiscall*)(AIFelonySystemFelonyManagerClass*, CCharacter*, int))0x4309E1)(this, pCharacter, CarType);
}

void AIFelonySystemFelonyManagerClass::AddChaseCarVehicleType(int inVehicleType, bool inIsSecondaryVehicleType, AIFelonySystemPatrolCarTypeEnum inPatrolCarType)
{
	((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, int, bool, AIFelonySystemPatrolCarTypeEnum))0x430e8f)(this, inVehicleType, inIsSecondaryVehicleType, inPatrolCarType);
}

void AIFelonySystemFelonyManagerClass::AddChaseCarWeaponType(EWeapons inWeapon, AIFelonySystemPatrolCarTypeEnum inPatrolCarType)
{
	m_PatrolDataArray[inPatrolCarType].AddChaseCarWeaponType(inWeapon);
}

void AIFelonySystemFelonyManagerClass::EnableCops(bool cops)
{
	((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, bool))0x4307da)(this, cops);
}

void AIFelonySystemFelonyManagerClass::SetChaseCarPatrolDensity(float inChaseCarPatrolDensity, AIFelonySystemPatrolCarTypeEnum inPatrolCarType)
{
	((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, float, AIFelonySystemPatrolCarTypeEnum))0x43074e)(this, inChaseCarPatrolDensity, inPatrolCarType);
}

void AIFelonySystemFelonyManagerClass::DeleteAllChaseEntities(AIFelonySystemPatrolCarTypeEnum inPatrolCarType)
{
	((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, AIFelonySystemPatrolCarTypeEnum))0x429a07)(this, inPatrolCarType);
}

void AIFelonySystemFelonyManagerClass::AddChaseCarCharacterType(int inCharacterType, AIFelonySystemPatrolCarTypeEnum inPatrolCarType)
{
	((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, int, AIFelonySystemPatrolCarTypeEnum))0x430eb0)(this, inCharacterType, inPatrolCarType);
}

void AIFelonySystemFelonyManagerClass::RemoveChaseCarCharacterType(int inCharacterType, AIFelonySystemPatrolCarTypeEnum inPatrolCarType)
{
	((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, int, AIFelonySystemPatrolCarTypeEnum))0x43116c)(this, inCharacterType, inPatrolCarType);
}

void AIFelonySystemFelonyManagerClass::RemoveChaseCarVehicleType(int inVehicleType, bool inIsSecondaryVehicleType, AIFelonySystemPatrolCarTypeEnum inPatrolCarType)
{
	((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, int, bool, AIFelonySystemPatrolCarTypeEnum))0x4310d5)(this, inVehicleType, inIsSecondaryVehicleType, inPatrolCarType);
}

void AIFelonySystemFelonyManagerClass::CreatePatrolCharacterOnFoot(Vector4* Position, AIFelonySystemPatrolCarTypeEnum CarType, float Angle)
{
    ((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, Vector4*, float, AIFelonySystemPatrolCarTypeEnum))0x429949)(this, Position, Angle, CarType);
}

void AIFelonySystemFelonyManagerClass::CreatePatrolVehicleUnit(Vector4* position, float angle, bool snapToTerrain, bool useSecondaryVehicleType, AIFelonySystemPatrolCarTypeEnum CarType)
{
	((void(__thiscall*)(AIFelonySystemFelonyManagerClass*, Vector4*, float, bool, bool, AIFelonySystemPatrolCarTypeEnum))0x429973)(this, position, angle, snapToTerrain, useSecondaryVehicleType, CarType);
}

void AIFelonySystemFelonyManagerClass::CreatePatrolHelicopterUnit(Vector4* Position, AIFelonySystemPatrolCarTypeEnum CarType, float Angle)
{
    ((void(__thiscall*)(AIFelonySystemFelonyManagerClass*,Vector4*, float, AIFelonySystemPatrolCarTypeEnum))0x4299A3)(this, Position, Angle, CarType);
}


bool AIFelonySystemPatrolDataClass::AddChaseCarVehicleType(int inVehicleType, bool inIsSecondaryVehicleType)
{
	return ((bool(__thiscall*)(AIFelonySystemPatrolDataClass*, int, bool))0x43054d)(this, inVehicleType, inIsSecondaryVehicleType);
}

bool AIFelonySystemPatrolDataClass::AddChaseCarWeaponType(EWeapons inWeapon)
{
	return ((bool(__thiscall*)(AIFelonySystemPatrolDataClass*, EWeapons))0x43052b)(this, inWeapon);
}

void AIFelonySystemPatrolDataClass::Initialise(int inChaseCarCharacterRole, float inChaseCarPatrolDensity, unsigned char inChaseCarMaxChasers, float inChaseCarArmourLevel, AIFelonySystemPatrolCarTypeEnum inPatrolCarType)
{
	((void(__thiscall*)(AIFelonySystemPatrolDataClass*, int, float, unsigned char, float, AIFelonySystemPatrolCarTypeEnum))0x43052b)(this, inChaseCarCharacterRole, inChaseCarPatrolDensity, inChaseCarMaxChasers, inChaseCarArmourLevel, inPatrolCarType);
}