#include "Hooks_Redirect.h"

#include "moss/Lua_Main.h"

CPCViewport* g_pMissionViewport = NULL;

void OnLoadMission()
{
	Init_LuaScripts();
}

void OnReloadGame()
{
	Reload_Lua();
}

void OnPostStep()
{
	PostStep_Lua();
}

void OnDrawMission(CPCViewport* vp)
{
	g_pMissionViewport = vp;

	OnDrawMission_Lua();
}

void OnDrawTargetManager()
{
	OnDrawTargetManager_Lua();
}