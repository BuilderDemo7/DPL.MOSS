#pragma once
#include "AutoPtr.h"
#include "ECharacterType.h"
#include "Matrix.h"
#include "Vector4.h"
#include "CWeapon.h"
#include "CCharacter.h"

#include "CLifePlayer.h"
#include "CSpoolableMissionObject.h"

class CLifeInstance_Vehicle;
class CLifeActor_Character;

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

	Vector4 position(unsigned int gameStepIndex);
	Vector4 GetPosition();

	void SetSpoolPosition(Vector4* pos);

	CSpoolableMissionObject* GetSpoolHandler();

public:
	char _pad[0x58];

	CCharacter* m_piCharacter;
	CLifePlayer* m_piPlayer;

	char _pad1[0xA4];

	Vector4 m_initialPosition;
	Vector4 m_positionChangePerGameStep;
	bool m_constrainPositionChange;

	char _pad2[0x13];

	float m_initialHeading;
	float m_headingChangePerGameStep;
	bool m_crouch;
	bool m_cowerIfCrouched;
	bool m_strafeAndWeaponDrawn;

	char _pad3;

	CWeapon m_weapon;
	bool m_shootIfWeaponDrawn;
	bool m_melee;
	bool m_weaponDrawn;

	char _pad4;

	float m_inaccuracy;
	CLifeInstance_Vehicle* m_vehiclePtr;
	int m_vehicleDoor;
	CLifeActor_Character* m_syncVehicleInfoPlayerActorPtr;
	Vector4 m_targetPosition;
	bool m_arrested;

	char _pad5[0x3]; // bool32 padding

	float m_health;
	short m_skin;

	char _pad6[0x2]; // short32 padding

	// vtable + 0xa8 -> position()
};