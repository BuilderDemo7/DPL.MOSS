#include "CTargetManager.h"

void CTargetManager::RenderObjectiveIcon(Matrix* matrix, CPCViewport* piViewport, SObjectiveIcon* objective)
{
	((void(__thiscall*)(CTargetManager*, Matrix*, CPCViewport*, SObjectiveIcon*))0x4738d5)(this, matrix, piViewport, objective);
}

CTargetManager* CTargetManager::GetInstance()
{
	return *(CTargetManager**)0x70c7ec;
}

void CTargetManager::AddObjectiveIcon(SObjectiveIcon* objectiveIcon, bool particleEffect)
{
	((void(__thiscall*)(CTargetManager*, SObjectiveIcon*, bool))0x4744d7)(this, objectiveIcon, particleEffect);
}