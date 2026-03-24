#pragma once
extern bool g_bSimulationInitalised;

void CState__LoadMission__Hook();
void CState_Simulation__Initialise__Hook();
void CLoadingScreen__Deactivate__Hook();
void CState_Reload__OnEnterState_Hook();
void CLifeSystem__Step__Hook();
void visuals_draw__DrawMission__Hook();
