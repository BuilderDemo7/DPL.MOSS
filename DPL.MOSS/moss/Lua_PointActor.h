#pragma once
#include "Lua_Main.h"
#include "Lua_LifeActor.h"
#include "..\dpl\CLifeActor_Marker.h"

extern const char* g_PointActorMetaName;

void Init_Lua_MetaTable_PointActor();

int lua_PointActorIndex(lua_State* L);

int lua_CreatePoint(lua_State* L);

int lua_SetPointActorPosition(lua_State* L);
int lua_GetPointActorPosition(lua_State* L);

int lua_GetPointActorRotation(lua_State* L);
int lua_SetPointActorRotation(lua_State* L);

int lua_GetPointActorPointer(lua_State* L);

int lua_SetPointActorHeading(lua_State* L);
int lua_GetPointActorHeading(lua_State* L);

int lua_GetPointActorForwardVector(lua_State* L);
int lua_GetPointActorRightVector(lua_State* L);
