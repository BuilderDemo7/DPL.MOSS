#pragma once
#include "Vector4.h"
#include "CLifeActor.h"
#include "CPCViewport.h"

#include "EGadgetType.h"

enum ObjectiveIconDisplayType
{
	DisplayType_VEDIT = 2,
	DisplayType_POSITIONMARKERTALLFAT = 0,
	DisplayType_ARMOUREDCAR = 4,
	DisplayType_CIRCUITRACE = 5,
	DisplayType_HITMAN = 6,
	DisplayType_MOTOCROSS = 7,
	DisplayType_PERFECTDELIVERY = 8,
	DisplayType_REPOMAN = 10,
	DisplayType_SAFEHOUSE = 0xb,
	DisplayType_STICKUP = 0xc,
	DisplayType_STREETRACE = 0xd,
	DisplayType_TAXI = 0xe,
	DisplayType_LOANSHARK = 0xf,
	DisplayType_POSITIONMARKERTALLSKINNY = 0x10,
	DisplayType_POSITIONMARKERSHORTSKINNY = 0x11,
	DisplayType_POSITIONMARKERSHORTFAT = 0x13,
	DisplayType_POSITIONMARKERCONE = 0x14,
	DisplayType_PRISONTRANSPORT = 0x15,
	DisplayType_GARAGEPOSITIONMARKERSHORTFAT = 0x19,
	DisplayType_GARAGEPOSITIONMARKERSHORTSKINNY = 0x1a,
	DisplayType_GARAGEPOSITIONMARKERTALLSKINNY = 0x1b
};

enum ObjectiveIconVisibility
{
	ObjVisibility_MinimapAndModel = 1,
	ObjVisibility_ModelOnly = 2,
	ObjVisibility_MinimapOnly = 3,
};

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

void SetupObjectiveIcon(SObjectiveIcon* oicon, int displayType, int lifeEventType = 0, bool bIsLifeEventVisible = true);
void AutoRenderObjectiveIcon(SObjectiveIcon* oicon, Matrix* matrix, CPCViewport* piViewport);