#pragma once
#include "Lua_Main.h"

extern bool g_bFreeCamOn;
extern void* g_pFreeCamPtr;

int lua_GetPlayerCharacter(lua_State* L);
int lua_GetPlayerActor(lua_State* L);
int lua_ShowMissionComment(lua_State* L);
int lua_EndAllLifeEvents(lua_State* L);

// TODO: do the set life event status function
//int lua_SetLifeEventStatus(lua_State* L);

int lua_GetEra(lua_State* L);

int lua_ToggleFreeCam(lua_State* L);
int lua_ToggleIGCS(lua_State* L);

int lua_SetGameDifficulty(lua_State* L);
int lua_GetGameDifficulty(lua_State* L);

int lua_EnableCops(lua_State* L);
int lua_DeleteAllChaseEntities(lua_State* L);
int lua_AddChaseCarWeaponType(lua_State* L);
int lua_AddChaseCarVehicleType(lua_State* L);
int lua_RemoveChaseCarVehicleType(lua_State* L);
int lua_AddChaseCarCharacterType(lua_State* L);
int lua_RemoveChaseCarCharacterType(lua_State* L);
int lua_SetChaseCarPatrolDensity(lua_State* L);

int lua_ActivatePager(lua_State* L);
int lua_SetVehicleFelonyLevel(lua_State* L);
int lua_SetFelonyLevel(lua_State* L);
int lua_GetFelonyLevel(lua_State* L);
int lua_SetChaseCarMaxChasers(lua_State* L);
int lua_IsPlayerFreeAiming(lua_State* L);
int lua_HasPlayerShotRecently(lua_State* L);
int lua_AddAllWeaponsForPlayer(lua_State* L);

int lua_CreatePatrolHelicopterUnit(lua_State* L);
int lua_CreatePatrolCharacterOnFoot(lua_State* L);
int lua_CreatePatrolVehicleUnit(lua_State* L);

int lua_SetMusicTrack(lua_State* L);
int lua_GetMileometer(lua_State* L);

int lua_GetMoney(lua_State* L);
int lua_SetMoney(lua_State* L);

int lua_GetDistanceBetweenPoints2D(lua_State* L);
int lua_GetDistanceBetweenPoints3D(lua_State* L);

int lua_SetMasterSpeedMultiplier(lua_State* L);
int lua_GetInputInfo(lua_State* L);

int lua_LaunchVEdit(lua_State* L);

int lua_SetCameraPosition(lua_State* L);

int lua_DrawText(lua_State* L);

int lua_GetVehicleInstances(lua_State* L);

int lua_GetPlaylistFileNames(lua_State* L);
int lua_GetPlaylistOrder(lua_State* L);

int lua_FindClosestVehicleForEntry(lua_State* L);

int lua_GetCameraPosition(lua_State* L);
int lua_GetCameraForwardVector(lua_State* L);
int lua_GetCameraRightVector(lua_State* L);