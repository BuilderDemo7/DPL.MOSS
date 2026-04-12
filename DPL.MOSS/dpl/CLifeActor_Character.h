#pragma once
#include "Matrix.h"
#include "CLifeActor.h"
#include "Vector4.h"
#include "CLifeInstance_Character.h"
#include "CLifeActor_Vehicle.h"
#include "CWeaponsStore.h"

#include "ECharacterRoles.h"
#include "EVehicleDoor.h"
#include "ECharacterType.h"

#pragma pack(push, 1)
class CLifeActor_Character : CLifeActor
{
public:
	void CustomInitialise(ECharacterType skin, Matrix matrix, EWeapons weapon = eWeapon70_Revolver, float initialHealth = 1.0f, float felony = 0.0f, CLifeActor_Vehicle* initialVehicle = NULL, int initialVehicleSeat = 0, bool createFromStart = true, bool addToFelonyManager = false, bool doNotUseIdleAnims = false, bool isPlayer = false, CLifeEventData* pEventData = NULL);
	
	Vector4 position(unsigned int gameStepIndex);
	Vector4 GetPosition();

	void* vtable;

	void* m_pEntity; // ILifeEntity

	int field8;

	CWeapon m_weapon;

	char __padding1[0x8];

	Matrix m_matrix;
	float m_spoolPosX;
	float m_spoolPosY;
	Vector4 m_initialPosition;
	Vector4 m_positionChangePerGameStep;
	Vector4 m_targetPosition;

	char __padding2[0x8];

	CLifeEventData* m_pOwner;

	char __padding3[0x4B0];

	CLifeInstance_Character* m_piCharacterInstance;
	CLifeActor_Vehicle* m_vehiclePtr;

	int m_originalSeat;
	int m_skin;
	int m_stepsSincelastFired;
	int m_initialGameStepIndex;

	int m_ePlayerNumber;
	ECharacterRoles m_eRole;
	EVehicleDoor m_vehicleDoor;
	float m_fVulnerability;
	float m_fFelony;
	float m_initialHeading;
	float m_headingChangePerGameStep;
	float m_targetInaccuracy;
	float m_health;

	bool m_skinOK;
	bool m_bPlayer;
	bool m_bAddToFelonyManager;
	bool m_bCreateFromStart;
	bool m_bDoNotUseIdleAnims;
	bool m_constrainPositionChange;
	bool m_crouch;
	bool m_cowerIfCrouched;
	bool m_strafeAndWeaponDrawn;
	bool m_shootIfWeaponDrawn;
	bool m_melee;
	bool m_weaponDrawn;
	bool m_arrested;

	char __padding4[0x3]; // bool32 padding

	int field0x5b0;
	int field0x5b4;
};
#pragma pack(pop)