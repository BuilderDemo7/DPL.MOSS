#include "Hooks_Redirect.h"

#include "moss/Lua_Main.h"

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

void OnDrawMission()
{
	OnDrawMission_Lua();
}