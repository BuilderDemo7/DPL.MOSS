#pragma once
#include "Lua_Main.h"
#include "..\dpl\LifeInstances.h"

extern const char* g_LifeInstanceMetaName;

struct Lua_LifeInstanceInfo
{
	const char* m_pszMetaTableName;
	void* m_pUserData; // CLifeInstances**
};

void Init_Lua_MetaTable_LifeInstance();
int lua_LifeInstanceIndex(lua_State* L);
int lua_GetLifeInstancePointer(lua_State* L);

void* lua_checklifeinstance(lua_State* L, int ud, bool shouldError = true);

const char* GetLifeInstanceMetaTableName(CLifeInstance* instance);
Lua_LifeInstanceInfo GetLuaLifeInstance(CLifeInstance* actor);

int lua_GetLifeInstanceInstance(lua_State* L);

int lua_GetLifeInstances(lua_State* L);

// generic funcs
int lua_DestroyLifeInstance(lua_State* L);
int lua_InstantiateLifeInstance(lua_State* L);

int lua_GetLifeInstancePosition(lua_State* L);
int lua_SetLifeInstancePosition(lua_State* L);