#pragma once
#include "Lua_Main.h"
#include "..\dpl\CLifeActor.h"
#include "..\dpl\SObjectiveIcon.h"
#include "..\dpl\CTargetManager.h"

struct Lua_LifeActorInfo
{
	const char* m_pszMetaTableName;
	void* m_pUserData; // CLifeActor**
};

int lua_AddObjectiveIconToLifeActor(lua_State* L);
int lua_RemoveObjectiveIconFromLifeActor(lua_State* L);

void* lua_checklifeactor(lua_State* L, int ud, bool shouldError = true);

const char* GetLifeActorMetaTableName(CLifeActor* actor);
Lua_LifeActorInfo GetLuaLifeActor(CLifeActor* actor);

// generic funcs
int lua_DestroyLifeActor(lua_State* L);
int lua_InstantiateLifeActor(lua_State* L);