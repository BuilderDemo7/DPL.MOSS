#pragma once
#include "CMovingObject.h"
#include "Vector4.h"

class CSpoolableMissionObject
{
public:
	void Unregister(); // disables pinging out

	void CreateObjects();

	void Initialise(CSpoolableMissionObject* piCreationObject, CMovingObject* piMovingObject, Vector4* v4LastKnownPosition, float lastKnownHeading = 0.0f);
};