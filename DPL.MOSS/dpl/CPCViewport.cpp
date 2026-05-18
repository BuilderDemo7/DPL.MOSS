#include "CPCViewport.h"

// -> 0x4b366e, sets viewport aspect ratio to 1.7777778
// -> 0x64b238, viewport's aspect ratio (1.7777778)
// -> 0x64b234, viewport's FOV factor (1.308)

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

float CPCViewport::GetWidth()
{
	return *(float*)((int)this + 0x504);
}

float CPCViewport::GetHeight()
{
	return *(float*)((int)this + 0x508);
}

float CPCViewport::GetAspectRatio()
{
	return *(float*)((int)this + 0x510);
}

int CPCViewport::GetVTableAddress()
{
	return *(int*)(this);
}

void CPCViewport::SetAspectRatio(float fAspect)
{
	((void(__thiscall*)(CPCViewport*, float))*(int*)(GetVTableAddress() + 0x94))(this, fAspect);
}

void CPCViewport::AddSpriteInstance(SSpriteInstance* pInstance)
{
	((void(__thiscall*)(CPCViewport*, SSpriteInstance*))*(int*)(GetVTableAddress() + 0x40))(this, pInstance);
}

void CPCViewport::AddStaticInstance(SStaticInstance* pInstance)
{
	((void(__thiscall*)(CPCViewport*, SStaticInstance*))*(int*)(GetVTableAddress() + 0x28))(this, pInstance);
}

void CPCViewport::SetViewportPosition(float fX, float fY)
{
	((void(__thiscall*)(CPCViewport*, float, float))*(int*)(GetVTableAddress() + 0x84))(this, fX, fY);
}