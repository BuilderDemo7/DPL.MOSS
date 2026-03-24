#include "Lua_Hooking.h"
#include "Lua_Character.h"

#include "..\utils.h"

int lua_memwrite(lua_State* L)
{
	int nargs = lua_gettop(L); // number of arguments

	int address = (int)luaL_checkinteger(L, 1);  // param 1
	const char* buffer = luaL_checkstring(L, 2);  // param 2
	int bufferSize = (int)luaL_checkinteger(L, 3);  // param 3

	if (nargs < 3)
	{
		return luaL_error(L, "Expected 1 integer (for address), a string (for buffer), another integer (for buffer size)");
	}

	WriteAt(address, buffer, bufferSize);

	return 0;  // number of return(s)
}

int lua_memread(lua_State* L)
{
	int address = (int)luaL_checkinteger(L, 1);  // param 1
	int size = (int)luaL_checkinteger(L, 2);  // param 2

	char* mem = (char*)lua_newuserdata(L, size);
	memset(mem, 0, size);

	memcpy(mem, (void*)address, size);

	lua_pushstring(L, mem);

	return 1; // number of return values
}

int lua_mempatch(lua_State* L)
{
	int address = (int)luaL_checkinteger(L, 1);  // param 1
	const char* buffer = luaL_checkstring(L, 2);  // param 2

	Patch(address, buffer);

	return 0;  // number of return(s)
}

// WARNING: the label must be constant and not stored in the stack to prevent data loss
int lua_meminject(lua_State* L)
{
	int address = (int)luaL_checkinteger(L, 1);  // param 1
	const char* funcLabel = luaL_checkstring(L, 2);  // param 2
	int type = (int)luaL_checkinteger(L, 3);  // param 3

	InjectHook(address, funcLabel, type);

	return 0;  // number of return(s)
}

// WARNING: the label must be constant and not stored in the stack to prevent data loss
int lua_GetAsyncKeyState(lua_State* L)
{
	int key = (int)luaL_checkinteger(L, 1);  // param 1

	int result = GetAsyncKeyState(key);
	lua_pushinteger(L, result);

	return 1;  // number of return(s)
}

int lua_castfloat(lua_State* L)
{
	const char* data = luaL_checkstring(L, 1);
	int offset = luaL_optinteger(L, 2, 0);

	float castData = *(float*)(data + offset);

	lua_pushnumber(L, castData);

	return 1;
}

int lua_castdouble(lua_State* L)
{
	const char* data = luaL_checkstring(L, 1);
	int offset = luaL_optinteger(L, 2, 0);

	double castData = *(double*)(data + offset);

	lua_pushnumber(L, castData);

	return 1;
}

int lua_castint(lua_State* L)
{
	const char* data = luaL_checkstring(L, 1);
	int offset = luaL_optinteger(L, 2, 0);

	unsigned int castData = *(unsigned int*)(data + offset);

	lua_pushinteger(L, castData);

	return 1;
}

int lua_castuint(lua_State* L)
{
	const char* data = luaL_checkstring(L, 1);
	int offset = luaL_optinteger(L, 2, 0);

	unsigned int castData = *(unsigned int*)(data + offset);

	lua_pushinteger(L, castData);

	return 1;
}

int lua_castshort(lua_State* L)
{
	const char* data = luaL_checkstring(L, 1);
	int offset = luaL_optinteger(L, 2, 0);

	short castData = *(short*)(data + offset);

	lua_pushinteger(L, castData);

	return 1;
}

int lua_castushort(lua_State* L)
{
	const char* data = luaL_checkstring(L, 1);
	int offset = luaL_optinteger(L, 2, 0);

	unsigned short castData = *(unsigned short*)(data + offset);

	lua_pushinteger(L, castData);

	return 1;
}
