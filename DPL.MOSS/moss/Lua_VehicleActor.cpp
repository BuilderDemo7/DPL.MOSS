#include "Lua_VehicleActor.h"
#include "..\dpl\Factory.h"
#include "..\dpl\MathFuncs.h"

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
	else if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetVehicleActorPosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetVehicleActorPosition);
		return 1;
	}
	else if (strcmp(key, "SetRotation") == 0) {
		lua_pushcfunction(L, lua_SetVehicleActorRotation);
		return 1;
	}
	else if (strcmp(key, "GetRotation") == 0) {
		lua_pushcfunction(L, lua_GetVehicleActorRotation);
		return 1;
	}
	else if (strcmp(key, "GetForwardVector") == 0 || strcmp(key, "GetForward") == 0) {
		lua_pushcfunction(L, lua_GetVehicleActorForwardVector);
		return 1;
	}
	else if (strcmp(key, "GetRightVector") == 0 || strcmp(key, "GetRight") == 0) {
		lua_pushcfunction(L, lua_GetVehicleActorRightVector);
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

int lua_GetVehicleActorForwardVector(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 fwd = Vector4();
	Matrix mt = avehicle->GetMatrix();

	fwd.X = mt.forward.X;
	fwd.Y = mt.forward.Y;
	fwd.Z = mt.forward.Z;

	vecRes->X = fwd.X;
	vecRes->Y = fwd.Y;
	vecRes->Z = fwd.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetVehicleActorRightVector(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 fwd = Vector4();
	Matrix mt = avehicle->GetMatrix();

	fwd.X = mt.right.X;
	fwd.Y = mt.right.Y;
	fwd.Z = mt.right.Z;

	vecRes->X = fwd.X;
	vecRes->Y = fwd.Y;
	vecRes->Z = fwd.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetVehicleActorPosition(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = avehicle->GetPosition();

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_SetVehicleActorRotation(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);

	Matrix m;
	Lua_Quaternion* q = *(Lua_Quaternion**)luaL_checkudata(L, 2, g_LuaQuaternionMetaTable);

	float xx = q->X * q->X;
	float yy = q->Y * q->Y;
	float zz = q->Z * q->Z;
	float xy = q->X * q->Y;
	float xz = q->X * q->Z;
	float yz = q->Y * q->Z;
	float wx = q->W * q->X;
	float wy = q->W * q->Y;
	float wz = q->W * q->Z;

	Matrix mat = avehicle->GetMatrix();

	m.right.X = 1.0f - 2.0f * (yy + zz);
	m.right.Y = 2.0f * (xy + wz);
	m.right.Z = 2.0f * (xz - wy);

	m.up.X = 2.0f * (xy - wz);
	m.up.Y = 1.0f - 2.0f * (xx + zz);
	m.up.Z = 2.0f * (yz + wx);

	m.forward.X = 2.0f * (xz + wy);
	m.forward.Y = 2.0f * (yz - wx);
	m.forward.Z = 1.0f - 2.0f * (xx + yy);
	m.pos = mat.pos;

	Vector4 vq = Vector4(q->X, q->Y, q->Z, q->W);

	avehicle->m_initialMatrix = m;
	avehicle->m_orientation = vq;

	if (avehicle->m_piVehicleInstance != NULL)
	{
		if (avehicle->m_piVehicleInstance->m_piVehicle != NULL)
		{
			avehicle->m_piVehicleInstance->m_piVehicle->SetDirection(vq);
		}
	}

	return 0;
}

int lua_GetVehicleActorRotation(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Quaternion();

	Lua_Quaternion* vecRes = *(Lua_Quaternion**)udata;

	Matrix m = avehicle->GetMatrix();
	Vector4 q = math_construct_quaternion(&m);

	vecRes->X = q.X;
	vecRes->Y = q.Y;
	vecRes->Z = q.Z;
	vecRes->W = q.W;

	luaL_getmetatable(L, g_LuaQuaternionMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_SetVehicleActorPosition(lua_State* L)
{
	CLifeActor_Vehicle* avehicle = *(CLifeActor_Vehicle**)luaL_checkudata(L, 1, g_VehicleActorMetaName);

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
	avehicle->m_initialMatrix.pos = Vector(x, y, z);
	avehicle->m_initialPosition = pos;
	avehicle->m_pPositionAtStart = pos;

	if (avehicle->m_piVehicleInstance != NULL)
	{
		if (avehicle->m_piVehicleInstance->m_piVehicle != NULL)
		{
			avehicle->m_piVehicleInstance->m_piVehicle->SetPosition(pos);
		}
	}

	return 0;  // number of return(s)
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
		randomTint = lua_toboolean(L, 14);

	bool spoolWithMission = false; // unknown
	bool smashStuff = false;
	if (nargs > 14)
		smashStuff = lua_toboolean(L, 15);

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

		avehicle->CustomInitalise(mat, model, tintValue, initialSpeed, initialFelony, impactSoftness, explosionSoftness, bulletSoftness, impactFragility, attachedVehicle, randomTint, startCreated, spoolWithMission, smashStuff);

		CLifeActor_Vehicle** udata = (CLifeActor_Vehicle**)lua_newuserdata(L, sizeof(void*));
		*udata = avehicle;

		luaL_getmetatable(L, g_VehicleActorMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return


		//if (startCreated)
		//{
			// create instance first which is very important because Create() checks that
			//((CLifeActor*)avehicle)->CreateInstance();

			//((CLifeActor*)avehicle)->Create();
		//}

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
	if (avehicle->m_piVehicleInstance == NULL)
		((CLifeActor*)avehicle)->CreateInstance();

	((CLifeActor*)avehicle)->Create();
	return 0;
}