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
	else {
		lua_pushnil(L);
	}

	return 1;
}

// disabled
/*
int lua_SetVehicleInstancePosition(lua_State* L)
{
	// TODO
	return 0;
}

int lua_GetVehicleInstancePosition(lua_State* L)
{
	// TODO
	return 0;
}
*/

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