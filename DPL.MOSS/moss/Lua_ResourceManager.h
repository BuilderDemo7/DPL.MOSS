#pragma once
#include "Lua_Main.h"

#include "..\dpl\SpoolableResourceManager.h"

int lua_SetEntityPriority(lua_State* L);
int lua_RequestEntity(lua_State* L);

int lua_IsEntityLoaded(lua_State* L);
int lua_IsEntityPresent(lua_State* L);