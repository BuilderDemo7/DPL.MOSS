#pragma once
#include "CCharacter.h"

class CPlayerDriverBehaviour {
public:
	CCharacter* GetCharacter();
	void AquaticCollisionCheck();

	bool HasShotRecently();
	void AddAllWeapons();
	bool IsFreeAiming();
	void PlayerIsStuck();
};