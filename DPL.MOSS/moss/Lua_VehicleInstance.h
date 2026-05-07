#pragma once
#include "Lua_Main.h"
#include "Lua_Vehicle.h"
#include "..\dpl\Vehicle.h"
#include "..\dpl\CLifeInstance_Vehicle.h"

extern const char* g_VehicleInstanceMetaName;

void Init_Lua_MetaTable_VehicleInstance();

int lua_VehicleInstanceIndex(lua_State* L);

int lua_SetVehicleInstancePosition(lua_State* L);
int lua_GetVehicleInstancePosition(lua_State* L);
int lua_GetVehicleInstance(lua_State* L);
int lua_GetVehicleInstancePointer(lua_State* L);

int lua_SetVehicleMustangHandling(lua_State* L);

int lua_UnregisterVehicleInstanceSpoolHandler(lua_State* L);

int lua_SetVehicleInstanceFelony(lua_State* L);
int lua_GetVehicleInstanceFelony(lua_State* L);
int lua_SetVehicleInstanceCreatedDamaged(lua_State* L);
int lua_GetVehicleInstanceCreatedDamaged(lua_State* L);