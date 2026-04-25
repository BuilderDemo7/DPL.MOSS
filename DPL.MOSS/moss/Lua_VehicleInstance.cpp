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
	else if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetVehicleInstancePosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetVehicleInstancePosition);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_SetVehicleInstancePosition(lua_State* L)
{
	CLifeInstance_Vehicle* ivehicle = *(CLifeInstance_Vehicle**)luaL_checkudata(L, 1, g_VehicleInstanceMetaName);

	int nargs = lua_gettop(L) - 1; // number of arguments after 'self'

	float x, y, z;

	if (nargs == 1) {
		// Single argument: expect a Vector
		Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 2, g_LuaVectorMetaTable);
		x = vec->X;
		y = vec->Y;
		z = vec->Z;
	}
	else if (nargs == 3) {
		// Three numbers
		x = (float)luaL_checknumber(L, 2);
		y = (float)luaL_checknumber(L, 3);
		z = (float)luaL_checknumber(L, 4);
	}
	else {
		return luaL_error(L, "Expected 1 Vector or 3 numbers");
	}

	Vector4 pos = Vector4(x, y, z, 1);
	*(Vector4*)(ivehicle + 0x2a8) = pos; // m_initialPosition

	if (ivehicle->m_piVehicle != NULL)
	{
		ivehicle->m_piVehicle->SetPosition(&pos);
	}

	return 0;  // number of return(s)
}

int lua_GetVehicleInstancePosition(lua_State* L)
{
	CLifeInstance_Vehicle* ivehicle = *(CLifeInstance_Vehicle**)luaL_checkudata(L, 1, g_VehicleInstanceMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = ivehicle->GetPosition();

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetVehicleInstance(lua_State* L)
{
	CLifeInstance_Vehicle* ivehicle = *(CLifeInstance_Vehicle**)luaL_checkudata(L, 1, g_VehicleInstanceMetaName);
	
	CVehicle* retVeh = ivehicle->m_piVehicle;

	if (retVeh == NULL)
	{
		lua_pushnil(L);
		return 1;
	}

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