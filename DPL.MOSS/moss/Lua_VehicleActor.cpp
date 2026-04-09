#include "Lua_VehicleActor.h"
#include "..\dpl\Factory.h"

const char* g_VehicleActorMetaName = "Vehicle_Actor";

void Init_Lua_MetaTable_VehicleActor()
{
	luaL_newmetatable(L, g_VehicleActorMetaName);

	// set __index
	lua_pushcfunction(L, lua_VehicleActorIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_VehicleActorIndex(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetInstance") == 0) {
		lua_pushcfunction(L, lua_GetVehicleActorInstance);
		return 1;
	}
	else if (strcmp(key, "GetLifeInstance") == 0) {
		lua_pushcfunction(L, lua_GetVehicleActorInstance);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetVehicleActorPointer);
		return 1;
	}
	else if (strcmp(key, "Create") == 0 || strcmp(key, "Instantiate") == 0) {
		lua_pushcfunction(L, lua_InstantiateVehicleActor);
		return 1;
	}
	else if (strcmp(key, "Destroy") == 0 || strcmp(key, "Delete") == 0) {
		lua_pushcfunction(L, lua_DestroyVehicleActor);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_GetVehicleActorInstance(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);

	if (avehicle->m_piVehicleInstance == NULL)
	{
		lua_pushnil(L);
		return 1;
	}

	CVehicle* retVeh = avehicle->m_piVehicleInstance->m_piVehicle; // m_piVehicle

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

int lua_GetVehicleActorPointer(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);

	lua_pushinteger(L, (int)avehicle);

	return 1;
}

int lua_CreateVehicleActor(lua_State* L)
{
	int nargs = lua_gettop(L);

	int model;
	float x, y, z;
	float angle;

	model = (int)luaL_checkinteger(L, 1);

	x = (float)luaL_checknumber(L, 2);
	y = (float)luaL_checknumber(L, 3);
	z = (float)luaL_checknumber(L, 4);

	angle = (float)luaL_optnumber(L, 5, 0.0);

	bool startCreated = true;
	if (nargs > 5)
		startCreated = lua_toboolean(L, 6);

	int tintValue = luaL_optinteger(L, 7, 1);
	float initialSpeed = luaL_optnumber(L, 8, 0.0f);
	float initialFelony = luaL_optnumber(L, 9, 0.0f);
	float impactSoftness = luaL_optnumber(L, 10, 1.0f);
	float explosionSoftness = luaL_optnumber(L, 11, 1.0f);
	float bulletSoftness = luaL_optnumber(L, 12, 1.0f);
	float impactFragility = luaL_optnumber(L, 13, 1.0f);

	// for tow truck hooking?
	CLifeActor* attachedVehicle = NULL;

	bool randomTint = false;
	if (nargs > 13)
		startCreated = lua_toboolean(L, 14);

	CLifeActor_Vehicle* avehicle = (CLifeActor_Vehicle*)hamster::CreateObject(EFactoryType::EFactoryType_LifeActor_Vehicle);

	if (avehicle != NULL)
	{
		float fx = sin(angle);
		float fz = cos(angle);

		Matrix mat = Matrix();
		mat.pos = Vector(x, y, z);

		mat.forward = Vector(fx, 0, fz);
		mat.right = CrossProduct(Vector(0, 1, 0), mat.forward);
		mat.up = CrossProduct(mat.forward, mat.right);

		avehicle->CustomInitalise(mat, model, tintValue, initialSpeed, initialFelony, impactSoftness, explosionSoftness, bulletSoftness, impactFragility, attachedVehicle, randomTint, startCreated);

		CLifeActor_Vehicle** udata = (CLifeActor_Vehicle**)lua_newuserdata(L, sizeof(void*));
		*udata = avehicle;

		luaL_getmetatable(L, g_VehicleActorMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		if (startCreated)
			((CLifeActor*)avehicle)->Create();

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_DestroyVehicleActor(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);
	((CLifeActor*)avehicle)->Delete();
	return 0;
}

int lua_InstantiateVehicleActor(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);
	((CLifeActor*)avehicle)->Create();
	return 0;
}