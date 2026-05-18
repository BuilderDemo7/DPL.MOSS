#pragma once
#include "Lua_Main.h"

extern const char* g_CharacterMetaName;

void Init_Lua_MetaTable_Character();
void Setup_Lua_MetaTable_Character(bool popStack = true);

// methods

int lua_CharacterIndex(lua_State* L);

int lua_SetCharacterPosition(lua_State* L);
int lua_GetCharacterPosition(lua_State* L);
int lua_GetCharacterAngle(lua_State* L);
int lua_SetCharacterAngle(lua_State* L);

int lua_GetCharacterVehicle(lua_State* L);
int lua_GetCharacterEnteringVehicle(lua_State* L);
int lua_TeleportCharacterIntoVehicle(lua_State* L);

int lua_GetCharacterPointer(lua_State* L); // get-only

int lua_GetCharacterCanExitVehicle(lua_State* L);
int lua_SetCharacterCanExitVehicle(lua_State* L);

int lua_CharacterForceIdleMode(lua_State* L);
int lua_CharacterPlayMissionAnimation(lua_State* L);
int lua_CharacterPlayMissionAnimationByID(lua_State* L);
int lua_CharacterPlayMissionAnimationByHash(lua_State* L);

int lua_CharacterKillMissionAnimations(lua_State* L);

int lua_CharacterEnterVehicle(lua_State* L);
int lua_CharacterExitVehicle(lua_State* L);

int lua_CharacterEjectFromVehicle(lua_State* L);
int lua_CharacterSetArrested(lua_State* L);

int lua_GetCharacterForwardVector(lua_State* L);
int lua_GetCharacterRightVector(lua_State* L);

int lua_CharacterSetHealth(lua_State* L);
int lua_CharacterGetHealth(lua_State* L);

int lua_CharacterSwapSkin(lua_State* L);
int lua_CharacterWalk(lua_State* L);

int lua_SetCharacterVelocity(lua_State* L);
int lua_GetCharacterVelocity(lua_State* L);

int lua_PromoteCharacterToLifeInstance(lua_State* L);

int lua_DestroyCharacter(lua_State* L);

int lua_CharacterSetAlpha(lua_State* L);
int lua_CharacterGetAlpha(lua_State* L);

int lua_CharacterSetModel(lua_State* L);
int lua_CharacterGetModel(lua_State* L);

int lua_CharacterSetAnimType(lua_State* L);
int lua_CharacterGetAnimType(lua_State* L);
