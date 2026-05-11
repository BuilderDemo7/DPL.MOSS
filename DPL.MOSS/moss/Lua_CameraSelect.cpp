#include "Lua_CameraSelect.h"
#include "..\dpl\Factory.h"
#include "Lua_LifeActor.h"

const char* g_CameraSelectMetaName = "CameraSelect";

void Init_Lua_MetaTable_CameraSelect()
{
	luaL_newmetatable(L, g_CameraSelectMetaName);

	// set __index
	lua_pushcfunction(L, lua_CameraSelectIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_CameraSelectIndex(lua_State* L)
{
	CLifeNode_CameraSelect* camSel = *(CLifeNode_CameraSelect**)luaL_checkudata(L, 1, g_CameraSelectMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetCameraSelectPointer);
		return 1;
	}
	else if (strcmp(key, "Activate") == 0 || strcmp(key, "Enable") == 0) {
		lua_pushcfunction(L, lua_EnableCameraSelect);
		return 1;
	}
	else if (strcmp(key, "Deactivate") == 0 || strcmp(key, "Disable") == 0) {
		lua_pushcfunction(L, lua_DisableCameraSelect);
		return 1;
	}
	else if (strcmp(key, "GetTarget") == 0) {
		lua_pushcfunction(L, lua_GetCameraSelectTarget);
		return 1;
	}
	else if (strcmp(key, "GetTargetPointer") == 0) {
		lua_pushcfunction(L, lua_GetCameraSelectTargetPointer);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_GetCameraSelectTarget(lua_State* L)
{
	CLifeNode_CameraSelect* camSel = *(CLifeNode_CameraSelect**)luaL_checkudata(L, 1, g_CameraSelectMetaName);
	CLifeActor* actor = camSel->m_targetActor;
	if (actor != NULL)
	{
		Lua_LifeActorInfo info = GetLuaLifeActor(actor);

		luaL_getmetatable(L, info.m_pszMetaTableName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_GetCameraSelectTargetPointer(lua_State* L)
{
	CLifeNode_CameraSelect* camSel = *(CLifeNode_CameraSelect**)luaL_checkudata(L, 1, g_CameraSelectMetaName);
	CLifeActor* actor = camSel->m_targetActor;

	lua_pushinteger(L, (int)actor);

	return 1;
}

int lua_GetCameraSelectPointer(lua_State* L)
{
	CLifeNode_CameraSelect* camSel = *(CLifeNode_CameraSelect**)luaL_checkudata(L, 1, g_CameraSelectMetaName);

	lua_pushinteger(L, (int)camSel);

	return 1;
}

int lua_EnableCameraSelect(lua_State* L)
{
	CLifeNode_CameraSelect* camSel = *(CLifeNode_CameraSelect**)luaL_checkudata(L, 1, g_CameraSelectMetaName);
	
	bool enabled;
	eNodeFireWire fw;

	((CLifeNode*)camSel)->OnEnable(&enabled, &fw);
	
	return 0;
}

int lua_DisableCameraSelect(lua_State* L)
{
	CLifeNode_CameraSelect* camSel = *(CLifeNode_CameraSelect**)luaL_checkudata(L, 1, g_CameraSelectMetaName);
	
	((CLifeNode*)camSel)->OnDisable();

	return 0;
}

int lua_CreateCameraSelect(lua_State* L)
{
	ECameraSelectType cameraType = (ECameraSelectType)luaL_checkinteger(L, 1);
	CLifeActor** actor = (CLifeActor**)lua_checklifeactor(L, 2);
	
	ECameraSelect_VehicleCamType vehiclePosition = (ECameraSelect_VehicleCamType)luaL_optinteger(L, 3, ECameraSelect_VehicleCamType_Bonnet);

	float duration = luaL_optnumber(L, 4, 60.0f);
	float zoom = luaL_optnumber(L, 5, 1.0f);
	float motionBlur = luaL_optnumber(L, 6, 0.0f);
	float speed = luaL_optnumber(L, 7, 1.0f);
	float blendTime = luaL_optnumber(L, 8, 0.0f);

	// TODO: in future life actor additions, add it in here:
	//if (!actor)
	//	actor = (CLifeActor*)luaL_testudata(L, 2, g_VehicleActorMetaName);

	CLifeNode_CameraSelect* camSel = (CLifeNode_CameraSelect*)hamster::CreateObject(EFactoryType::EFactoryType_LifeNode_CameraSelect);

	if (camSel != NULL)
	{
		camSel->CustomInitalise(cameraType, *actor, vehiclePosition, speed, zoom, motionBlur, duration, blendTime);

		CLifeNode_CameraSelect** udata = (CLifeNode_CameraSelect**)lua_newuserdata(L, sizeof(void*));
		*udata = camSel;

		luaL_getmetatable(L, g_CameraSelectMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return

		return 1;
	}

	lua_pushnil(L);
	return 1;
}