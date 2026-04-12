#include "Lua_CharacterActor.h"
#include "Lua_VehicleActor.h"
#include "..\dpl\Factory.h"
#include "..\dpl\MathFuncs.h"
#include "..\dpl\CLifeSystem_AIChaseCoordinator.h"

const char* g_CharacterActorMetaName = "Character_Actor";

void Init_Lua_MetaTable_CharacterActor()
{
	luaL_newmetatable(L, g_CharacterActorMetaName);

	// set __index
	lua_pushcfunction(L, lua_CharacterActorIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_CharacterActorIndex(lua_State* L)
{
	CLifeActor_Character* acharacter = *(CLifeActor_Character**)luaL_checkudata(L, 1, g_CharacterActorMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "GetInstance") == 0) {
		lua_pushcfunction(L, lua_GetCharacterActorInstance);
		return 1;
	}
	else if (strcmp(key, "GetLifeInstance") == 0) {
		lua_pushcfunction(L, lua_GetCharacterActorInstance);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetCharacterActorPointer);
		return 1;
	}
	else if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetCharacterActorPosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetCharacterActorPosition);
		return 1;
	}
	else if (strcmp(key, "SetRotation") == 0) {
		lua_pushcfunction(L, lua_SetCharacterActorRotation);
		return 1;
	}
	else if (strcmp(key, "GetRotation") == 0) {
		lua_pushcfunction(L, lua_GetCharacterActorRotation);
		return 1;
	}
	else if (strcmp(key, "GetForwardVector") == 0 || strcmp(key, "GetForward") == 0) {
		lua_pushcfunction(L, lua_GetCharacterActorForwardVector);
		return 1;
	}
	else if (strcmp(key, "GetRightVector") == 0 || strcmp(key, "GetRight") == 0) {
		lua_pushcfunction(L, lua_GetCharacterActorRightVector);
		return 1;
	}
	else if (strcmp(key, "Create") == 0 || strcmp(key, "Instantiate") == 0) {
		lua_pushcfunction(L, lua_InstantiateCharacterActor);
		return 1;
	}
	else if (strcmp(key, "Destroy") == 0 || strcmp(key, "Delete") == 0) {
		lua_pushcfunction(L, lua_DestroyCharacterActor);
		return 1;
	}
	else if (strcmp(key, "GoWander") == 0) {
		lua_pushcfunction(L, lua_CharacterActorGoWander);
		return 1;
	}
	else if (strcmp(key, "StopWander") == 0) {
		lua_pushcfunction(L, lua_CharacterActorStopWander);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_CharacterActorGoWander(lua_State* L)
{
	CLifeActor_Character* acharacter = *(CLifeActor_Character**)luaL_checkudata(L, 1, g_CharacterActorMetaName);
	
	int nargs = lua_gettop(L);

	float speed = luaL_optnumber(L, 2, 30.0f);
	float acceleration = luaL_optnumber(L, 3, 1.0f);
	float traction = luaL_optnumber(L, 4, 1.0f);
	float handOfTom = luaL_optnumber(L, 5, 1.0f);
	
	bool driveAsCiv = false;
	if (nargs > 5)
		driveAsCiv = lua_toboolean(L, 6);

	int cheatSettings = luaL_optinteger(L, 7, 1);

	auto ai = CLifeSystem_AIChaseCoordinator::GetInstance();
	if (ai)
	{
		TPursuerPointer pursuer = ai->GetPursuer((CLifeActor*)acharacter);
		if (pursuer != NULL)
		{
			pursuer->m_pPursuer->m_rDesiredChaseSpeed = speed;
			pursuer->m_pPursuer->m_rAccelerationMultiplier = acceleration;
			pursuer->m_pPursuer->m_rTractionMultiplier = traction;
			pursuer->m_pPursuer->m_rHOGMultiplier = handOfTom;
			pursuer->m_pPursuer->m_bDriveAsCiv = driveAsCiv;
			pursuer->m_pPursuer->m_eCheatSettings = (eCheatSettings)cheatSettings;

			ai->StartRandomWander(pursuer);
		}
	}

	return 0;
}

int lua_CharacterActorStopWander(lua_State* L)
{
	CLifeActor_Character* acharacter = *(CLifeActor_Character**)luaL_checkudata(L, 1, g_CharacterActorMetaName);

	auto ai = CLifeSystem_AIChaseCoordinator::GetInstance();
	if (ai)
	{
		TPursuerPointer pursuer = ai->GetPursuer((CLifeActor*)acharacter);
		if (pursuer != NULL)
		{
			ai->StopRandomWander(&pursuer);
		}
	}

	return 0;
}

int lua_GetCharacterActorForwardVector(lua_State* L)
{
	// TODO
	return 0;
}

int lua_GetCharacterActorRightVector(lua_State* L)
{
	// TODO
	return 0;
}

int lua_GetCharacterActorPosition(lua_State* L)
{
	CLifeActor_Character* acharacter = *(CLifeActor_Character**)luaL_checkudata(L, 1, g_CharacterActorMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = acharacter->GetPosition();

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_SetCharacterActorRotation(lua_State* L)
{
	// TODO
	return 0;
}

int lua_GetCharacterActorRotation(lua_State* L)
{
	// TODO
	return 0;
}

int lua_SetCharacterActorPosition(lua_State* L)
{
	CLifeActor_Character* acharacter = *(CLifeActor_Character**)luaL_checkudata(L, 1, g_CharacterActorMetaName);

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
		return luaL_error(L, "Expected 1 Vector or 3 numbers");
	}

	Vector4 pos = Vector4(x, y, z, 1);
	acharacter->m_matrix.pos = Vector(x, y, z);
	acharacter->m_initialPosition = pos;

	if (acharacter->m_piCharacterInstance != NULL)
	{
		if (acharacter->m_piCharacterInstance->m_piCharacter != NULL)
		{
			acharacter->m_piCharacterInstance->m_piCharacter->SetPosition(&pos);
		}
	}

	return 0;  // number of return(s)
}

int lua_GetCharacterActorInstance(lua_State* L)
{
	CLifeActor_Character* acharacter = *(CLifeActor_Character**)luaL_checkudata(L, 1, g_CharacterActorMetaName);

	if (acharacter->m_piCharacterInstance == NULL)
	{
		lua_pushnil(L);
		return 1;
	}

	CCharacter* retChar = acharacter->m_piCharacterInstance->m_piCharacter; // m_piCharacter

	if (retChar == NULL)
	{
		lua_pushnil(L);
		return 1;
	}

	// allocate userdata to hold the pointer
	CCharacter** udata = (CCharacter**)lua_newuserdata(L, sizeof(CCharacter*));
	*udata = retChar;

	// attach the vehicle metatable
	luaL_getmetatable(L, g_CharacterMetaName);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_GetCharacterActorPointer(lua_State* L)
{
	CLifeActor_Character* acharacter = *(CLifeActor_Character**)luaL_checkudata(L, 1, g_CharacterActorMetaName);

	lua_pushinteger(L, (int)acharacter);

	return 1;
}

int lua_CreateCharacterActor(lua_State* L)
{
	int nargs = lua_gettop(L);

	int skin;
	float x, y, z;
	float angle;

	skin = (int)luaL_checkinteger(L, 1);

	x = (float)luaL_checknumber(L, 2);
	y = (float)luaL_checknumber(L, 3);
	z = (float)luaL_checknumber(L, 4);

	angle = (float)luaL_optnumber(L, 5, 0.0);

	bool startCreated = true;
	if (nargs > 5)
		startCreated = lua_toboolean(L, 6);

	EWeapons wep = (EWeapons)luaL_optinteger(L, 7, 0);
	float initialHealth = luaL_optnumber(L, 8, 1.0f);
	float felony = luaL_optnumber(L, 9, 0.0f);
	CLifeActor_Vehicle** initialVehicle = (CLifeActor_Vehicle**)luaL_testudata(L, 10, g_VehicleActorMetaName);
	int initialVehicleSeat = luaL_optinteger(L, 11, 0);

	bool addToFelonyManager = false;
	if (nargs > 11)
		addToFelonyManager = lua_toboolean(L, 12);
	bool doNotUseIdleAnims = false;
	if (nargs > 12)
		doNotUseIdleAnims = lua_toboolean(L, 13);
	bool isPlayer = false;
	if (nargs > 13)
		isPlayer = lua_toboolean(L, 14);

	CLifeActor_Character* acharacter = (CLifeActor_Character*)hamster::CreateObject(EFactoryType::EFactoryType_LifeActor_Character);

	if (acharacter != NULL)
	{
		float fx = sin(angle);
		float fz = cos(angle);

		Matrix mat = Matrix();
		mat.pos = Vector(x, y, z);

		mat.forward = Vector(fx, 0, fz);
		mat.right = CrossProduct(Vector(0, 1, 0), mat.forward);
		mat.up = CrossProduct(mat.forward, mat.right);

		CLifeActor_Vehicle* iveh = NULL;
		if (initialVehicle)
			iveh = *initialVehicle;

		acharacter->CustomInitialise((ECharacterType)skin, mat, wep, initialHealth, felony, iveh, initialVehicleSeat, startCreated, addToFelonyManager, doNotUseIdleAnims, isPlayer);

		CLifeActor_Character** udata = (CLifeActor_Character**)lua_newuserdata(L, sizeof(void*));
		*udata = acharacter;

		luaL_getmetatable(L, g_CharacterActorMetaName); // return metatable type
		lua_setmetatable(L, -2); // return/set the return


		//if (startCreated)
		//{
			// create instance first which is very important because Create() checks that
			//((CLifeActor*)acharacter)->CreateInstance();

			//((CLifeActor*)acharacter)->Create();
		//}

		return 1;
	}

	lua_pushnil(L);
	return 1;
}

int lua_DestroyCharacterActor(lua_State* L)
{
	CLifeActor_Character* acharacter = *(CLifeActor_Character**)luaL_checkudata(L, 1, g_CharacterActorMetaName);
	((CLifeActor*)acharacter)->Delete();
	return 0;
}

int lua_InstantiateCharacterActor(lua_State* L)
{
	CLifeActor_Character* acharacter = *(CLifeActor_Character**)luaL_checkudata(L, 1, g_CharacterActorMetaName);
	if (acharacter->m_piCharacterInstance == NULL)
		((CLifeActor*)acharacter)->CreateInstance();

	((CLifeActor*)acharacter)->Create();
	return 0;
}