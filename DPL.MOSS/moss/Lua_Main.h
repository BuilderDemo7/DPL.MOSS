#pragma once
#include "..\lua\includelua.h"
#include "..\lua\vector_metatable.h"
#include "..\lua\quaternion_metatable.h"

#define LUA_SCRIPTS_FOLDER "moss_scripts"

// arrays, storage, etc.
#include <vector>

static bool g_SimulationFirstStepTicked = false;
extern bool g_bLuaScriptsLoaded;
extern bool g_bLuaScriptsStarted;

extern lua_State* L;

void Init_LuaMisc();
void Init_LuaScripts();

void Lua_Start();
void Step_Lua();
void PostStep_Lua();

void OnDrawMission_Lua();
void OnDrawTargetManager_Lua();

void Close_Lua();
void Reload_Lua();

void Init_Lua_Constants();
void Init_Lua_Funcs();
void Init_Lua_MetaTables();