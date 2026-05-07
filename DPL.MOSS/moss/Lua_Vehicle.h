#pragma once
#include "Lua_Main.h"
#include "..\dpl\Vehicle.h"

extern const char* g_VehicleMetaName;

void Init_Lua_MetaTable_Vehicle();

int lua_VehicleIndex(lua_State* L);

int lua_GetVehicleDamage(lua_State* L);
int lua_SetVehicleDamage(lua_State* L);

int lua_GetVehiclePointer(lua_State* L);

int lua_ExplodeVehicle(lua_State* L);
int lua_FixVehicle(lua_State* L);

int lua_SetVehicleNitro(lua_State* L);
int lua_GetVehicleNitro(lua_State* L);

int lua_GetVehicleType(lua_State* L);

int lua_ActivateVehicleLamp(lua_State* L);
int lua_ActivateVehicleSiren(lua_State* L);

int lua_SetVehiclePhysicsPriority(lua_State* L);
int lua_GetVehiclePhysicsPriority(lua_State* L);
int lua_SetVehicleRenderingPriority(lua_State* L);
int lua_GetVehicleRenderingPriority(lua_State* L);

int lua_SetVehicleColor(lua_State* L);
int lua_GetVehicleColor(lua_State* L);

int lua_SetVehiclePosition(lua_State* L);
int lua_GetVehiclePosition(lua_State* L);
int lua_SetVehicleRotation(lua_State* L);
int lua_GetVehicleRotation(lua_State* L);

int lua_SetVehicleVelocity(lua_State* L);
int lua_GetVehicleVelocity(lua_State* L);

int lua_SetVehicleAngle(lua_State* L);
int lua_GetVehicleAngle(lua_State* L);

int lua_GetVehicleDriver(lua_State* L);

int lua_CreateVehicle(lua_State* L);
int lua_DestroyVehicle(lua_State* L);

int lua_MakeInfiniteMass(lua_State* L);
int lua_MakeVehicleStatic(lua_State* L);
int lua_MakeVehicleDynamic(lua_State* L);

int lua_SendVehicleManipulationPacket(lua_State* L);

int lua_GetVehicleForwardVector(lua_State* L);
int lua_GetVehicleRightVector(lua_State* L);

int lua_ResetVehicleCustomData(lua_State* L);
int lua_VehicleAddCustomDataPart(lua_State* L);
int lua_DamageVehicle(lua_State* L);

int lua_GetVehicleRPM(lua_State* L);
int lua_GetVehicleGear(lua_State* L);