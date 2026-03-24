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

class CWipeManager {
public:
	static CWipeManager* GetInstance();
	void ResetWipes();
	void ScreenFadeOut(Vector4 color, float duration, bool additive = false);
	fade_from_colour* AddSpeedDependentWipe(fade_from_colour* val, EAddWipe eAddType);
};