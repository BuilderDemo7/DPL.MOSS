#pragma once
#include "VehicleModel.h"
#include "Vector4.h"
#include "Vehicle.h"
#include "CLifeActor.h"

class CLifeSystem_SoftSaveVehicle {
public:
	char pad[28];
	CVehicle** pSavedVehicle;
};

class CLifeInstance
{
public:
};

struct LifeInstanceItem
{
	CLifeInstance* m_pItem;

	void* m_pUnknown1;
	void* m_pUnknown2;
};

struct LifeInstancesHolder
{
	LifeInstanceItem m_items[132];
};

class CLifeInstances {
public:
	CLifeSystem_SoftSaveVehicle* GetSSV();
	void CreateVehicle(CVehicle* pVehicle, tVehicleModelUID tVehicle, Vector4* vPosition, float fRotation);

	void AskForInstance(CLifeActor* pActor, bool bCreateOnStart);

	int field0;
	int field4;
	LifeInstancesHolder m_itemsHolder;
};


CLifeInstances* GetLifeInstances();