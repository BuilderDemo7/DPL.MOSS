#include "CPCViewport.h"

CPCViewport* CPCViewport::GetSimulationViewport()
{
	return *(CPCViewport**)(0x71C390);
}

// NOT a CPCViewport*!!!
CPCViewport* CPCViewport::GetGenericViewport()
{
	return *(CPCViewport**)(0x70C718);
}

CPCViewport* CPCViewport::GetMainMenuViewport()
{
	void* Singleton_UserMainMenu = *(void**)0x70c560;
	CPCViewport* vp = *(CPCViewport**)((int)Singleton_UserMainMenu + 0x4);

	return vp;
}

void CPCViewport::SetFOV(float FOV)
{
	*(float*)((int)this + 0x50C) = FOV;
}

void CPCViewport::SetWidth(float width)
{
	*(float*)((int)this + 0x504) = width;
}

void CPCViewport::SetHeight(float height)
{
	*(float*)((int)this + 0x508) = height;
}

int CPCViewport::GetVTableAddress()
{
	return *(int*)(this);
}

void CPCViewport::AddStaticInstance(SStaticInstance* pInstance)
{
	((void(__thiscall*)(CPCViewport*, SStaticInstance*))*(int*)(GetVTableAddress() + 0x28))(this, pInstance);
}