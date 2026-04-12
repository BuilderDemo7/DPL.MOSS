#pragma once
#include "EWeapons.h"
#include "EGadgetType.h"

// size: 0x30
struct CWeaponData {
	EWeapons WeaponType;
	EGadgetType ModelID;
	int AmmoSize[2];
	int field16;
	int field20;
	float Range;
	float RateOfFire;
	bool  Automatic;
	char  pad[3];
	int   field36;
	float Spread;
	int   MaxAmmo;

};

class CWeapon {
public:
	void* vTable;
	CWeaponData* pData;
	int	  TotalAmmo;
	int   CurrentAmmo;
	int   InfiniteAmmo;
	int   CooldownTimer;
	int   CooldownTimerTwo;

	void Initialise(CWeaponData* weaponDataPtr, int totalAmmo, bool infiniteClips, int fireCounter);

	void Shoot();
	void Reload();

	bool IsAutomatic();
};