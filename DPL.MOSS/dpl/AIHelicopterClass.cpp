#include "AIHelicopterClass.h"
#include "Factory.h"

AIHelicopterClass* CreateHelicopter(Vector4 inPosition, Vector4 inVelocity, float inHeading, bool isGoonHelicopter, bool bHelicopterOnlySpline, bool bIsLanded, bool bDestroyable)
{
	AIHelicopterClass* heli = (AIHelicopterClass*)hamster::CreateObject(EFactoryType_Helicopter);

	heli->AIHelicopterInitialise(&inPosition, &inVelocity, inHeading, isGoonHelicopter, bHelicopterOnlySpline, bIsLanded, bDestroyable);

	// RegisterTargetHelicopter(CTargetManager *this,CLifeActor_Helicopter *pHelicopterActor) - just too lazy to do a actual function for it :P
	// EDIT: Whoops, it was meant for CLifeActor_Helicopter
	//((void(__thiscall*)(void*, AIHelicopterClass*))0x4738b9)(*(void**)0x70c7ec, heli);

	return heli;
}

void DestroyHelicopter(AIHelicopterClass* helicopter)
{
	// void operator()<class_IInterface> (void * pPointer)
	((void(__thiscall*)(void*))0x4ad031)((void*)helicopter);
}

void AIHelicopterClass::AIHelicopterInitialise(Vector4* inPosition, Vector4* inVelocity, float inHeading, bool isGoonHelicopter, bool bHelicopterOnlySpline, bool bIsLanded, bool bDestroyable)
{
	((void(__thiscall*)(AIHelicopterClass*, Vector4*, Vector4*, float, bool, bool, bool, bool))0x43cdc3)(this, inPosition, inVelocity, inHeading, isGoonHelicopter, bHelicopterOnlySpline, bIsLanded, bDestroyable);
}

void AIHelicopterClass::UpdateHelicopterMotion()
{
	((void(__thiscall*)(AIHelicopterClass*))0x43d452)(this);
}

float AIHelicopterClass::GetSpeed()
{
	return ((float(__thiscall*)(AIHelicopterClass*))0x43ea86)(this);
}

Matrix* AIHelicopterClass::GetMatrix(Matrix* returnStorage)
{
	return ((Matrix*(__thiscall*)(AIHelicopterClass*, Matrix*))0x43eaec)(this, returnStorage);
}

void AIHelicopterClass::KillMe()
{
	((void(__thiscall*)(AIHelicopterClass*))0x43d2dd)(this);
}

void AIHelicopterClass::FallFromSky()
{
	((void(__thiscall*)(AIHelicopterClass*))0x43d3d2)(this);
}