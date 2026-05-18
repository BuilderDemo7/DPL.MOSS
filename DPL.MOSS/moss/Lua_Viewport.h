#pragma once
#include "Lua_Main.h"
#include "..\dpl\CPCViewport.h"

extern const char* g_ViewportMetaName;

void Init_Lua_MetaTable_Viewport();

int lua_ViewportIndex(lua_State* L);

int lua_GetViewportPointer(lua_State* L);

int lua_SetViewportAspectRatio(lua_State* L);
int lua_GetViewportAspectRatio(lua_State* L);

int lua_SetViewportWidth(lua_State* L);
int lua_GetViewportWidth(lua_State* L);

int lua_SetViewportHeight(lua_State* L);
int lua_GetViewportHeight(lua_State* L);

int lua_SetViewportPosition(lua_State* L);

int lua_AddSpriteInstance(lua_State* L);
int lua_ViewportAddStaticInstance(lua_State* L);