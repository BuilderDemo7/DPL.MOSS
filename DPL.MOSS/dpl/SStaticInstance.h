#pragma once
#include "Matrix.h"
#include "Vector4.h"
#include "ELodType.h"

struct SStaticInstance
{
	Matrix mtxWorldTransform;
	Vector4 colour;
	int whichSubstance;
	int hModel;
	unsigned int roomMask;
	float distanceFromCamera;
	ELodType eLOD;
	float fAlpha;

	SStaticInstance() {
		hModel = 0xcccccccc;
		colour = Vector4(1, 1, 1, 0);
		whichSubstance = 0;
		roomMask = 1;
		distanceFromCamera = 0.0f;
	}
};