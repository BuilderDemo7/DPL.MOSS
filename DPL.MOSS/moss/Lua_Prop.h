#pragma once
#include "Lua_Main.h"
#include "..\dpl\CLifeActor_Prop.h"

extern const char* g_PropMetaName;

void Init_Lua_MetaTable_Prop();

int lua_PropIndex(lua_State* L);

int lua_CreateProp(lua_State* L);

int lua_SetPropPosition(lua_State* L);
int lua_GetPropPosition(lua_State* L);

int lua_GetPropRotation(lua_State* L);
int lua_SetPropRotation(lua_State* L);

int lua_GetPropPointer(lua_State* L);

int lua_SetPropHeading(lua_State* L);
int lua_GetPropHeading(lua_State* L);

int lua_GetPropVelocity(lua_State* L);
int lua_SetPropVelocity(lua_State* L);

int lua_GetPropForwardVector(lua_State* L);
int lua_GetPropRightVector(lua_State* L);

int lua_InstantiateProp(lua_State* L);
int lua_DeleteProp(lua_State* L);

int lua_SetPropModelHandle(lua_State* L);
int lua_GetPropModelHandle(lua_State* L);

int lua_SetPropGadgetType(lua_State* L);