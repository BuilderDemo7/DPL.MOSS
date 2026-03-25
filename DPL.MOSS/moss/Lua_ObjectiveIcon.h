#pragma once
#include "Lua_Main.h"
#include "..\dpl\SObjectiveIcon.h"
#include "..\dpl\Matrix.h"

struct Lua_ObjectiveIcon
{
	SObjectiveIcon m_iconData;

	int m_iDisplayType;
	Matrix m_matrix;
};

extern const char* g_ObjectiveIconMetaName;

void Init_Lua_MetaTable_ObjectiveIcon();

int lua_ObjectiveIconIndex(lua_State* L);

int lua_ObjectiveIconNew(lua_State* L);
int lua_GlobalObjectiveIconModuleIndex(lua_State* L);

int lua_SetObjectiveIconPosition(lua_State* L);
int lua_GetObjectiveIconPosition(lua_State* L);

int lua_GetObjectiveIconPointer(lua_State* L);

int lua_SetObjectiveIconHeading(lua_State* L);
int lua_GetObjectiveIconHeading(lua_State* L);

int lua_SetObjectiveIconType(lua_State* L);
int lua_GetObjectiveIconType(lua_State* L);

int lua_DrawObjectiveIcon(lua_State* L);