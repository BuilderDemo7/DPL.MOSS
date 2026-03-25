#include "Lua_ObjectiveIcon.h"
#include "..\dpl\CPCViewport.h"

const char* g_ObjectiveIconMetaName = "ObjectiveIcon";

void Init_Lua_MetaTable_ObjectiveIcon()
{
	luaL_newmetatable(L, g_ObjectiveIconMetaName);

	// set __index
	lua_pushcfunction(L, lua_ObjectiveIconIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);

	// Create a table
	lua_newtable(L);

	// Create a metatable
	lua_newtable(L);
	lua_pushcfunction(L, lua_GlobalObjectiveIconModuleIndex);
	lua_setfield(L, -2, "__index");

	// Set the metatable for the table
	lua_setmetatable(L, -2);

	// Push the table to the global scope
	lua_setglobal(L, "ObjectiveIcon");
}

int lua_GlobalObjectiveIconModuleIndex(lua_State* L)
{
	const char* key = lua_tostring(L, 2);

	if (strcmp(key, "new") == 0) {
		lua_pushcfunction(L, lua_ObjectiveIconNew);
	}

	return 1;
}

int lua_ObjectiveIconNew(lua_State* L)
{
	Lua_ObjectiveIcon* oicon = new Lua_ObjectiveIcon();

	Lua_ObjectiveIcon** udata = (Lua_ObjectiveIcon**)lua_newuserdata(L, sizeof(void*));
	*udata = oicon;

	oicon->m_iDisplayType = 20;
	SetupObjectiveIcon(&oicon->m_iconData, oicon->m_iDisplayType, 0);

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_ObjectiveIconIndex(lua_State* L)
{
	Lua_ObjectiveIcon* oicon = *(Lua_ObjectiveIcon**)luaL_checkudata(L, 1, g_ObjectiveIconMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetObjectiveIconPosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetObjectiveIconPosition);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetObjectiveIconPointer);
		return 1;
	}
	else if (strcmp(key, "SetHeading") == 0 || strcmp(key, "SetAngle") == 0) {
		lua_pushcfunction(L, lua_SetObjectiveIconHeading);
		return 1;
	}
	else if (strcmp(key, "GetHeading") == 0 || strcmp(key, "GetAngle") == 0) {
		lua_pushcfunction(L, lua_GetObjectiveIconHeading);
		return 1;
	}
	else if (strcmp(key, "SetType") == 0) {
		lua_pushcfunction(L, lua_SetObjectiveIconType);
		return 1;
	}
	else if (strcmp(key, "GetType") == 0) {
		lua_pushcfunction(L, lua_GetObjectiveIconType);
		return 1;
	}
	else if (strcmp(key, "Draw") == 0 || strcmp(key, "Render") == 0) {
		lua_pushcfunction(L, lua_DrawObjectiveIcon);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_SetObjectiveIconPosition(lua_State* L)
{
	Lua_ObjectiveIcon* oicon = *(Lua_ObjectiveIcon**)luaL_checkudata(L, 1, g_ObjectiveIconMetaName);

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
		return luaL_error(L, "bad argument #1 - Expected 1 Vector or 3 numbers");
	}

	Vector pos = Vector(x, y, z);
	oicon->m_matrix.pos = pos;

	return 0;  // number of return(s)
}

int lua_GetObjectiveIconPosition(lua_State* L)
{
	Lua_ObjectiveIcon* oicon = *(Lua_ObjectiveIcon**)luaL_checkudata(L, 1, g_ObjectiveIconMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = Vector4(oicon->m_matrix.pos.X, oicon->m_matrix.pos.Y, oicon->m_matrix.pos.Z, 1);

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetObjectiveIconPointer(lua_State* L)
{
	Lua_ObjectiveIcon* oicon = *(Lua_ObjectiveIcon**)luaL_checkudata(L, 1, g_ObjectiveIconMetaName);

	lua_pushinteger(L, (int)oicon);

	return 1;
}

int lua_SetObjectiveIconHeading(lua_State* L)
{
	return 0;
}

int lua_GetObjectiveIconHeading(lua_State* L)
{
	return 0;
}

int lua_SetObjectiveIconType(lua_State* L)
{
	Lua_ObjectiveIcon* oicon = *(Lua_ObjectiveIcon**)luaL_checkudata(L, 1, g_ObjectiveIconMetaName);
	int displayType = luaL_checkinteger(L, 2);

	SetupObjectiveIcon(&oicon->m_iconData, displayType, 0);
	oicon->m_iDisplayType = displayType;

	return 0;
}

int lua_GetObjectiveIconType(lua_State* L)
{
	Lua_ObjectiveIcon* oicon = *(Lua_ObjectiveIcon**)luaL_checkudata(L, 1, g_ObjectiveIconMetaName);

	lua_pushinteger(L, oicon->m_iDisplayType);

	return 1;
}

int lua_DrawObjectiveIcon(lua_State* L)
{
	Lua_ObjectiveIcon* oicon = *(Lua_ObjectiveIcon**)luaL_checkudata(L, 1, g_ObjectiveIconMetaName);

	CPCViewport* vp = CPCViewport::GetSimulationViewport();
	if (vp != NULL)
		AutoRenderObjectiveIcon(&oicon->m_iconData, &oicon->m_matrix, vp);

	return 0;
}