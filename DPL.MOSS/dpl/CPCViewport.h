#pragma once
#include "SStaticInstance.h"
#include "Sprite.h"

#define FOV_TO_FINAL(X) ((X) * 0.017453292f )
#define FINAL_TO_FOV(X) ((X) / 0.017453292f )

static bool AdjustableFOV = false;
static float ViewportFOV = 70;

class CPCViewport {
public:
	static CPCViewport* GetSimulationViewport();
	static CPCViewport* GetGenericViewport();
	static CPCViewport* GetMainMenuViewport();
	void SetFOV(float FOV);

	void SetWidth(float width);
	void SetHeight(float height);
	float GetWidth();
	float GetHeight();

	float GetAspectRatio();

	int GetVTableAddress();
	
	void AddStaticInstance(SStaticInstance* pInstance);
	void AddSpriteInstance(SSpriteInstance* pInstance);
	
	void SetViewportPosition(float fX, float fY);
	void SetAspectRatio(float fAspect);
};