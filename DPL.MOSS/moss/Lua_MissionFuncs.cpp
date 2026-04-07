#include "Lua_MissionFuncs.h"
#include "Lua_Character.h"
#include "Lua_Vehicle.h"

#include "..\dpl\AIFelonySystemFelonyManager.h"
#include "..\dpl\CLifeSystemCommentLog.h"
#include "..\dpl\CLifeSystem.h"
#include "..\dpl\CCharacterCategoryManager.h"
#include "..\dpl\CLifeEventDataManager.h"
#include "..\dpl\GameOverlayManager.h"
#include "..\dpl\AmbientSoundManager.h"
#include "..\dpl\ProfileSettings.h"
#include "..\dpl\GameCamera.h"
#include "..\dpl\Speed.h"
#include "..\dpl\InputManager.h"

int lua_EndAllLifeEvents(lua_State* L)
{
	CLifeEventDataManager* evman = CLifeEventDataManager::GetInstance();
	
	if (evman != NULL)
		evman->EndAllLifeEvents();

	return 0;
}

int lua_GetEra(lua_State* L)
{
	CCharacterCategoryManager* ccm = CCharacterCategoryManager::GetInstance();

	int era = 0;
	if (ccm != NULL)
	{
		era = ccm->GetEra();
	}

	lua_pushinteger(L, era);

	return 1;
}

int lua_EnableCops(lua_State* L)
{
	bool cops = lua_toboolean(L, 1);

	auto fman = GetFelonyManager();
	if (fman != NULL)
	{
		fman->EnableCops(cops);
	}

	return 0;
}

int lua_DeleteAllChaseEntities(lua_State* L)
{
	AIFelonySystemPatrolCarTypeEnum patrol = (AIFelonySystemPatrolCarTypeEnum)luaL_optinteger(L, 1, E_PATROLCARTYPE_COP);

	auto fman = GetFelonyManager();
	if (fman != NULL)
	{
		fman->DeleteAllChaseEntities(patrol);
	}

	return 0;
}

int lua_AddChaseCarWeaponType(lua_State* L)
{
	EWeapons wep = (EWeapons)luaL_checkinteger(L, 1);
	AIFelonySystemPatrolCarTypeEnum patrol = (AIFelonySystemPatrolCarTypeEnum)luaL_optinteger(L, 2, E_PATROLCARTYPE_COP);

	auto fman = GetFelonyManager();
	if (fman != NULL)
	{
		fman->AddChaseCarWeaponType(wep, patrol);
	}

	return 0;
}

int lua_AddChaseCarVehicleType(lua_State* L)
{
	int nargs = lua_gettop(L); // number of arguments

	int veh = luaL_checkinteger(L, 1);
	bool secondaryVehicle = false;

	if (nargs > 1)
		secondaryVehicle = lua_toboolean(L, 2);

	AIFelonySystemPatrolCarTypeEnum patrol = (AIFelonySystemPatrolCarTypeEnum)luaL_optinteger(L, 3, E_PATROLCARTYPE_COP);

	auto fman = GetFelonyManager();
	if (fman != NULL)
	{
		fman->AddChaseCarVehicleType(veh, secondaryVehicle, patrol);
	}

	return 0;
}

int lua_RemoveChaseCarVehicleType(lua_State* L)
{
	int nargs = lua_gettop(L); // number of arguments

	int veh = luaL_checkinteger(L, 1);
	bool secondaryVehicle = false;

	if (nargs > 1)
		secondaryVehicle = lua_toboolean(L, 2);

	AIFelonySystemPatrolCarTypeEnum patrol = (AIFelonySystemPatrolCarTypeEnum)luaL_optinteger(L, 3, E_PATROLCARTYPE_COP);

	auto fman = GetFelonyManager();
	if (fman != NULL)
	{
		fman->RemoveChaseCarVehicleType(veh, secondaryVehicle, patrol);
	}

	return 0;
}

int lua_AddChaseCarCharacterType(lua_State* L)
{
	int nargs = lua_gettop(L); // number of arguments

	int chara = luaL_checkinteger(L, 1);

	AIFelonySystemPatrolCarTypeEnum patrol = (AIFelonySystemPatrolCarTypeEnum)luaL_optinteger(L, 2, E_PATROLCARTYPE_COP);

	auto fman = GetFelonyManager();
	if (fman != NULL)
	{
		fman->AddChaseCarCharacterType(chara, patrol);
	}

	return 0;
}

int lua_RemoveChaseCarCharacterType(lua_State* L)
{
	int nargs = lua_gettop(L); // number of arguments

	int chara = luaL_checkinteger(L, 1);

	AIFelonySystemPatrolCarTypeEnum patrol = (AIFelonySystemPatrolCarTypeEnum)luaL_optinteger(L, 2, E_PATROLCARTYPE_COP);

	auto fman = GetFelonyManager();
	if (fman != NULL)
	{
		fman->RemoveChaseCarCharacterType(chara, patrol);
	}

	return 0;
}

int lua_SetChaseCarPatrolDensity(lua_State* L)
{
	int nargs = lua_gettop(L); // number of arguments

	float density = luaL_checknumber(L, 1);

	AIFelonySystemPatrolCarTypeEnum patrol = (AIFelonySystemPatrolCarTypeEnum)luaL_optinteger(L, 2, E_PATROLCARTYPE_COP);

	auto fman = GetFelonyManager();
	if (fman != NULL)
	{
		fman->SetChaseCarPatrolDensity(density, patrol);
	}

	return 0;
}

int lua_GetPlayerCharacter(lua_State* L)
{
	CCharacter* character = NULL;

	CLifeSystem* lsys = CLifeSystem::GetInstance();

	if (lsys != NULL)
	{
		CLifePlayer* plr = lsys->GetPlayer();
		if (plr != NULL)
		{
			CPlayerDriverBehaviour* db = plr->GetDriverBehaviour();
			if (db != NULL)
				character = db->GetCharacter();
		}
	}

	if ((int)character == 0xfdfdfdcd)
	{
		lua_pushnil(L);
		return 1;
	}

	if (character == NULL)
	{
		lua_pushnil(L);
		return 1;
	}

	// Allocate Lua-managed memory for the struct directly
	CCharacter** udata =
		(CCharacter**)lua_newuserdata(L, sizeof(CCharacter*));

	*udata = character;

	luaL_getmetatable(L, g_CharacterMetaName);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_ShowMissionComment(lua_State* L)
{
	int nargs = lua_gettop(L); // number of arguments

	float duration = (float)luaL_checknumber(L, 1);  // param 1
	const char* comment = luaL_checkstring(L, 2);    // param 2

	if (nargs < 2)
	{
		return luaL_error(L, "Expected 1 number (for duration) and a string (for commentary)");
	}

	auto clog = GetLifeSystemCommentLog();
	if (clog != NULL)
		clog->AddMissionComment((char*)comment, duration);

	return 0;  // number of return(s)
}

int lua_ActivatePager(lua_State* L)
{
	if ((*(int*)0x70C71C) != 0)
	{
		CGameOverlay* over = *(CGameOverlay**)((*(int*)0x70C71C) + 0x450);
		if (over)
			over->ActivatePager();
	}

	return 0;
}

int lua_SetVehicleFelonyLevel(lua_State* L)
{
	CVehicle* veh = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	float felony = luaL_checknumber(L, 2);
	int patrolSlot = luaL_optinteger(L, 3, 0); // 0 = cops, 1 = goons

	if (veh == NULL)
		return luaL_error(L, "Bad argument #1 - The target vehicle is nil");

	if (felony < 0.0f)
		felony = 0.0f;

	if (felony > 1.0f)
		felony = 1.0f;

	if (patrolSlot > 1 || patrolSlot < 0)
		return luaL_error(L, "Bad argument #3 - patrol slot is invalid, it must be between 0 (cops) and 1 (goons)");

	AIFelonySystemFelonyManagerClass* felonyMan = GetFelonyManager();
	if (felonyMan)
		felonyMan->SetVehicleFelonyLevel(veh, patrolSlot, felony);

	return 0;  // number of return(s)
}

int lua_SetFelonyLevel(lua_State* L)
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	float felony = luaL_checknumber(L, 2);
	int patrolSlot = luaL_optinteger(L, 3, 0); // 0 = cops, 1 = goons

	if (character == NULL)
		return luaL_error(L, "Bad argument #1 - The target character is nil");

	if (felony < 0.0f)
		felony = 0.0f;

	if (felony > 1.0f)
		felony = 1.0f;

	if (patrolSlot > 1 || patrolSlot < 0)
		return luaL_error(L, "Bad argument #3 - patrol slot is invalid, it must be between 0 (cops) and 1 (goons)");

	AIFelonySystemFelonyManagerClass* felonyMan = GetFelonyManager();
	if (felonyMan)
		felonyMan->SetFelonyLevel(character, patrolSlot, felony);

	return 0;  // number of return(s)
}

int lua_GetFelonyLevel(lua_State* L)
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	int patrolSlot = luaL_optinteger(L, 2, 0); // 0 = cops, 1 = goons

	if (character == NULL)
		return luaL_error(L, "Bad argument #1 - The target character is nil");

	if (patrolSlot > 1 || patrolSlot < 0)
		return luaL_error(L, "Bad argument #2 - patrol slot is invalid, it must be between 0 (cops) and 1 (goons)");
	
	float fel = 0;
	AIFelonySystemFelonyManagerClass* felonyMan = GetFelonyManager();
	if (felonyMan)
		fel = felonyMan->GetFelonyLevel(character, patrolSlot);

	lua_pushnumber(L, fel);

	return 1;  // number of return(s)
}

int lua_SetChaseCarMaxChasers(lua_State* L)
{
	int maxC = luaL_checkinteger(L, 1);
	int patrolSlot = luaL_optinteger(L, 2, 0); // 0 = cops, 1 = goons

	if (maxC < 0)
		return luaL_error(L, "Bad argument #1 - max number of chasers can't be negative");

	if (patrolSlot > 1 || patrolSlot < 0)
		return luaL_error(L, "Bad argument #2 - patrol slot is invalid, it must be between 0 (cops) and 1 (goons)");

	AIFelonySystemFelonyManagerClass* felonyMan = GetFelonyManager();
	if (felonyMan)
		felonyMan->SetChaseCarMaxChasers(maxC, patrolSlot);

	return 0;  // number of return(s)
}

int lua_IsPlayerFreeAiming(lua_State* L)
{
	CPlayerDriverBehaviour* db = NULL;

	CLifeSystem* lsys = CLifeSystem::GetInstance();

	if (lsys != NULL)
	{
		CLifePlayer* plr = lsys->GetPlayer();
		if (plr != NULL)
		{
			db = plr->GetDriverBehaviour();
		}
	}

	if (db == NULL)
	{
		lua_pushboolean(L, false);
		return 1;
	}

	lua_pushboolean(L, db->IsFreeAiming());

	return 1; // number of return(s)
}

int lua_HasPlayerShotRecently(lua_State* L)
{
	CPlayerDriverBehaviour* db = NULL;

	CLifeSystem* lsys = CLifeSystem::GetInstance();

	if (lsys != NULL)
	{
		CLifePlayer* plr = lsys->GetPlayer();
		if (plr != NULL)
		{
			db = plr->GetDriverBehaviour();
		}
	}

	if (db == NULL)
	{
		lua_pushboolean(L, false);
		return 1;
	}

	lua_pushboolean(L, db->HasShotRecently());

	return 1; // number of return(s)
}

int lua_AddAllWeaponsForPlayer(lua_State* L)
{
	CPlayerDriverBehaviour* db = NULL;

	CLifeSystem* lsys = CLifeSystem::GetInstance();

	if (lsys != NULL)
	{
		CLifePlayer* plr = lsys->GetPlayer();
		if (plr != NULL)
		{
			db = plr->GetDriverBehaviour();
		}
	}

	if (db)
	{
		db->AddAllWeapons();
	}

	return 0; // number of return(s)
}

int lua_CreatePatrolHelicopterUnit(lua_State* L)
{
	int nargs = lua_gettop(L);

	float x, y, z, angle;
	int patrolSlot;

	if (nargs > 3) {
		// Three numbers
		x = (float)luaL_checknumber(L, 1);
		y = (float)luaL_checknumber(L, 2);
		z = (float)luaL_checknumber(L, 3);
		angle = (float)luaL_optnumber(L, 4, 0);
		patrolSlot = (int)luaL_optinteger(L, 5, 0);

		if (patrolSlot > 1 || patrolSlot < 0)
			return luaL_error(L, "Bad argument #5 - patrol slot is invalid, it must be between 0 (cops) and 1 (goons)");
	}
	else if (nargs <= 3) {
		// Vector
		Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable);
		x = vec->X;
		y = vec->Y;
		z = vec->Z;
		angle = (float)luaL_optnumber(L, 2, 0);
		patrolSlot = (int)luaL_optinteger(L, 3, 0);

		if (patrolSlot > 1 || patrolSlot < 0)
			return luaL_error(L, "Bad argument #3 - patrol slot is invalid, it must be between 0 (cops) and 1 (goons)");
	}
	else {
		return luaL_error(L, "Bad argument #1 - expected 1 Vector or 3 numbers");
	}

	Vector4 pos = Vector4(x, y, z, 1);
	AIFelonySystemFelonyManagerClass* felonyMan = GetFelonyManager();
	if (felonyMan)
		felonyMan->CreatePatrolHelicopterUnit(&pos, (AIFelonySystemPatrolCarTypeEnum)patrolSlot, angle);

	return 0;  // number of return(s)
}

int lua_CreatePatrolCharacterOnFoot(lua_State* L)
{
	int nargs = lua_gettop(L);

	float x, y, z, angle;
	int patrolSlot;

	if (nargs > 3) {
		// Three numbers
		x = (float)luaL_checknumber(L, 1);
		y = (float)luaL_checknumber(L, 2);
		z = (float)luaL_checknumber(L, 3);
		angle = (float)luaL_optnumber(L, 4, 0);
		patrolSlot = (int)luaL_optinteger(L, 5, 0);

		if (patrolSlot > 1 || patrolSlot < 0)
			return luaL_error(L, "Bad argument #5 - patrol slot is invalid, it must be between 0 (cops) and 1 (goons)");
	}
	else if (nargs <= 3) {
		// Vector
		Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable);
		x = vec->X;
		y = vec->Y;
		z = vec->Z;
		angle = (float)luaL_optnumber(L, 2, 0);
		patrolSlot = (int)luaL_optinteger(L, 3, 0);

		if (patrolSlot > 1 || patrolSlot < 0)
			return luaL_error(L, "Bad argument #3 - patrol slot is invalid, it must be between 0 (cops) and 1 (goons)");
	}
	else {
		return luaL_error(L, "Bad argument #1 - expected 1 Vector or 3 numbers");
	}

	Vector4 pos = Vector4(x, y, z, 1);
	AIFelonySystemFelonyManagerClass* felonyMan = GetFelonyManager();
	if (felonyMan)
		felonyMan->CreatePatrolCharacterOnFoot(&pos, (AIFelonySystemPatrolCarTypeEnum)patrolSlot, angle);

	return 0;  // number of return(s)
}

int lua_CreatePatrolVehicleUnit(lua_State* L)
{
	int nargs = lua_gettop(L);

	float x, y, z, angle;
	int patrolSlot;

	bool snapToTerrain = false;
	bool useSecondaryVehicleType = false;

	if (lua_isuserdata(L, 1) != 1) {
		// Three numbers
		x = (float)luaL_checknumber(L, 1);
		y = (float)luaL_checknumber(L, 2);
		z = (float)luaL_checknumber(L, 3);
		angle = (float)luaL_optnumber(L, 4, 0);
		patrolSlot = (int)luaL_optinteger(L, 5, 0);
		if (nargs > 5)
			snapToTerrain = lua_toboolean(L, 6);
		if (nargs > 6)
			useSecondaryVehicleType = lua_toboolean(L, 7);

		if (patrolSlot > 1 || patrolSlot < 0)
			return luaL_error(L, "Bad argument #5 - patrol slot is invalid, it must be between 0 (cops) and 1 (goons)");
	}
	else if (lua_isuserdata(L, 1) == 1) {
		// Vector
		Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable);
		x = vec->X;
		y = vec->Y;
		z = vec->Z;
		angle = (float)luaL_optnumber(L, 2, 0);
		patrolSlot = (int)luaL_optinteger(L, 3, 0);
		if (nargs > 3)
			snapToTerrain = lua_toboolean(L, 4);
		if (nargs > 4)
			useSecondaryVehicleType = lua_toboolean(L, 5);

		if (patrolSlot > 1 || patrolSlot < 0)
			return luaL_error(L, "Bad argument #3 - patrol slot is invalid, it must be between 0 (cops) and 1 (goons)");
	}
	else {
		return luaL_error(L, "Bad argument #1 - expected 1 Vector or 3 numbers");
	}

	Vector4 pos = Vector4(x, y, z, 1);
	AIFelonySystemFelonyManagerClass* felonyMan = GetFelonyManager();
	if (felonyMan)
		felonyMan->CreatePatrolVehicleUnit(&pos, angle, snapToTerrain, useSecondaryVehicleType, (AIFelonySystemPatrolCarTypeEnum)patrolSlot);

	return 0;  // number of return(s)
}

int lua_SetMusicTrack(lua_State* L)
{
	int trackId = (int)luaL_checkinteger(L, 1);  // param 1

	CAmbientSoundManager* ambS = GetAmbientSoundManager();
	if (ambS)
		ambS->SetMusicTrack(trackId);

	return 0;  // number of return(s)
}

int lua_GetMileometer(lua_State* L)
{
	CProfileSettings* profile = GetProfileSettings();

	double odom = (double)profile->GetOdometer();
	odom = odom * 0.0006213712;

	lua_pushnumber(L, odom);

	return 1;
}

int lua_SetMasterSpeedMultiplier(lua_State* L)
{
	float mult = luaL_checknumber(L, 1);

	speed::SetMasterSpeedMultiplier(mult);

	return 0;
}

int lua_LaunchVEdit(lua_State* L)
{
	void* Singleton_SystemConfig = *(void**)0x70c558;

	if (Singleton_SystemConfig != NULL)
	{
		unsigned int vtable = *(unsigned int*)Singleton_SystemConfig;
		unsigned int vtable_func = *(unsigned int*)(vtable + 0x10);

		// ProcessCommand__18CState_GameRunningPCcT1()?
		((void(__thiscall*)(void*, const char*, int))vtable_func)(Singleton_SystemConfig, "vedit_enter", 0);
	}

	return 0;
}

int lua_GetInputInfo(lua_State* L)
{
	int inputId = luaL_checkinteger(L, 1);
	float input = 0;
	bool debounce = false;

	CInputManager* manager = GetInputManagerByAction((EInputAction)inputId);

	if (manager != NULL)
	{
		Input_impl* inpt = manager->GetModifiableInput((EInputAction)inputId);
		input = inpt->value_;
		debounce = inpt->debounce_;
	}

	lua_pushnumber(L, input);
	lua_pushboolean(L, debounce);

	return 2;
}

int lua_GetMoney(lua_State* L)
{
	CProfileSettings* profile = GetProfileSettings();

	int money = profile->GetMoney();

	lua_pushinteger(L, money);

	return 1;
}

int lua_SetMoney(lua_State* L)
{
	CProfileSettings* profile = GetProfileSettings();

	int money = luaL_checkinteger(L, 1);

	profile->SetMoney(money);

	return 0;
}

int lua_GetDistanceBetweenPoints2D(lua_State* L)
{
	float x1 = (float)luaL_checknumber(L, 1);
	float y1 = (float)luaL_checknumber(L, 2);

	float x2 = (float)luaL_checknumber(L, 3);
	float y2 = (float)luaL_checknumber(L, 4);

	float result = GetDistanceBetweenPoints2D(x1, y1, x2, y2);

	lua_pushnumber(L, result);

	return 1;
}

int lua_GetDistanceBetweenPoints3D(lua_State* L)
{
	float x1 = (float)luaL_checknumber(L, 1);
	float y1 = (float)luaL_checknumber(L, 2);
	float z1 = (float)luaL_checknumber(L, 3);

	float x2 = (float)luaL_checknumber(L, 4);
	float y2 = (float)luaL_checknumber(L, 5);
	float z2 = (float)luaL_checknumber(L, 6);

	float result = GetDistanceBetweenPoints3D(x1, y1, z1, x2, y2, z2);

	lua_pushnumber(L, result);

	return 1;
}

int lua_SetCameraPosition(lua_State* L)
{
	GameCamera* cam = GameCamera::GetInstance();

	int nargs = lua_gettop(L);

	float x, y, z;

	if (nargs == 1) {
		// Single argument: expect a Vector
		Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 1, g_LuaVectorMetaTable);
		x = vec->X;
		y = vec->Y;
		z = vec->Z;
	}
	else if (nargs == 3) {
		// Three numbers
		x = (float)luaL_checknumber(L, 1);
		y = (float)luaL_checknumber(L, 2);
		z = (float)luaL_checknumber(L, 3);
	}
	else {
		return luaL_error(L, "bad argument #1 - Expected 1 Vector or 3 numbers");
	}

	cam->m_Matrix.pos = Vector(x, y, z);

	return 0;  // number of return(s)
}
