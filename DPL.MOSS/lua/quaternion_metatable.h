#pragma once
#include <iostream>
#include "includelua.h"
#include "vector_metatable.h"

#define MATH_PI 3.14159274101257324219

struct Lua_Quaternion
{
	float X, Y, Z, W;
};

extern const char* g_LuaQuaternionMetaTable;

extern void Init_Lua_MetaTable_Quaternion(lua_State* LST);

int lua_QuaternionNew(lua_State* L);
int lua_QuaternionDestroy(lua_State* L);

int lua_QuaternionIndex(lua_State* L);
int lua_QuaternionNewIndex(lua_State* L);

int lua_GlobalQuaternionModuleIndex(lua_State* L);

int lua_QuaternionFromEulerAngles(lua_State* L);
int lua_QuaternionToEulerAngles(lua_State* L);