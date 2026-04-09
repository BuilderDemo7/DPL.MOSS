#pragma once
#include "Matrix.h"
#include "CLifeActor.h"
#include "Vector4.h"
#include "CLifeInstance_Vehicle.h"

#define VEH_ACTOR_FLAG__RANDOM_TINT			0x20000
#define VEH_ACTOR_FLAG__START_CREATED		0x2000000
#define VEH_ACTOR_FLAG__SPOOL_WITH_MISSION  0x100000

#pragma pack(push, 1)
class CLifeActor_Vehicle : CLifeActor
{
public:
	void CustomInitalise(Matrix matrix, int vehicleType, int tintValue = 1, float initialSpeed = 0.0f, float initialFelony = 0.0f, float impactSoftness = 0.0f, float explosionSoftness = 1.0f, float bulletSoftness = 1.0f, float impactFragility = 1.0f, CLifeActor* attachedVehicle = NULL, bool randomTint = false, bool startCreated = true, bool spoolWithMission = false, CLifeEventData* pEventData = NULL);

	char __padding0[0x8];

	CLifeEventData* m_pOwner;
	void* m_pDataObjects;
	Vector4 m_orientation; // quaternion (MAq)
	Matrix m_initialMatrix; 
	Vector4 m_initialPosition;
	Vector4 m_positionChangePerGameStep;

	char __padding1[0xC];

	CLifeInstance_Vehicle* m_piVehicleInstance;
	float m_fInitialSpeed;
	float m_fInitialFelony;
	int field98;
	float m_fISoftness;
	float m_fESoftness;
	float m_fBSoftness;
	float m_fIFragility;
	int m_iTintValue;
	bool m_bCanSmashStuff;
	char __padding2[0x3]; // bool 32 padding
	int m_iFlags;
	int m_vehicleType;
	CLifeActor* m_pAttachedToActor;
	Vector4 m_pPositionAtStart;
	bool m_bSpoolRequested;
	char __padding3[0x3]; // bool 32 padding

	int m_initialGameStepIndex;
};
#pragma pack(pop)