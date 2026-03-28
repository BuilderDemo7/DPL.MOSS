#include "CLifeActor.h"

int CLifeActor::GetVTableAddress()
{
	return *(int*)(this);
}

void CLifeActor::Create()
{
	((void(__thiscall*)(CLifeActor*))*(int*)(GetVTableAddress() + 0x10))(this);
}

void CLifeActor::Delete()
{
	((void(__thiscall*)(CLifeActor*))*(int*)(GetVTableAddress() + 0x14))(this);
}

EFactoryType CLifeActor::hamsterFactoryType()
{
	return ((EFactoryType(__thiscall*)(CLifeActor*))*(int*)(GetVTableAddress() + 0x18))(this);
}

Matrix CLifeActor::GetMatrix()
{
	Matrix returnStorage = Matrix();

	((Matrix*(__thiscall*)(CLifeActor*, Matrix*))*(int*)(GetVTableAddress() + 0x24))(this, &returnStorage);

	return returnStorage;
}