#pragma once
#include "Vector4.h"
#include "CLifeActor.h"
#include "CPCViewport.h"

#include "EGadgetType.h"

struct SObjectiveIcon
{
	Vector4 m_colour;
	CLifeActor* m_pTarget;

	int field8;
	
	int m_modelHandle;
	int _m_activity;
	int m_displayType;
	int m_visibility;
	int m_material;
	bool m_minimapDisplayArrow;
	bool m_displayAsCop;
	bool m_bRotate;
	bool m_bParticleEffect;
	void* m_pParticleEffect;
	unsigned int m_uiEffectIssueNum;
	bool m_bUseColour;

	char __padding0[7];
	
	float m_rotation;
	float m_heightOffset;
};

void SetupObjectiveIcon(SObjectiveIcon* oicon, int displayType, int lifeEventType = 0);
void AutoRenderObjectiveIcon(SObjectiveIcon* oicon, Matrix* matrix, CPCViewport* piViewport);