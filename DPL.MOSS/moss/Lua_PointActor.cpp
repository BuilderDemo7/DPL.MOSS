#include "Lua_PointActor.h"
#include "..\dpl\Vector4.h"
#include "..\dpl\Factory.h"
#include "..\dpl\MathFuncs.h"

const char* g_PointActorMetaName = "Point_Actor";

void Init_Lua_MetaTable_PointActor()
{
	luaL_newmetatable(L, g_PointActorMetaName);

	// set __index
	lua_pushcfunction(L, lua_PointActorIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_PointActorIndex(lua_State* L)
{
	CLifeActor_Marker* ptMarker = *(CLifeActor_Marker**)luaL_checkudata(L, 1, g_PointActorMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetPointActorPosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetPointActorPosition);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetPointActorPointer);
		return 1;
	}
	else if (strcmp(key, "SetHeading") == 0 || strcmp(key, "SetAngle") == 0) {
		lua_pushcfunction(L, lua_SetPointActorHeading);
		return 1;
	}
	else if (strcmp(key, "GetHeading") == 0 || strcmp(key, "GetAngle") == 0) {
		lua_pushcfunction(L, lua_GetPointActorHeading);
		return 1;
	}
	else if (strcmp(key, "GetRotation") == 0) {
		lua_pushcfunction(L, lua_GetPointActorRotation);
		return 1;
	}
	else if (strcmp(key, "SetRotation") == 0) {
		lua_pushcfunction(L, lua_SetPointActorRotation);
		return 1;
	}
	else if (strcmp(key, "GetForwardVector") == 0 || strcmp(key, "GetForward") == 0) {
		lua_pushcfunction(L, lua_GetPointActorForwardVector);
		return 1;
	}
	else if (strcmp(key, "GetRightVector") == 0 || strcmp(key, "GetRight") == 0) {
		lua_pushcfunction(L, lua_GetPointActorRightVector);
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
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_GetPointActorRotation(lua_State* L)
{
	CLifeActor_Marker* ptMarker = *(CLifeActor_Marker**)luaL_checkudata(L, 1, g_PointActorMetaName);

	Matrix mat = ptMarker->m_matrix;

	Vector4 maQ = math_construct_quaternion(&mat);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Quaternion();

	Lua_Quaternion* vecRes = *(Lua_Quaternion**)udata;

	vecRes->X = maQ.X;
	vecRes->Y = maQ.Y;
	vecRes->Z = maQ.Z;
	vecRes->W = maQ.W;

	luaL_getmetatable(L, g_LuaQuaternionMetaTable);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_SetPointActorRotation(lua_State* L)
{
	CLifeActor_Marker* ptMarker = *(CLifeActor_Marker**)luaL_checkudata(L, 1, g_PointActorMetaName);

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

	Matrix mat = ptMarker->m_matrix;

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

	ptMarker->m_matrix = m;

	return 0;
}

int lua_CreatePoint(lua_State* L)
{
	int nargs = lua_gettop(L);

	float x, y, z = 0;
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
	
	CLifeActor_Marker* ptMarker = (CLifeActor_Marker*)hamster::CreateObject(EFactoryType::EFactoryType_LifeActor_Marker);

	if (ptMarker != NULL)
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

		ptMarker->CustomInitalise(mtx);

		// just making sure...
		ptMarker->m_matrix.pos = Vector(x, y, z);

		CLifeActor_Marker** udata = (CLifeActor_Marker**)lua_newuserdata(L, sizeof(void*));
		*udata = ptMarker;

		luaL_getmetatable(L, g_PointActorMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		//((CLifeActor*)ptMarker)->Create();

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_SetPointActorPosition(lua_State* L)
{
	CLifeActor_Marker* ptMarker = *(CLifeActor_Marker**)luaL_checkudata(L, 1, g_PointActorMetaName);

	Matrix mat = ptMarker->m_matrix;

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
	mat.pos = Vector(pos.X, pos.Y, pos.Z);
	ptMarker->m_matrix = mat;

	return 0;
}

int lua_GetPointActorPosition(lua_State* L)
{
	CLifeActor_Marker* ptMarker = *(CLifeActor_Marker**)luaL_checkudata(L, 1, g_PointActorMetaName);

	Matrix mat = ptMarker->m_matrix;

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = Vector4(mat.pos.X, mat.pos.Y, mat.pos.Z, 1);
	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_GetPointActorPointer(lua_State* L)
{
	CLifeActor_Marker* ptMarker = *(CLifeActor_Marker**)luaL_checkudata(L, 1, g_PointActorMetaName);

	lua_pushinteger(L, (int)ptMarker);

	return 1;
}

int lua_SetPointActorHeading(lua_State* L)
{
	CLifeActor_Marker* ptMarker = *(CLifeActor_Marker**)luaL_checkudata(L, 1, g_PointActorMetaName);

	Matrix mat = ptMarker->m_matrix;

	float angle = luaL_checknumber(L, 2);

	float fx = sin(angle);
	float fz = cos(angle);

	mat.forward = Vector(fx, 0, fz);
	mat.right = CrossProduct(Vector(0, 1, 0), mat.forward);
	mat.up = CrossProduct(mat.forward, mat.right);

	ptMarker->m_matrix = mat;

	return 0;
}

int lua_GetPointActorHeading(lua_State* L)
{
	return 0;
}

int lua_GetPointActorForwardVector(lua_State* L)
{
	return 0;
}

int lua_GetPointActorRightVector(lua_State* L)
{
	return 0;
}