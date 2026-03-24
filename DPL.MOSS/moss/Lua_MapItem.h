#pragma once
#include "Lua_Main.h"
#include "..\dpl\GameOverlayManager.h"

extern const char* g_MapItemMetaName;

void Init_Lua_MetaTable_MapItem();

int lua_AddMapItem(lua_State* L);

int lua_MapItemIndex(lua_State* L);

int lua_SetMapItemPosition(lua_State* L);
int lua_GetMapItemPosition(lua_State* L);

int lua_GetMapItemPointer(lua_State* L);

int lua_SetMapItemHeading(lua_State* L);
int lua_GetMapItemHeading(lua_State* L);

int lua_SetMapItemType(lua_State* L);
int lua_GetMapItemType(lua_State* L);

int lua_SetMapItemShowArrow(lua_State* L);
int lua_GetMapItemShowArrow(lua_State* L);

int lua_GetMapMarkerActive(lua_State* L);
int lua_SetMapMarkerActive(lua_State* L);

int lua_GetPlayerMapItem(lua_State* L);
int lua_GetMapMarkerItem(lua_State* L);
int lua_GetCameraMapItem(lua_State* L);

int lua_GetMapItems(lua_State* L);