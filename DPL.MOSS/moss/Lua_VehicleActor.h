#pragma once
#include "Lua_Main.h"
#include "Lua_Vehicle.h"
#include "Lua_VehicleInstance.h"
#include "..\dpl\Vehicle.h"
#include "..\dpl\CLifeInstance_Vehicle.h"
#include "..\dpl\CLifeActor_Vehicle.h"

extern const char* g_VehicleActorMetaName;

void Init_Lua_MetaTable_VehicleActor();

int lua_VehicleActorIndex(lua_State* L);

//int lua_SetVehicleInstancePosition(lua_State* L);
//int lua_GetVehicleInstancePosition(lua_State* L);
int lua_GetVehicleActorInstance(lua_State* L);
int lua_GetVehicleActorPointer(lua_State* L);

int lua_CreateVehicleActor(lua_State* L);
int lua_DestroyVehicleActor(lua_State* L);
int lua_InstantiateVehicleActor(lua_State* L);