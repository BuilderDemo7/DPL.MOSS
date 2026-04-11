#include "CLifeActor.h"

int CLifeActor::GetVTableAddress()
{
	return *(int*)(this);
}

CSpoolableMissionObject* CLifeActor::CreateInstance()
{
	CSpoolableMissionObject* return_storage_ptr = NULL;

	return ((CSpoolableMissionObject*(__thiscall*)(CLifeActor*, CSpoolableMissionObject**))*(int*)(GetVTableAddress() + 0xC))(this, &return_storage_ptr);
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