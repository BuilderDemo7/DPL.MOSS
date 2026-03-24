#pragma once
#include "Vector4.h"

struct OBobject
{
	char undefined[128];
	Vector4 m_vPos;
	Vector4 m_vVel;
	Vector4 m_qOrientation;
};

typedef OBobject PHobject;

void phObjectVelocitySet(OBobject* phObj, Vector4* velocity); // set object velocity (MAv4 field 0x90)
void phObjectOrientationSet(OBobject* phObj, Vector4* quatRotation); // set object rotation (MAq field 0x80)
void phObjectPositionSet(OBobject* phObj, Vector4* position); // set object position (MAv4 field 0xA0)
void phObjectPositionSet_HACK(OBobject* phObj, Vector4* position);
void phObjectPositionAndOrientationSet(PHobject* phObj, Vector4* quatOrientation, Vector4* position);