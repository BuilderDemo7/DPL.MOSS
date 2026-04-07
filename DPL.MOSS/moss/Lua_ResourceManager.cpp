#include "Lua_ResourceManager.h"

int lua_SetEntityPriority(lua_State* L)
{
	SpooledPackageType pkg = (SpooledPackageType)luaL_checkinteger(L, 1);
	int entity = luaL_checkinteger(L, 2);
	ESpoolPriority priority = (ESpoolPriority)luaL_checkinteger(L, 3);

	auto rman = SpoolableResourceManager::GetInstance();
	if (rman != NULL)
	{
		rman->SetEntityPriority(pkg, entity, priority);
	}

	return 0;
}

int lua_RequestEntity(lua_State* L)
{
	SpooledPackageType pkg = (SpooledPackageType)luaL_checkinteger(L, 1);
	int entity = luaL_checkinteger(L, 2);
	ESpoolPriority priority = (ESpoolPriority)luaL_checkinteger(L, 3);

	auto rman = SpoolableResourceManager::GetInstance();
	if (rman != NULL)
	{
		char in_mav2buffer[12];
		memset(&in_mav2buffer, 0, 12);

		rman->RequestEntity(pkg, entity, (int)&in_mav2buffer, priority);
	}

	return 0;
}

int lua_IsEntityLoaded(lua_State* L)
{
	bool loaded = false;
	SpooledPackageType pkg = (SpooledPackageType)luaL_checkinteger(L, 1);
	int entity = luaL_checkinteger(L, 2);

	auto rman = SpoolableResourceManager::GetInstance();
	if (rman != NULL)
	{
		loaded = rman->IsEntityLoaded(pkg, entity);
	}

	lua_pushboolean(L, loaded);
	return 1;
}

int lua_IsEntityPresent(lua_State* L)
{
	bool loaded = false;
	SpooledPackageType pkg = (SpooledPackageType)luaL_checkinteger(L, 1);
	int entity = luaL_checkinteger(L, 2);

	auto rman = SpoolableResourceManager::GetInstance();
	if (rman != NULL)
	{
		loaded = rman->IsEntityPresent(pkg, entity);
	}

	lua_pushboolean(L, loaded);
	return 1;
}