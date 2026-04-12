#pragma once
#include "CWeapon.h"
#include "EWeapons.h"

class CWeaponsStore
{
public:
	static CWeaponsStore* GetInstance();

	CWeaponData* weaponData(EWeapons weapon);
};