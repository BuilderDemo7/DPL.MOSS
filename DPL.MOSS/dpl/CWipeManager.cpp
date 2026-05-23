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

void CWipeManager::ScreenFade(Vector4 color, Vector4 targetColor, float duration, bool fadeAudio, bool fadeToBlack)
{
	fade_node_wipe data = fade_node_wipe();

	data.m_colour = color;
	data.m_targetColour = targetColor;
	data.m_fDuration = duration;
	data.m_bFadeToBlack = fadeToBlack;
	data.m_bFadeAudio = fadeAudio;
	data.m_bDying = false;

	AddSpeedDependentWipe(&data, EAddWipe_Replace);
}

fade_from_colour* CWipeManager::AddSpeedDependentWipe(fade_from_colour* val, EAddWipe eAddType)
{
	return ((fade_from_colour*(__thiscall*)(CWipeManager*, fade_from_colour*, EAddWipe))0x45d823)(this, val, eAddType);
}

fade_node_wipe* CWipeManager::AddSpeedDependentWipe(fade_node_wipe* val, EAddWipe eAddType)
{
	return ((fade_node_wipe*(__thiscall*)(CWipeManager*, fade_node_wipe*, EAddWipe, int unknown))0x49a547)(this, val, eAddType, 0);
}