#include "Lua_Prop.h"
#include "..\dpl\Vector4.h"
#include "..\dpl\Factory.h"

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
	else if (strcmp(key, "GetForwardVector") == 0 || strcmp(key, "GetForward") == 0) {
		lua_pushcfunction(L, lua_GetPropForwardVector);
		return 1;
	}
	else if (strcmp(key, "GetRightVector") == 0 || strcmp(key, "GetRight") == 0) {
		lua_pushcfunction(L, lua_GetPropRightVector);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_CreateProp(lua_State* L)
{
	int nargs = lua_gettop(L);

	float x, y, z = 0;
	EGadgetType gadget = EGadgetType::VENDERDONUTS;
	bool canBeTargeted = false;

	Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable);
	x = vec->X;
	y = vec->Y;
	z = vec->Z;

	gadget = (EGadgetType)luaL_checkinteger(L, 2);
	if (nargs > 2)
		canBeTargeted = lua_toboolean(L, 3);

	CLifeActor_Prop* prop = (CLifeActor_Prop*)hamster::CreateObject(EFactoryType::EFactoryType_LifeActor_Prop);

	if (prop != NULL)
	{
		Matrix mtx = Matrix();
		mtx.forward = Vector(0, 0, 1);
		mtx.right = Vector(0, 1, 0);
		mtx.up = Vector(1, 0, 0);
		mtx.pos = Vector(x, y, z);

		prop->CustomInitalise(mtx, gadget, canBeTargeted);

		CLifeActor_Prop** udata = (CLifeActor_Prop**)lua_newuserdata(L, sizeof(void*));
		*udata = prop;

		luaL_getmetatable(L, g_PropMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		// instantiate it (create)
		((CLifeActor*)prop)->Create();

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_SetPropPosition(lua_State* L)
{
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

	return 0;
}

int lua_GetPropPointer(lua_State* L)
{
	CLifeActor_Prop* prop = *(CLifeActor_Prop**)luaL_checkudata(L, 1, g_PropMetaName);

	lua_pushinteger(L, (int)prop);

	return 1;
}

int lua_SetPropHeading(lua_State* L)
{
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