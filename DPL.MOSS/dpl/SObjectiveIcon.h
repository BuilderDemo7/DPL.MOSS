#pragma once
#include "Vector4.h"
#include "CLifeActor.h"
#include "CPCViewport.h"

#include "EGadgetType.h"

#pragma pack(push, 1)
struct SObjectiveIcon
{
	Vector4 m_colour;

	int field8; // LocalisedString* m_description
	
	CLifeActor* m_pTarget;

	unsigned short m_modelHandle;
	short __padding0;
	int m_activity;
	int m_displayType;
	int m_visibility;
	int m_material;
	bool m_minimapDisplayArrow;
	bool m_displayAsCop;
	bool m_bRotate;
	bool m_bParticleEffect;
	void* m_pParticleEffect;
	unsigned int m_uiEffectIssueNum;
	char field38;

	char __padding1[3];

	bool m_bUseColour;

	char __padding2[3];

	float m_rotation;
	float m_heightOffset;
};
#pragma pack(pop)

void SetupObjectiveIcon(SObjectiveIcon* oicon, int displayType, int lifeEventType = 0);
void AutoRenderObjectiveIcon(SObjectiveIcon* oicon, Matrix* matrix, CPCViewport* piViewport);