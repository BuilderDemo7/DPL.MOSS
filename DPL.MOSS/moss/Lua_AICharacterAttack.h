#pragma once
#include "Lua_Main.h"
#include "..\dpl\LifeNode_AI_CharacterAttack.h"

extern const char* g_AICharacterAttackMetaName;

extern Life::Node::Character::Attack::Class* g_aCustomAICharacterAttacks[102];

void Init_Lua_MetaTable_AICharacterAttack();

int lua_AICharacterAttackIndex(lua_State* L);

int lua_GetAICharacterAttackPointer(lua_State* L);

int lua_EnableAICharacterAttack(lua_State* L);
int lua_DisableAICharacterAttack(lua_State* L);

int lua_CreateCharacterAttackAI(lua_State* L);

int lua_GetAICharacterAttackAttackee(lua_State* L);
int lua_GetAICharacterAttackAttackeePointer(lua_State* L);

int lua_GetAICharacterAttackAttacker(lua_State* L);
int lua_GetAICharacterAttackAttackerPointer(lua_State* L);

int lua_SetAICharacterAttackAttackee(lua_State* L);
int lua_SetAICharacterAttackAttacker(lua_State* L);