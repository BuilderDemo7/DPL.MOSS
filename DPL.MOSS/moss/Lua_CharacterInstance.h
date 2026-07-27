#pragma once
#include "Lua_Main.h"
#include "Lua_Character.h"
#include "..\dpl\CCharacter.h"
#include "..\dpl\CLifeInstance_Character.h"

extern const char* g_CharacterInstanceMetaName;

void Init_Lua_MetaTable_CharacterInstance();

int lua_CharacterInstanceIndex(lua_State* L);

int lua_GetCharacterInstance(lua_State* L);
int lua_GetCharacterInstancePointer(lua_State* L);

int lua_SetCharacterInstancePosition(lua_State* L);
int lua_GetCharacterInstancePosition(lua_State* L);

int lua_SetCharacterInstancePositionChangePerGameStep(lua_State* L);
int lua_GetCharacterInstancePositionChangePerGameStep(lua_State* L);

int lua_SetCharacterInstanceConstrainPositionChange(lua_State* L);
int lua_GetCharacterInstanceConstrainPositionChange(lua_State* L);

int lua_UnregisterCharacterInstanceSpoolHandler(lua_State* L);

int lua_PromoteCharacterInstanceToLifeActor(lua_State* L);