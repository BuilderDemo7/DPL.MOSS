#pragma once

enum AIManagerVehicleTypeEnum
{
	Civilian,
	CivilianParked,
	CivilianParkedAttractedCar,
	CivilianParkedAttractedBus,
	CivilianParkedAttractedBoat,
	CivilianParkedAttractedBike,
	CivilianParkedAttractedLorry,
	CivilianParkedAttractedTaxi,
	CivilianParkedAttractedGoKart,
	NumberOf
};

class AIManager {
public:
	static AIManager* GetInstance();

	void SetVehicleDensity(AIManagerVehicleTypeEnum vehicleType, float vehicleDensity);
};