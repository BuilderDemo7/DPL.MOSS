#include "CLifeActor.h"

int CLifeActor::GetVTableAddress()
{
	return *(int*)(this);
}

void CLifeActor::Create()
{
	((void(__thiscall*)(CLifeActor*))*(int*)(GetVTableAddress() + 0x10))(this);
}

Matrix CLifeActor::GetMatrix()
{
	Matrix returnStorage = Matrix();

	((Matrix*(__thiscall*)(CLifeActor*, Matrix*))*(int*)(GetVTableAddress() + 0x24))(this, &returnStorage);

	return returnStorage;
}