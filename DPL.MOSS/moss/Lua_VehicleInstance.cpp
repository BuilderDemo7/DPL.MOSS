#include "Lua_VehicleInstance.h"

const char* g_VehicleInstanceMetaName = "Vehicle_LifeInstance";

void Init_Lua_MetaTable_VehicleInstance()
{
	luaL_newmetatable(L, g_VehicleInstanceMetaName);

	// set __index
	lua_pushcfunction(L, lua_VehicleInstanceIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_VehicleInstanceIndex(lua_State* L)
{
	CLifeInstance_Vehicle* ivehicle = *(CLifeInstance_Vehicle**)luaL_checkudata(L, 1, g_VehicleInstanceMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetInstance") == 0) {
		lua_pushcfunction(L, lua_GetVehicleInstance);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetVehicleInstancePointer);
		return 1;
	}
	else if (strcmp(key, "SetMustangHandling") == 0) {
		lua_pushcfunction(L, lua_SetVehicleMustangHandling);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

// disabled
/*
int lua_SetVehicleInstancePosition(lua_State* L)
{
	// TODO
	return 0;
}

int lua_GetVehicleInstancePosition(lua_State* L)
{
	// TODO
	return 0;
}
*/

int lua_GetVehicleInstance(lua_State* L)
{
	CLifeInstance_Vehicle* ivehicle = *(CLifeInstance_Vehicle**)luaL_checkudata(L, 1, g_VehicleInstanceMetaName);
	
	CVehicle* retVeh = ivehicle->m_piVehicle;

	// allocate userdata to hold the pointer
	CVehicle** udata = (CVehicle**)lua_newuserdata(L, sizeof(CCharacter*));
	*udata = retVeh;

	// attach the vehicle metatable
	luaL_getmetatable(L, g_VehicleMetaName);
	lua_setmetatable(L, -2);
	
	return 1;
}

int lua_GetVehicleInstancePointer(lua_State* L)
{
	CLifeInstance_Vehicle* ivehicle = *(CLifeInstance_Vehicle**)luaL_checkudata(L, 1, g_VehicleInstanceMetaName);

	lua_pushinteger(L, (int)ivehicle);

	return 1;
}

int lua_SetVehicleMustangHandling(lua_State* L)
{
	CLifeInstance_Vehicle* ivehicle = *(CLifeInstance_Vehicle**)luaL_checkudata(L, 1, g_VehicleInstanceMetaName);

	bool bOn = lua_toboolean(L, 2);

	ivehicle->SetMustangHandling(bOn);

	return 0;
}