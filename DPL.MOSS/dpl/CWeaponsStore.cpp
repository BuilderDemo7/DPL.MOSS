#include "CWeaponsStore.h"

CWeaponsStore* CWeaponsStore::GetInstance()
{
	return *(CWeaponsStore**)0x70c6c4;
}

CWeaponData* CWeaponsStore::weaponData(EWeapons weapon)
{
	return ((CWeaponData*(__thiscall*)(CWeaponsStore*, EWeapons))0x525055)(this, weapon);
}