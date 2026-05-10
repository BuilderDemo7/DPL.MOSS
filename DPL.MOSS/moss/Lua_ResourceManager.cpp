#include "Lua_ResourceManager.h"
#include "..\dpl\CLifeSystem.h"
#include "..\dpl\Vector.h"

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
		Vector mav2_pos = Vector();
		Vector4 playerPos = Vector4();
		if (CLifeSystem::GetInstance() != NULL)
			CLifeSystem::GetInstance()->GetPlayer()->GetDriverBehaviour()->GetCharacter()->GetPosition(&playerPos);
		
		mav2_pos.X = playerPos.X;
		mav2_pos.Y = playerPos.Z;

		rman->RequestEntity(pkg, entity, (int)&mav2_pos, priority);
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