#include "AIManager.h"

AIManager* AIManager::GetInstance()
{
	return ((AIManager**)0x70c5c0)[0];
}

void AIManager::SetVehicleDensity(AIManagerVehicleTypeEnum vehicleType, float vehicleDensity)
{
	((void(__thiscall*)(AIManager*, AIManagerVehicleTypeEnum vehicleType, float vehicleDensity))0x40af37)(this, vehicleType, vehicleDensity);
}