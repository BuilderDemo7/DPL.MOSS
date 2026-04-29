#include "Lua_CharacterInstance.h"

const char* g_CharacterInstanceMetaName = "Character_LifeInstance";

void Init_Lua_MetaTable_CharacterInstance()
{
	luaL_newmetatable(L, g_CharacterInstanceMetaName);

	// set __index
	lua_pushcfunction(L, lua_CharacterInstanceIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_CharacterInstanceIndex(lua_State* L)
{
	CLifeInstance_Character* icharacter = *(CLifeInstance_Character**)luaL_checkudata(L, 1, g_CharacterInstanceMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetInstance") == 0) {
		lua_pushcfunction(L, lua_GetCharacterInstance);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetCharacterInstancePointer);
		return 1;
	}
	else if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetCharacterInstancePosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetCharacterInstancePosition);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_SetCharacterInstancePosition(lua_State* L)
{
	CLifeInstance_Character* icharacter = *(CLifeInstance_Character**)luaL_checkudata(L, 1, g_CharacterInstanceMetaName);

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
	icharacter->m_initialPosition = pos;
	icharacter->SetSpoolPosition(&pos);

	if (icharacter->m_piCharacter != NULL)
	{
		icharacter->m_piCharacter->SetPosition(&pos);
	}

	return 0;  // number of return(s)
}

int lua_GetCharacterInstancePosition(lua_State* L)
{
	CLifeInstance_Character* icharacter = *(CLifeInstance_Character**)luaL_checkudata(L, 1, g_CharacterInstanceMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = icharacter->GetPosition();

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetCharacterInstance(lua_State* L)
{
	CLifeInstance_Character* icharacter = *(CLifeInstance_Character**)luaL_checkudata(L, 1, g_CharacterInstanceMetaName);

	CCharacter* retChar = icharacter->m_piCharacter;

	if (retChar == NULL)
	{
		lua_pushnil(L);
		return 1;
	}

	// allocate userdata to hold the pointer
	CCharacter** udata = (CCharacter**)lua_newuserdata(L, sizeof(CCharacter*));
	*udata = retChar;

	// attach the vehicle metatable
	luaL_getmetatable(L, g_CharacterMetaName);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_GetCharacterInstancePointer(lua_State* L)
{
	CLifeInstance_Character* icharacter = *(CLifeInstance_Character**)luaL_checkudata(L, 1, g_CharacterInstanceMetaName);

	lua_pushinteger(L, (int)icharacter);

	return 1;
}