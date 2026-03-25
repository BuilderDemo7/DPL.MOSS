#pragma once
#include "Lua_Main.h"

int lua_memwrite(lua_State* L);
int lua_memread(lua_State* L);
int lua_mempatch(lua_State* L);
int lua_meminject(lua_State* L);

int lua_castfloat(lua_State* L);
int lua_castdouble(lua_State* L);
int lua_castint(lua_State* L);
int lua_castuint(lua_State* L);
int lua_castshort(lua_State* L);
int lua_castushort(lua_State* L);

int lua_castCharacter(lua_State* L);
int lua_castVehicle(lua_State* L);
int lua_castHelicopter(lua_State* L);
int lua_castMapItem(lua_State* L);

int lua_GetAsyncKeyState(lua_State* L);