#pragma once
#include "Lua_Main.h"
#include "Lua_Character.h"
#include "Lua_CharacterInstance.h"
#include "..\dpl\CCharacter.h"
#include "..\dpl\CLifeInstance_Character.h"
#include "..\dpl\CLifeActor_Character.h"

extern const char* g_CharacterActorMetaName;

void Init_Lua_MetaTable_CharacterActor();

int lua_CharacterActorIndex(lua_State* L);

//int lua_SetVehicleInstancePosition(lua_State* L);
//int lua_GetVehicleInstancePosition(lua_State* L);
int lua_GetCharacterActorInstance(lua_State* L);
int lua_GetCharacterActorPointer(lua_State* L);

int lua_CreateCharacterActor(lua_State* L);
int lua_DestroyCharacterActor(lua_State* L);
int lua_InstantiateCharacterActor(lua_State* L);

int lua_SetCharacterActorPosition(lua_State* L);
int lua_GetCharacterActorPosition(lua_State* L);

int lua_SetCharacterActorRotation(lua_State* L);
int lua_GetCharacterActorRotation(lua_State* L);

int lua_GetCharacterActorForwardVector(lua_State* L);
int lua_GetCharacterActorRightVector(lua_State* L);

int lua_CharacterActorGoWander(lua_State* L);
int lua_CharacterActorStopWander(lua_State* L);