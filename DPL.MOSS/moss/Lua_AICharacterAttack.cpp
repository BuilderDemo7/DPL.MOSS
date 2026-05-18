#include "Lua_AICharacterAttack.h"
#include "..\dpl\Factory.h"
#include "Lua_LifeActor.h"

using namespace Life::Node;

const char* g_AICharacterAttackMetaName = "AICharacterAttack";

Life::Node::Character::Attack::Class* g_aCustomAICharacterAttacks[102] = {};

void Init_Lua_MetaTable_AICharacterAttack()
{
	luaL_newmetatable(L, g_AICharacterAttackMetaName);

	// set __index
	lua_pushcfunction(L, lua_AICharacterAttackIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_AICharacterAttackIndex(lua_State* L)
{
	Character::Attack::Class* aiCharaAttack = *(Character::Attack::Class**)luaL_checkudata(L, 1, g_AICharacterAttackMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetAICharacterAttackPointer);
		return 1;
	}
	else if (strcmp(key, "Activate") == 0 || strcmp(key, "Enable") == 0) {
		lua_pushcfunction(L, lua_EnableAICharacterAttack);
		return 1;
	}
	else if (strcmp(key, "Deactivate") == 0 || strcmp(key, "Disable") == 0) {
		lua_pushcfunction(L, lua_DisableAICharacterAttack);
		return 1;
	}
	else if (strcmp(key, "GetAttackee") == 0) {
		lua_pushcfunction(L, lua_GetAICharacterAttackAttackee);
		return 1;
	}
	else if (strcmp(key, "GetAttackeePointer") == 0) {
		lua_pushcfunction(L, lua_GetAICharacterAttackAttackeePointer);
		return 1;
	}
	else if (strcmp(key, "GetAttacker") == 0) {
		lua_pushcfunction(L, lua_GetAICharacterAttackAttacker);
		return 1;
	}
	else if (strcmp(key, "GetAttackerPointer") == 0) {
		lua_pushcfunction(L, lua_GetAICharacterAttackAttackerPointer);
		return 1;
	}
	else if (strcmp(key, "SetAttackee") == 0) {
		lua_pushcfunction(L, lua_SetAICharacterAttackAttackee);
		return 1;
	}
	else if (strcmp(key, "SetAttacker") == 0) {
		lua_pushcfunction(L, lua_SetAICharacterAttackAttacker);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

void Add_AICharacterAttack(Character::Attack::Class* item)
{
	for (int i = 0; i < 102; i++)
	{
		if (g_aCustomAICharacterAttacks[i] == NULL)
		{
			g_aCustomAICharacterAttacks[i] = item;
			break;
		}
	}
}

void Remove_AICharacterAttack(Character::Attack::Class* item)
{
	for (int i = 0; i < 102; i++)
	{
		if (g_aCustomAICharacterAttacks[i] == item)
		{
			g_aCustomAICharacterAttacks[i] = NULL;
			break;
		}
	}
}

int lua_CreateCharacterAttackAI(lua_State* L)
{
	CLifeActor** attackee = (CLifeActor**)lua_checklifeactor(L, 1, true);
	CLifeActor** attacker = (CLifeActor**)lua_checklifeactor(L, 2, false);
	float accuracy = luaL_optnumber(L, 3, 1.0f);

	CLifeActor* m_pAttacker = NULL;
	if (attacker != NULL)
		m_pAttacker = *attacker;

	Character::Attack::Class* aiCharaAttack = (Character::Attack::Class*)hamster::CreateObject(EFactoryType::EFactoryType_CharacterAttackLifeNode);

	if (aiCharaAttack != NULL)
	{
		aiCharaAttack->CustomInitialise(*attackee, m_pAttacker, accuracy);

		Character::Attack::Class** udata = (Character::Attack::Class**)lua_newuserdata(L, sizeof(void*));
		*udata = aiCharaAttack;

		Add_AICharacterAttack(aiCharaAttack);

		luaL_getmetatable(L, g_AICharacterAttackMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_GetAICharacterAttackPointer(lua_State* L)
{
	Character::Attack::Class* aiCharaAttack = *(Character::Attack::Class**)luaL_checkudata(L, 1, g_AICharacterAttackMetaName);

	lua_pushinteger(L, (int)aiCharaAttack);

	return 1;
}

int lua_EnableAICharacterAttack(lua_State* L)
{
	Character::Attack::Class* aiCharaAttack = *(Character::Attack::Class**)luaL_checkudata(L, 1, g_AICharacterAttackMetaName);

	bool enabled;
	eNodeFireWire fw;

	((CLifeNode*)aiCharaAttack)->OnEnable(&enabled, &fw);

	return 0;
}

int lua_DisableAICharacterAttack(lua_State* L)
{
	Character::Attack::Class* aiCharaAttack = *(Character::Attack::Class**)luaL_checkudata(L, 1, g_AICharacterAttackMetaName);

	((CLifeNode*)aiCharaAttack)->OnDisable();

	return 0;
}

int lua_GetAICharacterAttackAttackee(lua_State* L)
{
	Character::Attack::Class* aiCharaAttack = *(Character::Attack::Class**)luaL_checkudata(L, 1, g_AICharacterAttackMetaName);
	CLifeActor* actor = aiCharaAttack->m_attackeeCharacterActorPtr;
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

int lua_GetAICharacterAttackAttackeePointer(lua_State* L)
{
	Character::Attack::Class* aiCharaAttack = *(Character::Attack::Class**)luaL_checkudata(L, 1, g_AICharacterAttackMetaName);
	CLifeActor* actor = aiCharaAttack->m_attackeeCharacterActorPtr;

	lua_pushinteger(L, (int)actor);

	return 1;
}

int lua_GetAICharacterAttackAttacker(lua_State* L)
{
	Character::Attack::Class* aiCharaAttack = *(Character::Attack::Class**)luaL_checkudata(L, 1, g_AICharacterAttackMetaName);
	CLifeActor* actor = aiCharaAttack->m_attackerActorCharacterPtr;
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

int lua_GetAICharacterAttackAttackerPointer(lua_State* L)
{
	Character::Attack::Class* aiCharaAttack = *(Character::Attack::Class**)luaL_checkudata(L, 1, g_AICharacterAttackMetaName);
	CLifeActor* actor = aiCharaAttack->m_attackerActorCharacterPtr;

	lua_pushinteger(L, (int)actor);

	return 1;
}

int lua_SetAICharacterAttackAttackee(lua_State* L)
{
	Character::Attack::Class* aiCharaAttack = *(Character::Attack::Class**)luaL_checkudata(L, 1, g_AICharacterAttackMetaName);
	CLifeActor** actor = (CLifeActor**)lua_checklifeactor(L, 2, true);

	CLifeActor* m_pActor = NULL;
	if (actor != NULL)
		m_pActor = *actor;

	aiCharaAttack->m_attackeeCharacterActorPtr = m_pActor;

	return 0;
}

int lua_SetAICharacterAttackAttacker(lua_State* L)
{
	Character::Attack::Class* aiCharaAttack = *(Character::Attack::Class**)luaL_checkudata(L, 1, g_AICharacterAttackMetaName);
	CLifeActor** actor = (CLifeActor**)lua_checklifeactor(L, 2, false);

	CLifeActor* m_pActor = NULL;
	if (actor != NULL)
		m_pActor = *actor;

	aiCharaAttack->m_attackerActorCharacterPtr = m_pActor;

	return 0;
}