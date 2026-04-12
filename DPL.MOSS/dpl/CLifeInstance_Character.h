#pragma once
#include "AutoPtr.h"
#include "ECharacterType.h"
#include "Matrix.h"
#include "Vector4.h"
#include "CWeapon.h"
#include "CCharacter.h"

// size: 0x1f4
class CLifeInstance_Character {
public:
	CLifeInstance_Character();
	void Initialise(
		AutoPtr<CLifeInstance_Character, int>* outPtr,
		int playerEnum,
		ECharacterType characterType,
		Matrix* posMatrix,
		void* punk,
		int iunk,
		int _iunk,
		Vector4* pos,
		Vector4* _pos,
		Vector4* velocitymaybe,
		Matrix* zeroMatrix,
		float heading,
		int __iunk,
		Matrix* _zeroMatrix,
		Matrix* __zeroMatrix,
		Matrix* ___zeroMatrix,
		CWeapon* weapon,
		void* _punk,
		void* __punk,
		void* ___punk,
		int ___iunk,
		int ____iunk,
		void* ____punk,
		Vector4* rotation,
		Matrix* ____zeroMatrix,
		float funk
	);
	void CoreCreate();
public:
	char _pad[0x58];

	CCharacter* m_piCharacter;
};