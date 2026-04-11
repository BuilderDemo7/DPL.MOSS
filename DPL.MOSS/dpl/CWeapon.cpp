#include "CWeapon.h"

void CWeapon::Initialise(CWeaponData* weaponDataPtr, int totalAmmo, bool infiniteClips, int fireCounter)
{
	((void(__thiscall*)(CWeapon*, CWeaponData*, int, bool, int))0x438599)(this, weaponDataPtr, totalAmmo, infiniteClips, fireCounter);
}

void CWeapon::Shoot()
{
	((void(__thiscall*)(CWeapon*))0x525268)(this);
}

void CWeapon::Reload()
{
	((void(__thiscall*)(CWeapon*))0x5253B4)(this);
}

bool CWeapon::IsAutomatic()
{
	return 	((bool(__thiscall*)(CWeapon*))0x525312)(this);
}