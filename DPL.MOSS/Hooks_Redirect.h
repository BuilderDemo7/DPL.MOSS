#pragma once
#include "dpl/CPCViewport.h"

extern CPCViewport* g_pMissionViewport;

void OnLoadMission();
void OnReloadGame();
void OnPostStep();
void OnDrawMission(CPCViewport* vp);