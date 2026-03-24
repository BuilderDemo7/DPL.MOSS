#pragma once
#include "AutoPtr.h"
#include "CWeapon.h"
#include "CCharacter.h"
#include "Vector4.h"
#include "EAnimStates.h"
#include "ECharacterRoles.h"
#include "ECharacterType.h"

class CCharacterManager {
public:
	static CCharacterManager* GetInstance();
	CCharacter* CreateCharacter(AutoPtr<CCharacter, int>* outChar, ECharacterType eType, Vector4* v4Position, float fHeading,
		EnumAnimCondition eAnimCondition, ECharacterRoles eRole, Vector4* velocity, bool strafe,
		AutoPtr<CWeapon, int> weaponPtr, Vector4* targetPosition, bool crouch, float health);
	void FreeCharacter(AutoPtr<CCharacter, int>* characterPtr);
	int GetFreeCharacterCount();
	// no idea what this does or if it's correct
	void CharacterSetNoFelon(CCharacter* character, int unk);
};