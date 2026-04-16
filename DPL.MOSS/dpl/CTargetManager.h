#pragma once
#include "Matrix.h"
#include "CPCViewport.h"

#include "SObjectiveIcon.h"

class CTargetManager
{
public:
	void RenderObjectiveIcon(Matrix* matrix, CPCViewport* piViewport, SObjectiveIcon* objective);
	void AddObjectiveIcon(SObjectiveIcon* objectiveIcon, bool particleEffect = false);

	static CTargetManager* GetInstance();
};