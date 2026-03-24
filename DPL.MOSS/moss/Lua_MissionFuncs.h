#pragma once
#include "Lua_Main.h"

int lua_GetPlayerCharacter(lua_State* L);
int lua_ShowMissionComment(lua_State* L);
int lua_EndAllLifeEvents(lua_State* L);

// TODO: do the set life event status function
//int lua_SetLifeEventStatus(lua_State* L);

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

int lua_SetCameraPosition(lua_State* L);