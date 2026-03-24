#include "CWipeManager.h"

CWipeManager* CWipeManager::GetInstance()
{
	return *(CWipeManager**)0x70c79c;
}

void CWipeManager::ResetWipes()
{
	((void(__thiscall*)(CWipeManager*))0x55dd29)(this);
}

void CWipeManager::ScreenFadeOut(Vector4 color, float duration, bool additive)
{
	fade_from_colour data = fade_from_colour();

	data.m_colour = color;
	data.m_duration = duration;
	data.m_bAdditive = additive;

	AddSpeedDependentWipe(&data, EAddWipe_Replace);
}

fade_from_colour* CWipeManager::AddSpeedDependentWipe(fade_from_colour* val, EAddWipe eAddType)
{
	return ((fade_from_colour*(__thiscall*)(CWipeManager*, fade_from_colour*, EAddWipe))0x45d823)(this, val, eAddType);
}