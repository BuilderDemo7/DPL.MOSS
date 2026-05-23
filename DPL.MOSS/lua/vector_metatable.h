#pragma once
#include <iostream>
#include "includelua.h"

//#define LUA_VECTOR_DEBUGLOG_CALLS

struct Lua_Vector
{
	double X,Y,Z;
};

extern const char* g_LuaVectorMetaTable;

extern void Init_Lua_MetaTable_Vector(lua_State* LST);

int lua_VectorAdd(lua_State* L);
int lua_VectorSub(lua_State* L);
int lua_VectorMul(lua_State* L);
int lua_VectorDiv(lua_State* L);

int lua_VectorNew(lua_State* L);
int lua_VectorDestroy(lua_State* L);

int lua_GlobalVectorModuleIndex(lua_State* L);

int lua_VectorNewIndex(lua_State* L);
int lua_VectorIndex(lua_State* L);