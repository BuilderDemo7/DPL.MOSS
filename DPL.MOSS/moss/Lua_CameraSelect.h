#pragma once
#include "Lua_Main.h"
#include "..\dpl\CLifeNode_CameraSelect.h"

extern const char* g_CameraSelectMetaName;

void Init_Lua_MetaTable_CameraSelect();

int lua_CameraSelectIndex(lua_State* L);

int lua_GetCameraSelectPointer(lua_State* L);

int lua_EnableCameraSelect(lua_State* L);
int lua_DisableCameraSelect(lua_State* L);

int lua_CreateCameraSelect(lua_State* L);