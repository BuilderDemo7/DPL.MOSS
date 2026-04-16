#pragma once
#include "Lua_Main.h"
#include "..\dpl\CLifeActor.h"
#include "..\dpl\SObjectiveIcon.h"
#include "..\dpl\CTargetManager.h"

int lua_AddObjectiveIconToLifeActor(lua_State* L);
int lua_RemoveObjectiveIconFromLifeActor(lua_State* L);