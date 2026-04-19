#pragma once

// EType__177_9586
enum EPrimitiveType
{
	InvalidPrimitive = -1,
	Cylinder = 0x1,
	Box = 0x2,
	Sphere = 0x3,
	Plane = 0x4
};

struct SPrimitiveData
{
	EPrimitiveType eType;

	//float fWidth;
	//float fRadius;

	// this is how it should be
	float fWidthOrRadius;
	
	float fLength;
	float fHeight;
};