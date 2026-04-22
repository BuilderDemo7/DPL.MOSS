#include "Lua_Prop.h"
#include "..\dpl\Vector4.h"
#include "..\dpl\Factory.h"
#include "..\dpl\CGadgetHandler.h"
#include "..\dpl\MathFuncs.h"

const char* g_PropMetaName = "Prop";

void Init_Lua_MetaTable_Prop()
{
	luaL_newmetatable(L, g_PropMetaName);

	// set __index
	lua_pushcfunction(L, lua_PropIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_PropIndex(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetPropPosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetPropPosition);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetPropPointer);
		return 1;
	}
	else if (strcmp(key, "GetModelHandle") == 0) {
		lua_pushcfunction(L, lua_GetPropModelHandle);
		return 1;
	}
	else if (strcmp(key, "SetModelHandle") == 0) {
		lua_pushcfunction(L, lua_SetPropModelHandle);
		return 1;
	}
	else if (strcmp(key, "SetGadgetType") == 0) {
		lua_pushcfunction(L, lua_SetPropGadgetType);
		return 1;
	}
	else if (strcmp(key, "Create") == 0 || strcmp(key, "Instantiate") == 0) {
		lua_pushcfunction(L, lua_InstantiateProp);
		return 1;
	}
	else if (strcmp(key, "Destroy") == 0 || strcmp(key, "Delete") == 0) {
		lua_pushcfunction(L, lua_DeleteProp);
		return 1;
	}
	else if (strcmp(key, "SetHeading") == 0 || strcmp(key, "SetAngle") == 0) {
		lua_pushcfunction(L, lua_SetPropHeading);
		return 1;
	}
	else if (strcmp(key, "GetHeading") == 0 || strcmp(key, "GetAngle") == 0) {
		lua_pushcfunction(L, lua_GetPropHeading);
		return 1;
	}
	else if (strcmp(key, "GetVelocity") == 0) {
		lua_pushcfunction(L, lua_GetPropVelocity);
		return 1;
	}
	else if (strcmp(key, "SetVelocity") == 0) {
		lua_pushcfunction(L, lua_SetPropVelocity);
		return 1;
	}
	else if (strcmp(key, "GetRotation") == 0) {
		lua_pushcfunction(L, lua_GetPropRotation);
		return 1;
	}
	else if (strcmp(key, "SetRotation") == 0) {
		lua_pushcfunction(L, lua_SetPropRotation);
		return 1;
	}
	else if (strcmp(key, "Created") == 0) {
		lua_pushboolean(L, prop->m_bCreated);
		return 1;
	}
	else if (strcmp(key, "GetForwardVector") == 0 || strcmp(key, "GetForward") == 0) {
		lua_pushcfunction(L, lua_GetPropForwardVector);
		return 1;
	}
	else if (strcmp(key, "GetRightVector") == 0 || strcmp(key, "GetRight") == 0) {
		lua_pushcfunction(L, lua_GetPropRightVector);
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

		CLifeActor* actor = ((CLifeActor*)prop);
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

int lua_InstantiateProp(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	//if (!prop->m_bCreated)
		((CLifeActor*)prop)->Create();

	return 0;
}

int lua_DeleteProp(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	//if (prop->m_bCreated)
		((CLifeActor*)prop)->Delete();

	return 0;
}

int lua_SetPropModelHandle(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	int handle = luaL_checkinteger(L, 2);

	prop->m_propModelHandle = handle;

	return 0;
}

int lua_SetPropGadgetType(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	int gadgetType = luaL_checkinteger(L, 2);

	prop->m_propModelHandle = CGadgetHandler::GetInstance()->GetGadgetModelHandle((EGadgetType)gadgetType);

	return 0;
}

int lua_GetPropModelHandle(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	int handle = prop->m_propModelHandle;

	lua_pushinteger(L, handle);

	return 1;
}

int lua_GetPropRotation(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	Matrix mat = ((CLifeActor*)prop)->GetMatrix();

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

int lua_SetPropRotation(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

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

	Matrix mat = ((CLifeActor*)prop)->GetMatrix();

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

	prop->m_matrix = m;
	//if (prop->m_bCreated)
		prop->Move(prop->m_matrix);

	return 0;
}

int lua_CreateProp(lua_State* L)
{
	int nargs = lua_gettop(L);

	float x, y, z = 0;
	EGadgetType gadget = EGadgetType::VENDERDONUTS;
	Vector4 rotation = Vector4();
	bool canBeTargeted = false;
	bool startCreated = true;

	Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable);
	x = vec->X;
	y = vec->Y;
	z = vec->Z;

	gadget = (EGadgetType)luaL_checkinteger(L, 2);
	if (nargs > 2)
	{
		Lua_Quaternion* qua = *(Lua_Quaternion**)luaL_checkudata(L, 3, g_LuaQuaternionMetaTable);
		rotation.X = qua->X;
		rotation.Y = qua->Y;
		rotation.Z = qua->Z;
		rotation.W = qua->W;
	}
	if (nargs > 3)
		canBeTargeted = lua_toboolean(L, 4);
	if (nargs > 4)
		startCreated = lua_toboolean(L, 5);

	CLifeActor_Prop* prop = (CLifeActor_Prop*)hamster::CreateObject(EFactoryType::EFactoryType_LifeActor_Prop);

	if (prop != NULL)
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

		prop->CustomInitalise(mtx, gadget, canBeTargeted);

		CLifeActor_Prop** udata = (CLifeActor_Prop**)lua_newuserdata(L, sizeof(void*));
		*udata = prop;

		luaL_getmetatable(L, g_PropMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		if (startCreated)
		{
			// instantiate it (create)
			((CLifeActor*)prop)->Create();
		}

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_SetPropPosition(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	Matrix mat = ((CLifeActor*)prop)->GetMatrix();

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
	prop->m_matrix = mat;

	//if (prop->m_bCreated)
		prop->Move(prop->m_matrix);

	return 0;
}

int lua_GetPropPosition(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	Matrix mat = ((CLifeActor*)prop)->GetMatrix();

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

int lua_GetPropPointer(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	lua_pushinteger(L, (int)prop);

	return 1;
}

int lua_SetPropHeading(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	Matrix mat = ((CLifeActor*)prop)->GetMatrix();

	float angle = luaL_checknumber(L, 2);

	float fx = sin(angle);
	float fz = cos(angle);

	mat.forward = Vector(fx, 0, fz);
	mat.right = CrossProduct(Vector(0, 1, 0), mat.forward);
	mat.up = CrossProduct(mat.forward, mat.right);

	prop->m_matrix = mat;

	//if (prop->m_bCreated)
		prop->Move(prop->m_matrix);

	return 0;
}

int lua_GetPropHeading(lua_State* L)
{
	return 0;
}

int lua_GetPropVelocity(lua_State* L)
{
	return 0;
}

int lua_SetPropVelocity(lua_State* L)
{
	return 0;
}

int lua_GetPropForwardVector(lua_State* L)
{
	return 0;
}

int lua_GetPropRightVector(lua_State* L)
{
	return 0;
}