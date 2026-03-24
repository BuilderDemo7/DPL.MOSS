#include "CPCViewport.h"

CPCViewport* CPCViewport::GetSimulationViewport()
{
	return (CPCViewport*)(*(int*)(0x71C390));
}

CPCViewport* CPCViewport::GetGenericViewport()
{
	return *(CPCViewport**)(*(int*)(0x70C718));
}

void CPCViewport::SetFOV(float FOV)
{
	*(float*)((int)this + 0x50C) = FOV;
}

int CPCViewport::GetVTableAddress()
{
	return *(int*)(this);
}

void CPCViewport::AddStaticInstance(SStaticInstance* pInstance)
{
	((void(__thiscall*)(CPCViewport*, SStaticInstance*))*(int*)(GetVTableAddress() + 0x28))(this, pInstance);
}