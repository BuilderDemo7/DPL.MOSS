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