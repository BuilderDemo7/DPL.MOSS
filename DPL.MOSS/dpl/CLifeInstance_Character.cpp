#include "CLifeInstance_Character.h"
#include "CWeaponsStore.h"
#include "CCharacterCategoryManager.h"
#include <iostream>

CLifeInstance_Character::CLifeInstance_Character()
{
	memset(this, 0, sizeof(CLifeInstance_Character));
	((void(__thiscall*)(CLifeInstance_Character*))0x47f97e)(this);
}

void CLifeInstance_Character::CoreCreate() {
	((void(__thiscall*)(CLifeInstance_Character*))0x47f8c3)(this);
}

Vector4 CLifeInstance_Character::position(unsigned int gameStepIndex)
{
	Vector4 returnStorage = Vector4();

	((Vector4*(__thiscall*)(CLifeInstance_Character*, Vector4*, unsigned int))0x47ddb5)(this, &returnStorage, gameStepIndex);
	return returnStorage;
}

Vector4 CLifeInstance_Character::GetPosition()
{
	void* Singleton_Time = *(void**)(0x70c5b0); // CGameTime *
	unsigned int gameStepIndex = *(int*)Singleton_Time + 0x4; // Singleton_Time->m_nGameFrame

	return position(gameStepIndex);
}

// BETA, might crash on some cases..
void CLifeInstance_Character::InitialiseFromCharacter(CCharacter* pCharacter, bool enableSpooling)
{
	if (pCharacter == NULL)
		return;

	Vector4 pos = Vector4();
	pCharacter->GetPosition(&pos);

	CWeapon* wep = pCharacter->GetWeapon();
	if (wep != NULL)
	{
		m_weapon.InfiniteAmmo = wep->InfiniteAmmo;
		m_weapon.CooldownTimer = wep->CooldownTimer;
		m_weapon.pData = wep->pData;
		m_weapon.TotalAmmo = wep->TotalAmmo;
		m_weapon.CooldownTimerTwo = wep->CooldownTimerTwo;
	}
	else
	{
		auto ws = CWeaponsStore::GetInstance();
		if (ws)
		{
			auto ccm = CCharacterCategoryManager::GetInstance();
			int era = ccm->GetEra();

			EWeapons wep = eWeapon70_Revolver;
			if (era != 0)
				wep = eWeapon00_Beretta;

			CWeaponData* data = ws->weaponData(wep);
			if (data != NULL)
			{
				m_weapon = CWeapon();
				m_weapon.Initialise(data, 999, true, 0);
			}
		}
	}

	m_initialPosition = pos;
	m_skin = pCharacter->GetModel();
	*(int*)(this + 0x60) = m_skin;
	*(int*)(this + 0x64) = 0xefcdab0; // ePlayerNumber

	CMovingObject* piObj = (CMovingObject*)(this + 0x14);

	if (!enableSpooling)
		piObj = NULL;

	GetSpoolHandler()->Initialise((CSpoolableMissionObject*)this, piObj, &pos, 0.0f);

	m_piCharacter = pCharacter;
	m_bOwned = true;
	m_bCreated = true;

	//if (enableSpooling)
	//	GetSpoolHandler()->CreateObjects();
}

void CLifeInstance_Character::SetSpoolPosition(Vector4* pos)
{
	// this->m_SpoolHandler->m_ref->list
	//void* spoolHandler = (void*)((int)this + 0xE4);
	//void* spoolHandler_dependencyList = *(void**)((int)spoolHandler + 0x4);
	
	void* spoolHandler_dependencyList = *(void**)((int)this + 0xE8);

	if (spoolHandler_dependencyList == NULL)
		return;

	Vector4* positionalStuff_pos = (Vector4*)((int)spoolHandler_dependencyList + 0xA0);

	positionalStuff_pos->X = pos->X;
	positionalStuff_pos->Y = pos->Y;
	positionalStuff_pos->Z = pos->Z;
	positionalStuff_pos->W = pos->W;
}

CSpoolableMissionObject* CLifeInstance_Character::GetSpoolHandler()
{
	return (CSpoolableMissionObject*)((int)this + 0xE4);
}

void CLifeInstance_Character::Initialise(
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
)
{
	((void(__thiscall*)(
		CLifeInstance_Character*,
		AutoPtr<CLifeInstance_Character, int>*,
		int,
		ECharacterType,
		Matrix *,
		void*,
		int,
		int,
		Vector4*,
		Vector4*,
		Vector4*,
		Matrix*,
		float,
		int,
		Matrix*,
		Matrix*,
		Matrix*,
		CWeapon*,
		void*,
		void*,
		void*,
		int,
		int,
		void*,
		Vector4*,
		Matrix*,
		float
	))0x47e1a6)(
		this, 
		outPtr, 
		playerEnum, 
		characterType, 
		posMatrix, 
		punk, 
		iunk, 
		_iunk, 
		pos, 
		_pos, 
		velocitymaybe, 
		zeroMatrix,
		heading, 
		__iunk,
		_zeroMatrix, 
		__zeroMatrix, 
		___zeroMatrix, 
		weapon,
		_punk,
		__punk,
		___punk,
		___iunk,
		____iunk,
		____punk,
		rotation,
		____zeroMatrix,
		funk
		);
}