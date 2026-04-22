#include "Lua_TestVolume.h"
#include "..\dpl\Vector4.h"
#include "..\dpl\Factory.h"
#include "..\dpl\MathFuncs.h"

const char* g_TestVolumeMetaName = "TestVolume";

void Init_Lua_MetaTable_TestVolume()
{
	luaL_newmetatable(L, g_TestVolumeMetaName);

	// set __index
	lua_pushcfunction(L, lua_TestVolumeIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_TestVolumeIndex(lua_State* L)
{
	CLifeActor_TestVolume* tVolume = *(CLifeActor_TestVolume**)luaL_checkudata(L, 1, g_TestVolumeMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetTestVolumePosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetTestVolumePosition);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetTestVolumePointer);
		return 1;
	}
	else if (strcmp(key, "SetHeading") == 0 || strcmp(key, "SetAngle") == 0) {
		lua_pushcfunction(L, lua_SetTestVolumeHeading);
		return 1;
	}
	else if (strcmp(key, "GetHeading") == 0 || strcmp(key, "GetAngle") == 0) {
		lua_pushcfunction(L, lua_GetTestVolumeHeading);
		return 1;
	}
	else if (strcmp(key, "GetRotation") == 0) {
		lua_pushcfunction(L, lua_GetTestVolumeRotation);
		return 1;
	}
	else if (strcmp(key, "SetRotation") == 0) {
		lua_pushcfunction(L, lua_SetTestVolumeRotation);
		return 1;
	}
	else if (strcmp(key, "IsInside") == 0) {
		lua_pushcfunction(L, lua_TestVolumeIsPositionInside);
		return 1;
	}
	else if (strcmp(key, "GetForwardVector") == 0 || strcmp(key, "GetForward") == 0) {
		lua_pushcfunction(L, lua_GetTestVolumeForwardVector);
		return 1;
	}
	else if (strcmp(key, "GetRightVector") == 0 || strcmp(key, "GetRight") == 0) {
		lua_pushcfunction(L, lua_GetTestVolumeRightVector);
		return 1;
	}
	// LifeActor generic methods
	else if (strcmp(key, "AddObjectiveIcon") == 0) {
		lua_pushcfunction(L, lua_AddObjectiveIconToLifeActor);
		return 1;
	}
	else if (strcmp(key, "RemoveObjectiveIcon") == 0) {
		lua_pushcfunction(L, lua_RemoveObjectiveIconFromLifeActor);
		return 1;
	}
	else if (strcmp(key, "hamsterFactoryType") == 0 || strcmp(key, "FactoryType") == 0) {
		int facType = -1;

		CLifeActor* actor = ((CLifeActor*)tVolume);
		if (actor != NULL)
			facType = actor->hamsterFactoryType();

		lua_pushinteger(L, facType);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_TestVolumeIsPositionInside(lua_State* L)
{
	CLifeActor_TestVolume* tVolume = *(CLifeActor_TestVolume**)luaL_checkudata(L, 1, g_TestVolumeMetaName);

	float x, y, z = 0;
	Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable);
	x = vec->X;
	y = vec->Y;
	z = vec->Z;

	void* zone = tVolume->m_piZone;
	if (zone != NULL)
	{
		Vector4 pos = Vector4(x, y, z, 1);

		// Inside__C20CLifeInstance_VolumeRC4MAv4
		((void(__thiscall*)(void*, Vector4*))0x483037)(zone, &pos);
	}

	return 0;
}

int lua_GetTestVolumeRotation(lua_State* L)
{
	return 0;
}

int lua_SetTestVolumeRotation(lua_State* L)
{
	return 0;
}

int lua_CreateTestVolume(lua_State* L)
{
	int nargs = lua_gettop(L);

	float x, y, z = 0;
	
	int primType = 1; // cylinder = default
	float widthOrRadius = 2.5f;
	float length = 0.0f;
	float fHeight = 5.0f;

	primType = luaL_optinteger(L, 3, 1);
	widthOrRadius = luaL_optnumber(L, 4, 2.5f);
	length = luaL_optnumber(L, 5, 0.0f);
	fHeight = luaL_optnumber(L, 6, 5.0f);

	CLifeActor** actorRef = (CLifeActor**)lua_touserdata(L, 7);

	CLifeActor* pActorRef = NULL;

	if (actorRef != NULL)
		pActorRef = *actorRef;

	Vector4 rotation = Vector4();

	Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable);
	x = vec->X;
	y = vec->Y;
	z = vec->Z;

	if (nargs > 1)
	{
		Lua_Quaternion* qua = *(Lua_Quaternion**)luaL_checkudata(L, 2, g_LuaQuaternionMetaTable);
		rotation.X = qua->X;
		rotation.Y = qua->Y;
		rotation.Z = qua->Z;
		rotation.W = qua->W;
	}

	CLifeActor_TestVolume* tVolume = (CLifeActor_TestVolume*)hamster::CreateObject(EFactoryType::EFactoryType_LifeActor_TestVolume);

	if (tVolume != NULL)
	{
		Matrix mtx = Matrix();

		//mtx.forward = Vector(0, 0, 1);
		//mtx.right = Vector(0, 1, 0);
		//mtx.up = Vector(1, 0, 0);

		float xx = rotation.X * rotation.X;
		float yy = rotation.Y * rotation.Y;
		float zz = rotation.Z * rotation.Z;
		float xy = rotation.X * rotation.Y;
		float xz = rotation.X * rotation.Z;
		float yz = rotation.Y * rotation.Z;
		float wx = rotation.W * rotation.X;
		float wy = rotation.W * rotation.Y;
		float wz = rotation.W * rotation.Z;

		mtx.right.X = 1.0f - 2.0f * (yy + zz);
		mtx.right.Y = 2.0f * (xy + wz);
		mtx.right.Z = 2.0f * (xz - wy);

		mtx.up.X = 2.0f * (xy - wz);
		mtx.up.Y = 1.0f - 2.0f * (xx + zz);
		mtx.up.Z = 2.0f * (yz + wx);

		mtx.forward.X = 2.0f * (xz + wy);
		mtx.forward.Y = 2.0f * (yz - wx);
		mtx.forward.Z = 1.0f - 2.0f * (xx + yy);

		mtx.pos = Vector(x, y, z);

		SPrimitiveData data = SPrimitiveData();
		data.eType = (EPrimitiveType)primType;
		data.fWidthOrRadius = widthOrRadius;
		data.fHeight = fHeight;
		data.fLength = length;

		tVolume->CustomInitalise(mtx, data, pActorRef);

		CLifeActor_TestVolume** udata = (CLifeActor_TestVolume**)lua_newuserdata(L, sizeof(void*));
		*udata = tVolume;

		luaL_getmetatable(L, g_TestVolumeMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		((CLifeActor*)tVolume)->Create();

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_SetTestVolumePosition(lua_State* L)
{
	// TODO
	return 0;
}

int lua_GetTestVolumePosition(lua_State* L)
{
	// TODO
	return 0;
}

int lua_GetTestVolumePointer(lua_State* L)
{
	CLifeActor_TestVolume* tVolume = *(CLifeActor_TestVolume**)luaL_checkudata(L, 1, g_TestVolumeMetaName);

	lua_pushinteger(L, (int)tVolume);

	return 1;
}

int lua_SetTestVolumeHeading(lua_State* L)
{
	// TODO
	return 0;
}

int lua_GetTestVolumeHeading(lua_State* L)
{
	// TODO
	return 0;
}

int lua_GetTestVolumeForwardVector(lua_State* L)
{
	// TODO
	return 0;
}

int lua_GetTestVolumeRightVector(lua_State* L)
{
	// TODO
	return 0;
}