#pragma once
#include "Lua_Main.h"
#include "Lua_LifeActor.h"
#include "..\dpl\CLifeActor_TestVolume.h"

extern const char* g_TestVolumeMetaName;

void Init_Lua_MetaTable_TestVolume();

int lua_TestVolumeIndex(lua_State* L);

int lua_CreateTestVolume(lua_State* L);

int lua_TestVolumeIsPositionInside(lua_State* L);

int lua_SetTestVolumePosition(lua_State* L);
int lua_GetTestVolumePosition(lua_State* L);

int lua_GetTestVolumeRotation(lua_State* L);
int lua_SetTestVolumeRotation(lua_State* L);

int lua_GetTestVolumePointer(lua_State* L);

int lua_SetTestVolumeHeading(lua_State* L);
int lua_GetTestVolumeHeading(lua_State* L);

int lua_GetTestVolumeForwardVector(lua_State* L);
int lua_GetTestVolumeRightVector(lua_State* L);
