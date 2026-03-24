#include "Lua_Character.h"
#include "Lua_Vehicle.h"
#include "Lua_MissionFuncs.h"
#include "..\dpl\CCharacter.h"

const char* g_CharacterMetaName = "Character";

void Init_Lua_MetaTable_Character()
{
	luaL_newmetatable(L, g_CharacterMetaName);

	Setup_Lua_MetaTable_Character(false);

	lua_pop(L, 1);
}

void Setup_Lua_MetaTable_Character(bool popStack)
{
	// set __index
	lua_pushcfunction(L, lua_CharacterIndex);
	lua_setfield(L, -2, "__index");

	if (popStack)
	{
		lua_pop(L, 1);
	}
}

int lua_CharacterIndex(lua_State* L)
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetCharacterPosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetCharacterPosition);
		return 1;
	}
	else if (strcmp(key, "GetAngle") == 0 || strcmp(key, "GetHeading") == 0) {
		lua_pushcfunction(L, lua_GetCharacterAngle);
		return 1;
	}
	else if (strcmp(key, "SetAngle") == 0 || strcmp(key, "SetHeading") == 0) {
		lua_pushcfunction(L, lua_SetCharacterAngle);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetCharacterPointer);
		return 1;
	}
	else if (strcmp(key, "GetVehicle") == 0) {
		lua_pushcfunction(L, lua_GetCharacterVehicle);
		return 1;
	}
	else if (strcmp(key, "TeleportIntoVehicle") == 0 || strcmp(key, "WarpIntoVehicle") == 0 || strcmp(key, "SetVehicle") == 0) {
		lua_pushcfunction(L, lua_TeleportCharacterIntoVehicle);
		return 1;
	}
	else if (strcmp(key, "GetCanExitVehicle") == 0) {
		lua_pushcfunction(L, lua_GetCharacterCanExitVehicle);
		return 1;
	}
	else if (strcmp(key, "SetCanExitVehicle") == 0) {
		lua_pushcfunction(L, lua_SetCharacterCanExitVehicle);
		return 1;
	}
	else if (strcmp(key, "ForceIdleMode") == 0) {
		lua_pushcfunction(L, lua_CharacterForceIdleMode);
		return 1;
	}
	else if (strcmp(key, "SetFelony") == 0) {
		lua_pushcfunction(L, lua_SetFelonyLevel);
		return 1;
	}
	else if (strcmp(key, "GetFelony") == 0) {
		lua_pushcfunction(L, lua_GetFelonyLevel);
		return 1;
	}
	else if (strcmp(key, "GetForwardVector") == 0 || strcmp(key, "GetForward") == 0) {
		lua_pushcfunction(L, lua_GetCharacterForwardVector);
		return 1;
	}
	else if (strcmp(key, "GetRightVector") == 0 || strcmp(key, "GetRight") == 0) {
		lua_pushcfunction(L, lua_GetCharacterRightVector);
		return 1;
	}
	else if (strcmp(key, "PlayMissionAnimation") == 0) {
		lua_pushcfunction(L, lua_CharacterPlayMissionAnimation);
		return 1;
	}
	else if (strcmp(key, "KillMissionAnimations") == 0) {
		lua_pushcfunction(L, lua_CharacterKillMissionAnimations);
		return 1;
	}
	else if (strcmp(key, "EnterVehicle") == 0) {
		lua_pushcfunction(L, lua_CharacterEnterVehicle);
		return 1;
	}
	else if (strcmp(key, "ExitVehicle") == 0) {
		lua_pushcfunction(L, lua_CharacterExitVehicle);
		return 1;
	}
	else if (strcmp(key, "EjectFromVehicle") == 0) {
		lua_pushcfunction(L, lua_CharacterEjectFromVehicle);
		return 1;
	}
	else if (strcmp(key, "SetArrested") == 0) {
		lua_pushcfunction(L, lua_CharacterSetArrested);
		return 1;
	}
	else if (strcmp(key, "SetHealth") == 0) {
		lua_pushcfunction(L, lua_CharacterSetHealth);
		return 1;
	}
	else if (strcmp(key, "GetHealth") == 0) {
		lua_pushcfunction(L, lua_CharacterGetHealth);
		return 1;
	}
	else if (strcmp(key, "SwapSkin") == 0) {
		lua_pushcfunction(L, lua_CharacterSwapSkin);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_SetCharacterPosition(lua_State* L)
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	int nargs = lua_gettop(L) - 1; // number of arguments after 'self'

	float x, y, z;

	if (nargs == 1) {
		// Single argument: expect a Vector
		Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 2, g_LuaVectorMetaTable);
		x = vec->X;
		y = vec->Y;
		z = vec->Z;
	}
	else if (nargs == 3) {
		// Three numbers
		x = (float)luaL_checknumber(L, 2);
		y = (float)luaL_checknumber(L, 3);
		z = (float)luaL_checknumber(L, 4);
	}
	else {
		return luaL_error(L, "Bad argument #1 - Expected 1 Vector or 3 numbers");
	}

	Vector4 pos = Vector4(x,y,z,1);
	character->SetPosition(&pos);

	return 0;  // number of return(s)
}

int lua_GetCharacterPosition(lua_State* L)
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = Vector4();
	character->GetPosition(&pos);

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetCharacterForwardVector(lua_State* L)
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 fwd = Vector4();
	Matrix* mt = character->GetMatrix();
	fwd.X = mt->forward.X;
	fwd.Y = mt->forward.Y;
	fwd.Z = mt->forward.Z;

	vecRes->X = fwd.X;
	vecRes->Y = fwd.Y;
	vecRes->Z = fwd.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetCharacterRightVector(lua_State* L)
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 fwd = Vector4();
	Matrix* mt = character->GetMatrix();
	fwd.X = mt->right.X;
	fwd.Y = mt->right.Y;
	fwd.Z = mt->right.Z;

	vecRes->X = fwd.X;
	vecRes->Y = fwd.Y;
	vecRes->Z = fwd.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetCharacterVehicle(lua_State* L) 
{
	CCharacter* character =
		*(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName);

	CVehicle* vehicle = character->GetVehicle();

	if (!vehicle)
	{
		lua_pushnil(L);
		return 1;
	}

	// allocate userdata to hold the pointer
	CVehicle** udata = (CVehicle**)lua_newuserdata(L, sizeof(CVehicle*));
	*udata = vehicle;

	// attach the vehicle metatable
	luaL_getmetatable(L, g_VehicleMetaName);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_TeleportCharacterIntoVehicle(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	if (!lua_isinteger(L, 3)) {
		return luaL_error(L, "Bad argument #2 - Expected a integer");
	}

	CVehicle* veh = *(CVehicle**)luaL_checkudata(L, 2, g_VehicleMetaName);
	int seat = lua_tointeger(L, 3);
		
	if (veh == NULL)
		return luaL_error(L, "Bad argument #1 - The target vehicle is nil");

	if (seat < -1 || seat > 32)
		return luaL_error(L, "Bad argument #2 - Invalid seat ID, try using non-negative numbers or a smaller number");

	character->TeleportToVehicle(veh, seat, false);

	return 0;  // number of return(s)
}

int lua_GetCharacterPointer(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	lua_pushinteger(L, (int)character);

	return 1;
}

int lua_GetCharacterAngle(lua_State* L)
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	double angle = (double)character->GetAngle();
	
	// D:PL doesn't work with degrees all the time
	//angle = (angle * 180) / MATH_PI; // convert to degrees

	lua_pushnumber(L, angle);

	return 1;
}

int lua_SetCharacterAngle(lua_State* L)
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	double angle = luaL_checknumber(L, 2);

	// D:PL doesn't work with degrees all the time
	//angle = (angle * 180) / MATH_PI; // convert to degrees

	character->SetAngle((float)angle);

	return 0;
}

int lua_GetCharacterCanExitVehicle(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	lua_pushboolean(L, character->GetAllowGetOutOfVehicle());

	return 1;
}

int lua_SetCharacterCanExitVehicle(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1
	if (!lua_isboolean(L, 2)) {
		return luaL_error(L, "Expected a number");
	}

	bool allow = lua_toboolean(L, 2);

	character->SetAllowGetOutOfVehicle(allow);

	return 0;  // number of return(s)
}

int lua_CharacterForceIdleMode(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	character->ForceIdleMode();

	return 0;
}

// TODO
int lua_CharacterPlayMissionAnimation(lua_State* L) { return 0; }

int lua_CharacterKillMissionAnimations(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	character->KillMissionAnimations();

	return 0;
}

int lua_CharacterEnterVehicle(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	if (!lua_isinteger(L, 3)) {
		return luaL_error(L, "Bad argument #2 - Expected a integer");
	}
	if (!lua_isboolean(L, 4)) {
		return luaL_error(L, "Bad argument #3 - Expected a boolean");
	}

	CVehicle* veh = *(CVehicle**)luaL_checkudata(L, 2, g_VehicleMetaName);
	int seat = lua_tointeger(L, 3);
	int hijack = lua_toboolean(L, 4);

	if (veh == NULL)
		return luaL_error(L, "Bad argument #1 - The target vehicle is nil");

	if (seat < -1 || seat > 32)
		return luaL_error(L, "Bad argument #2 - Invalid seat ID, try using non-negative numbers or a smaller number");

	character->EnterVehicle(veh, seat, hijack, true);

	return 0;  // number of return(s)
}

int lua_CharacterExitVehicle(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	character->ExitVehicle(0, 0, 0);

	return 0;  // number of return(s)
}

int lua_CharacterEjectFromVehicle(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	character->EjectFromVehicle();

	return 0;  // number of return(s)
}

int lua_CharacterSetArrested(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	character->SetArrested();

	return 0;  // number of return(s)
}

int lua_CharacterSetHealth(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	float h = luaL_checknumber(L, 2);

	character->SetHealth(h);

	return 0;  // number of return(s)
}

int lua_CharacterGetHealth(lua_State* L) 
{
	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName); // param 1

	lua_pushnumber(L, character->GetHealth());

	return 1;
}

// TODO
int lua_CharacterSwapSkin(lua_State* L) { return 0; }