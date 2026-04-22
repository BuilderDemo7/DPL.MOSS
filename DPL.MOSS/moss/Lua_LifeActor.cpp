#include "Lua_LifeActor.h"

// all life actors (in Lua)
#include "Lua_CharacterActor.h"
#include "Lua_VehicleActor.h"
#include "Lua_Camera.h"
#include "Lua_TestVolume.h"
#include "Lua_PointActor.h"
#include "Lua_Prop.h" // also an LifeActor

const char* g_LifeActorMetaName = "LifeActor";

void Init_Lua_MetaTable_LifeActor()
{
	luaL_newmetatable(L, g_LifeActorMetaName);

	// set __index
	lua_pushcfunction(L, lua_LifeActorIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_LifeActorIndex(lua_State* L)
{
	CLifeActor* actor = *(CLifeActor**)lua_touserdata(L, 1);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetLifeActorPointer);
		return 1;
	}
	// LifeActor generic methods
	else if (strcmp(key, "AddObjectiveIcon") == 0) {
		lua_pushcfunction(L, lua_AddObjectiveIconToLifeActor);
		return 1;
	}
	else if (strcmp(key, "RemoveObjectiveIcon") == 0) {
		lua_pushcfunction(L, lua_RemoveObjectiveIconFromLifeActor);
		return 1;
	}
	else if (strcmp(key, "Create") == 0 || strcmp(key, "Instantiate") == 0) {
		lua_pushcfunction(L, lua_InstantiateLifeActor);
		return 1;
	}
	else if (strcmp(key, "Destroy") == 0 || strcmp(key, "Delete") == 0) {
		lua_pushcfunction(L, lua_DestroyLifeActor);
		return 1;
	}
	else if (strcmp(key, "hamsterFactoryType") == 0 || strcmp(key, "FactoryType") == 0) {
		int facType = -1;

		if (actor != NULL)
			facType = actor->hamsterFactoryType();
		
		lua_pushinteger(L, facType);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_GetLifeActorPointer(lua_State* L)
{
	CLifeActor* actor = *(CLifeActor**)lua_touserdata(L, 1);

	lua_pushinteger(L, (int)actor);

	return 1;
}

int lua_AddObjectiveIconToLifeActor(lua_State* L)
{
	CLifeActor* actor = *(CLifeActor**)lua_touserdata(L, 1);

	int nargs = lua_gettop(L);

	int displayType = luaL_checkinteger(L, 2);
	int visibility = luaL_optinteger(L, 3, 1); // ObjVisibility_MinimapAndModel
	bool displayMinimapArrow = false;
	if (nargs > 3)
		displayMinimapArrow = lua_toboolean(L, 4);
	bool displayAsCop = false;
	if (nargs > 4)
		displayAsCop = lua_toboolean(L, 5);

	float heightOffset = luaL_optnumber(L, 6, 0.0f);
	int eventType = luaL_optinteger(L, 7, 0);

	SObjectiveIcon objective = SObjectiveIcon();
	objective.m_bParticleEffect = false;
	objective.m_pTarget = actor;

	objective.m_activity = 1; // 1 = add, 2 = remove

	SetupObjectiveIcon(&objective, displayType, eventType, eventType == 4);

	objective.m_minimapDisplayArrow = displayMinimapArrow;
	objective.m_displayAsCop = displayAsCop;
	objective.m_heightOffset = objective.m_heightOffset + heightOffset;
	objective.m_visibility = visibility;

	auto tm = CTargetManager::GetInstance();
	if (tm)
	{
		tm->AddObjectiveIcon(&objective, objective.m_bParticleEffect);
	}

	return 0;
}

int lua_RemoveObjectiveIconFromLifeActor(lua_State* L)
{
	// NOTE: pretty much similar to lua_AddObjectiveIconToLifeActor, except that objective.m_activity = 2
	CLifeActor* actor = *(CLifeActor**)lua_touserdata(L, 1);

	int nargs = lua_gettop(L);

	int displayType = luaL_checkinteger(L, 2);
	bool displayMinimapArrow = false;
	if (nargs > 2)
		displayMinimapArrow = lua_toboolean(L, 3);
	bool displayAsCop = false;
	if (nargs > 3)
		displayAsCop = lua_toboolean(L, 4);

	float heightOffset = luaL_optnumber(L, 5, 0.0f);
	int eventType = luaL_optinteger(L, 6, 0);

	SObjectiveIcon objective = SObjectiveIcon();
	objective.m_bParticleEffect = false;
	objective.m_pTarget = actor;

	objective.m_activity = 2; // 1 = add, 2 = remove

	SetupObjectiveIcon(&objective, displayType, eventType, eventType == 4);

	objective.m_minimapDisplayArrow = displayMinimapArrow;
	objective.m_displayAsCop = displayAsCop;
	objective.m_heightOffset = objective.m_heightOffset + heightOffset;

	auto tm = CTargetManager::GetInstance();
	if (tm)
	{
		tm->AddObjectiveIcon(&objective, objective.m_bParticleEffect);
	}

	return 0;
}

void* lua_checklifeactor(lua_State* L, int ud, bool shouldError)
{
	CLifeActor** targetActor = (CLifeActor**)luaL_testudata(L, ud, g_VehicleActorMetaName);
	if (!targetActor)
		targetActor = (CLifeActor**)luaL_testudata(L, ud, g_CharacterActorMetaName);
	if (!targetActor)
		targetActor = (CLifeActor**)luaL_testudata(L, ud, g_PropMetaName);
	if (!targetActor)
		targetActor = (CLifeActor**)luaL_testudata(L, ud, g_TestVolumeMetaName);
	if (!targetActor)
		targetActor = (CLifeActor**)luaL_testudata(L, ud, g_CameraMetaName);
	if (!targetActor)
		targetActor = (CLifeActor**)luaL_testudata(L, ud, g_PointActorMetaName);

	if (!targetActor && shouldError)
	{
		luaL_error(L, "invalid userdata, expected a LifeActor, do not use instances types");
		return NULL;
	}

	return (void*)targetActor;
}

const char* GetLifeActorMetaTableName(CLifeActor* actor)
{
	const char* name = NULL;

	if (actor != NULL)
	{
		EFactoryType fct = actor->hamsterFactoryType();

		switch (fct)
		{
		case EFactoryType_LifeActor_Vehicle:
		{
			name = g_VehicleActorMetaName;
			break;
		}
		case EFactoryType_LifeActor_Character:
		{
			name = g_CharacterActorMetaName;
			break;
		}
		case EFactoryType_LifeActor_Prop:
		{
			name = g_PropMetaName;
			break;
		}
		case EFactoryType_LifeActor_TestVolume:
		{
			name = g_TestVolumeMetaName;
			break;
		}
		case EFactoryType_LifeActor_Marker:
		{
			name = g_PointActorMetaName;
			break;
		}
		case EFactoryType_LifeActor_Camera:
		{
			name = g_CameraMetaName;
			break;
		}
		}
	}

	return name;
}

Lua_LifeActorInfo GetLuaLifeActor(CLifeActor* actor)
{
	Lua_LifeActorInfo info = Lua_LifeActorInfo();

	if (actor != NULL)
	{
		CLifeActor** udata = (CLifeActor**)lua_newuserdata(L, sizeof(void*));
		*udata = actor;

		info.m_pszMetaTableName = GetLifeActorMetaTableName(actor);

		info.m_pUserData = (void*)udata;
	}
	
	return info;
}

// generic funcs
int lua_DestroyLifeActor(lua_State* L)
{
	CLifeActor* actor = *(CLifeActor**)lua_touserdata(L, 1);
	actor->Delete();
	return 0;
}

int lua_InstantiateLifeActor(lua_State* L)
{
	CLifeActor* actor = *(CLifeActor**)lua_touserdata(L, 1);
	actor->Create();
	return 0;
}