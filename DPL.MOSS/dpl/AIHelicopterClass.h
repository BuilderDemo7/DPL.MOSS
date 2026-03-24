#pragma once
#include "Vector4.h"
#include "Matrix.h"

class AIHelicopterClass
{
public:
	char __padding0[0x8f];

	Vector4 m_v4Position;
	Vector4 m_v4DesiredPosition;
	Vector4 m_v4PositionSnappedToRoad;
	Vector4 m_v4Velocity;
	Vector4 m_v4DesiredVelocity;
	Vector4 m_v4Tangent;
	Vector4 m_v4Normal;
	Vector4 m_v4Binormal;
	Vector4 m_v4Heading;
	Vector4 m_v3Size;
	float m_rXAxisRoll;
	float m_rZAxisRoll;
	float m_rWobble_X;
	float m_rWobble_Y;
	float m_rWobble_Z;
	float m_rDesiredHeading;
	unsigned int m_eHelicopterType;

	char __padding1[0x17];

	float m_rDamage;

	void AIHelicopterInitialise(Vector4* inPosition, Vector4* inVelocity, float inHeading, bool isGoonHelicopter, bool bHelicopterOnlySpline, bool bIsLanded, bool bDestroyable);
	void UpdateHelicopterMotion();

	float GetSpeed();
	Matrix* GetMatrix(Matrix* returnStorage);
	void KillMe();
	void FallFromSky();
};

AIHelicopterClass* CreateHelicopter(Vector4 inPosition, Vector4 inVelocity, float inHeading, bool isGoonHelicopter, bool bHelicopterOnlySpline, bool bIsLanded, bool bDestroyable);
void DestroyHelicopter(AIHelicopterClass* helicopter);