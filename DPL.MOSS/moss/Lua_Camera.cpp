#include "Lua_Camera.h"
#include "..\dpl\Factory.h"
#include "Lua_LifeActor.h"

#include "..\dpl\MathFuncs.h"

const char* g_CameraMetaName = "Camera";

void Init_Lua_MetaTable_Camera()
{
	luaL_newmetatable(L, g_CameraMetaName);

	// set __index
	lua_pushcfunction(L, lua_CameraIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_CameraIndex(lua_State* L)
{
	CLifeActor_Camera* camera = *(CLifeActor_Camera**)luaL_checkudata(L, 1, g_CameraMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetCameraPointer);
		return 1;
	}
	else if (strcmp(key, "GetAttachedActor") == 0) {
		lua_pushcfunction(L, lua_GetCameraAttachedTo);
		return 1;
	}
	else if (strcmp(key, "GetAttachedActorPointer") == 0) {
		lua_pushcfunction(L, lua_GetCameraAttachedToPointer);
		return 1;
	}
	else if (strcmp(key, "GetLookAtActor") == 0) {
		lua_pushcfunction(L, lua_GetCameraAttachedTo);
		return 1;
	}
	else if (strcmp(key, "GetLookAtActorPointer") == 0) {
		lua_pushcfunction(L, lua_GetCameraAttachedToPointer);
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
	else if (strcmp(key, "GetLookAtActor") == 0) {
		lua_pushcfunction(L, lua_GetCameraAttachedTo);
		return 1;
	}
	else if (strcmp(key, "GetLookAtActorPointer") == 0) {
		lua_pushcfunction(L, lua_GetCameraAttachedToPointer);
		return 1;
	}
	else if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetCameraActorPosition);
		return 1;
	}
	else if (strcmp(key, "SetRotation") == 0) {
		lua_pushcfunction(L, lua_SetCameraActorRotation);
		return 1;
	}
	else if (strcmp(key, "hamsterFactoryType") == 0 || strcmp(key, "FactoryType") == 0) {
		int facType = -1;

		CLifeActor* actor = ((CLifeActor*)camera);
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

int lua_SetCameraActorPosition(lua_State* L)
{
	CLifeActor_Camera* camera = *(CLifeActor_Camera**)luaL_checkudata(L, 1, g_CameraMetaName);

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
	camera->m_matrix.pos = Vector(x, y, z);
	if (camera->m_pCamera != NULL)
	{
		unsigned int vtable = *(unsigned int*)camera->m_pCamera;

		Matrix* mt = NULL;

		switch (vtable)
		{
		case 0x6501e4: // _vt$12CFixedCamera
		{
			mt = (Matrix*)(((int)camera->m_pCamera) + 0x10);
			break;
		}
		}

		if (mt != NULL)
		{
			mt->pos = camera->m_matrix.pos;
		}
	}

	return 0;  // number of return(s)
}

int lua_SetCameraActorRotation(lua_State* L)
{
	CLifeActor_Camera* camera = *(CLifeActor_Camera**)luaL_checkudata(L, 1, g_CameraMetaName);

	Lua_Quaternion* q = *(Lua_Quaternion**)luaL_checkudata(L, 2, g_LuaQuaternionMetaTable);
	
	Vector4 rotation = Vector4(q->X, q->Y, q->Z, q->W);
	
	Matrix mtx = math_initFromQandV3(&rotation, camera->m_matrix.pos);

	camera->m_matrix = mtx;
	if (camera->m_pCamera != NULL)
	{
		unsigned int vtable = *(unsigned int*)camera->m_pCamera;

		Matrix* mt = NULL;

		switch (vtable)
		{
		case 0x6501e4: // _vt$12CFixedCamera
		{
			mt = (Matrix*)(((int)camera->m_pCamera) + 0x10);
			break;
		}
		}

		if (mt != NULL)
		{
			mt->forward = camera->m_matrix.forward;
			mt->up = camera->m_matrix.up;
			mt->right = camera->m_matrix.right;
			mt->pos = camera->m_matrix.pos;
		}
	}

	return 0;  // number of return(s)
}

int lua_GetCameraAttachedTo(lua_State* L)
{
	CLifeActor_Camera* camera = *(CLifeActor_Camera**)luaL_checkudata(L, 1, g_CameraMetaName);
	CLifeActor* actor = camera->m_pAttachTo;
	if (actor != NULL)
	{
		Lua_LifeActorInfo info = GetLuaLifeActor(actor);

		luaL_getmetatable(L, info.m_pszMetaTableName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_GetCameraAttachedToPointer(lua_State* L)
{
	CLifeActor_Camera* camera = *(CLifeActor_Camera**)luaL_checkudata(L, 1, g_CameraMetaName);
	CLifeActor* actor = camera->m_pAttachTo;

	lua_pushinteger(L, (int)actor);

	return 1;
}

int lua_GetCameraLookAt(lua_State* L)
{
	CLifeActor_Camera* camera = *(CLifeActor_Camera**)luaL_checkudata(L, 1, g_CameraMetaName);
	CLifeActor* actor = camera->m_pLookAt;
	if (actor != NULL)
	{
		Lua_LifeActorInfo info = GetLuaLifeActor(actor);

		luaL_getmetatable(L, info.m_pszMetaTableName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_GetCameraLookAtPointer(lua_State* L)
{
	CLifeActor_Camera* camera = *(CLifeActor_Camera**)luaL_checkudata(L, 1, g_CameraMetaName);
	CLifeActor* actor = camera->m_pLookAt;

	lua_pushinteger(L, (int)actor);

	return 1;
}

int lua_GetCameraPointer(lua_State* L)
{
	CLifeActor_Camera* camera = *(CLifeActor_Camera**)luaL_checkudata(L, 1, g_CameraMetaName);

	lua_pushinteger(L, (int)camera);

	return 1;
}

int lua_CreateCamera(lua_State* L)
{
	int nargs = lua_gettop(L);

	float x, y, z = 0;
	CLifeActor** attachTo = (CLifeActor**)lua_checklifeactor(L, 3, false);
	CLifeActor** lookAt = (CLifeActor**)lua_checklifeactor(L, 4, false);

	CLifeActor* pAttachTo = NULL;
	CLifeActor* pLookAt = NULL;

	if (attachTo)
		pAttachTo = *attachTo;
	if (lookAt)
		pLookAt = *lookAt;

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

	CLifeActor_Camera* camera = (CLifeActor_Camera*)hamster::CreateObject(EFactoryType::EFactoryType_LifeActor_Camera);

	if (camera != NULL)
	{
		Matrix mtx = math_initFromQandV3(&rotation, Vector(x,y,z));

		//mtx.forward = Vector(0, 0, 1);
		//mtx.right = Vector(0, 1, 0);
		//mtx.up = Vector(1, 0, 0);

		/*
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

		// TODO: find a way to fix the camera projection, the sky goes black but the direction is correct
		mtx.forward.X = -mtx.forward.X;
		mtx.forward.Z = -mtx.forward.Z;

		mtx.right.X = -mtx.right.X;
		mtx.right.Z = -mtx.right.Z;

		mtx.forward.Normalise();
		mtx.right.Normalise();
		mtx.up.Normalise();

		*/
		mtx.pos = Vector(x, y, z);

		camera->CustomInitalise(mtx, pAttachTo, pLookAt);

		CLifeActor_Camera** udata = (CLifeActor_Camera**)lua_newuserdata(L, sizeof(void*));
		*udata = camera;

		luaL_getmetatable(L, g_CameraMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}