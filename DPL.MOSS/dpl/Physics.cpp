#include "Physics.h"

void phObjectVelocitySet(OBobject* phObj, Vector4* velocity)
{
	((void(__fastcall*)(OBobject*, Vector4*))0x5C5133)(phObj, velocity);
}

void phObjectOrientationSet(OBobject* phObj, Vector4* quatRotation)
{
	((void(__fastcall*)(OBobject*, Vector4*))0x5c516e)(phObj, quatRotation);
}

void phObjectPositionSet(OBobject* phObj, Vector4* position)
{
	((void(__fastcall*)(OBobject*, Vector4*))0x5c50d3)(phObj, position);
}

// defunc!! do NOT use!!
void phObjectPositionSet_HACK(OBobject* phObj, Vector4* position)
{
	phObj->m_vPos.X = position->X;
	phObj->m_vPos.Y = position->Y;
	phObj->m_vPos.Z = position->Z;
	phObj->m_vPos.W = position->W;

	// obUpdateTransMatrix__FP8OBobject()
	((void(__thiscall*)(OBobject*))0x5cf4e0)(phObj);
}

void phObjectPositionAndOrientationSet(PHobject* phObj, Vector4* quatOrientation, Vector4* position)
{
	((void(__fastcall*)(OBobject*, Vector4*, Vector4*))0x5C4EDA)(phObj, quatOrientation, position);
}