#pragma once
#include "Lua_Main.h"
#include "..\dpl\CLifeActor_Camera.h"

extern const char* g_CameraMetaName;

void Init_Lua_MetaTable_Camera();

int lua_CameraIndex(lua_State* L);

int lua_GetCameraPointer(lua_State* L);

int lua_CreateCamera(lua_State* L);

int lua_GetCameraAttachedTo(lua_State* L);
int lua_GetCameraAttachedToPointer(lua_State* L);
int lua_GetCameraLookAt(lua_State* L);
int lua_GetCameraLookAtPointer(lua_State* L);