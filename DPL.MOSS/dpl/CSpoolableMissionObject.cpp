#include "CSpoolableMissionObject.h"

void CSpoolableMissionObject::Unregister()
{
	((void(__thiscall*)(CSpoolableMissionObject*))0x4736b2)(this);
}

void CSpoolableMissionObject::CreateObjects()
{
	((void(__thiscall*)(CSpoolableMissionObject*))0x473604)(this);
}

void CSpoolableMissionObject::Initialise(CSpoolableMissionObject* piCreationObject, CMovingObject* piMovingObject, Vector4* v4LastKnownPosition, float lastKnownHeading)
{
	((void(__thiscall*)(CSpoolableMissionObject*, CSpoolableMissionObject* piCreationObject, CMovingObject* piMovingObject, Vector4* v4LastKnownPosition, float lastKnownHeading))0x473673)(this, piCreationObject, piMovingObject, v4LastKnownPosition, lastKnownHeading);
}