#include "CLifeActor_Vehicle.h"
#include "Vehicle.h"
#include "MathFuncs.h"
#include "SpoolableResourceManager.h"

void CLifeActor_Vehicle::CustomInitalise(Matrix matrix, int vehicleType, int tintValue, float initialSpeed, float initialFelony, float impactSoftness, float explosionSoftness, float bulletSoftness, float impactFragility, CLifeActor* attachedVehicle, bool randomTint, bool startCreated, bool spoolWithMission, CLifeEventData* pEventData)
{
	CLifeEventData* pActualEventData = pEventData;

	if (pActualEventData == NULL)
	{
		AutoPtr<CLifeEventData, int> data = CLifeEventDataManager::GetInstance()->GetLifeEventData(0);

		// 'data' only stored once in the stack, also we have to do this 
		pActualEventData = data.m_pPointer;
	}
	
	// generate flags for the other functions in the v-table
	m_iFlags = (randomTint ? VEH_ACTOR_FLAG__RANDOM_TINT : 0) | (startCreated ? VEH_ACTOR_FLAG__START_CREATED : 0) | (spoolWithMission ? VEH_ACTOR_FLAG__SPOOL_WITH_MISSION : 0);

	m_vehicleType = vehicleType;
	m_iTintValue = tintValue;

	if (randomTint)
	{
		// int r = Singleton_LifeSystemRandom->GetRandom();
		int r = ((int(__thiscall*)(void*))0x403a97)(*(void**)(0x70c7dc));
		m_iTintValue = r % 15;
	}

	m_pOwner = pActualEventData;
	m_initialMatrix = matrix;

	m_piVehicleInstance = NULL;
	void* Singleton_Time = *(void**)(0x70c5b0); // CGameTime *
	m_initialGameStepIndex = *(int*)Singleton_Time + 0x4; // Singleton_Time->m_nGameFrame
	m_positionChangePerGameStep = Vector4(0, 0, 0, 0);

	m_initialPosition = Vector4(matrix.pos.X, matrix.pos.Y, matrix.pos.Z, 1);

	m_orientation = math_construct_quaternion(&m_initialMatrix);

	m_pPositionAtStart = m_initialPosition;

	if (startCreated)
	{
		auto srm = SpoolableResourceManager::GetInstance();
		if (srm != NULL)
		{
			Vector v2Pos; // MAv2
			v2Pos.X = m_initialPosition.X;
			v2Pos.Y = m_initialPosition.Z;
			srm->RequestEntity(SpooledPackageType_Vehicles, m_vehicleType, (int)&v2Pos, ESpoolPriority_Required);
			this->m_bSpoolRequested = true;
		}

		//((CLifeActor*)this)->Create();
	}
	else {
		this->m_bSpoolRequested = false;
	}
}