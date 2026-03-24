#pragma once
#include "Lua_Main.h"
#include "..\dpl\AIHelicopterClass.h"

extern const char* g_HelicopterMetaName;

void Init_Lua_MetaTable_Helicopter();

int lua_HelicopterIndex(lua_State* L);

int lua_GetHelicopterDamage(lua_State* L);
int lua_SetHelicopterDamage(lua_State* L);

int lua_GetHelicopterPointer(lua_State* L);

int lua_SetHelicopterDesiredPosition(lua_State* L);
int lua_GetHelicopterPosition(lua_State* L); // actual position
int lua_GetHelicopterDesiredPosition(lua_State* L);

int lua_GetHelicopterVelocity(lua_State* L);

int lua_GetHelicopterDesiredVelocity(lua_State* L);
int lua_SetHelicopterDesiredVelocity(lua_State* L);

int lua_SetHelicopterDesiredHeading(lua_State* L);
int lua_GetHelicopterDesiredHeading(lua_State* L);

int lua_GetHelicopterForwardVector(lua_State* L);
int lua_GetHelicopterRightVector(lua_State* L);

int lua_HelicopterStepTo(lua_State* L);

int lua_CreateHelicopter(lua_State* L);
int lua_DestroyHelicopter(lua_State* L);
int lua_UpdateHelicopterMotion(lua_State* L);
