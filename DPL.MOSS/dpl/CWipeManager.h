#pragma once
#include "Vector4.h"
#include "EAddWipe.h"

struct fade_from_colour
{
	void * vtable;
	Vector4 m_colour;
	float m_duration;
	bool m_bAdditive;

	fade_from_colour()
	{
		vtable = (void*)0x643528;
	}
};

struct fade_node_wipe
{
	void * vtable;

	Vector4 m_colour;
	Vector4 m_targetColour;
	float m_fDuration;
	bool m_bFadeToBlack;
	bool m_bDying;
	bool m_bFadeAudio;

	fade_node_wipe()
	{
		vtable = (void*)0x648ee8;
		m_bDying = false;
	}
};

class CWipeManager {
public:
	static CWipeManager* GetInstance();
	void ResetWipes();
	void ScreenFadeOut(Vector4 color, float duration, bool additive = false);
	void ScreenFade(Vector4 color, Vector4 targetColor, float duration, bool fadeAudio, bool fadeToBlack);

	fade_from_colour* AddSpeedDependentWipe(fade_from_colour* val, EAddWipe eAddType);
	fade_node_wipe* AddSpeedDependentWipe(fade_node_wipe* val, EAddWipe eAddType);
};