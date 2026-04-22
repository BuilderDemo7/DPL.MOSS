#pragma once
#include "Lua_Main.h"
#include "..\dpl\CLifeActor.h"
#include "..\dpl\SObjectiveIcon.h"
#include "..\dpl\CTargetManager.h"

extern const char* g_LifeActorMetaName;

struct Lua_LifeActorInfo
{
	const char* m_pszMetaTableName;
	void* m_pUserData; // CLifeActor**
};

void Init_Lua_MetaTable_LifeActor();
int lua_LifeActorIndex(lua_State* L);
int lua_GetLifeActorPointer(lua_State* L);

int lua_AddObjectiveIconToLifeActor(lua_State* L);
int lua_RemoveObjectiveIconFromLifeActor(lua_State* L);

void* lua_checklifeactor(lua_State* L, int ud, bool shouldError = true);

const char* GetLifeActorMetaTableName(CLifeActor* actor);
Lua_LifeActorInfo GetLuaLifeActor(CLifeActor* actor);

// generic funcs
int lua_DestroyLifeActor(lua_State* L);
int lua_InstantiateLifeActor(lua_State* L);