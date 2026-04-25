#include "Lua_Vehicle.h"
#include "Lua_Character.h"
#include "Lua_MissionFuncs.h"
#include "..\dpl\Vector4.h"

#include "..\dpl\VehicleSpecification.h"
#include "..\dpl\VehicleSpecificationManager.h"
#include "..\dpl\CLifeAcquirableVehicleManager.h"
#include "..\dpl\SpoolableResourceManager.h"

const char* g_VehicleMetaName = "Vehicle";

void Init_Lua_MetaTable_Vehicle() 
{
	luaL_newmetatable(L, g_VehicleMetaName);

	// set __index
	lua_pushcfunction(L, lua_VehicleIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_VehicleIndex(lua_State* L) 
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "SetPosition") == 0) {
		lua_pushcfunction(L, lua_SetVehiclePosition);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetVehiclePosition);
		return 1;
	}
	else if (strcmp(key, "SetVelocity") == 0) {
		lua_pushcfunction(L, lua_SetVehicleVelocity);
		return 1;
	}
	else if (strcmp(key, "GetVelocity") == 0) {
		lua_pushcfunction(L, lua_GetVehicleVelocity);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetVehiclePointer);
		return 1;
	}
	else if (strcmp(key, "SetFelony") == 0) {
		lua_pushcfunction(L, lua_SetVehicleFelonyLevel);
		return 1;
	}
	else if (strcmp(key, "GetType") == 0 || strcmp(key, "GetModel") == 0) {
		lua_pushcfunction(L, lua_GetVehicleType);
		return 1;
	}
	else if (strcmp(key, "SetRotation") == 0) {
		lua_pushcfunction(L, lua_SetVehicleRotation);
		return 1;
	}
	else if (strcmp(key, "GetRotation") == 0) {
		lua_pushcfunction(L, lua_GetVehicleRotation);
		return 1;
	}
	else if (strcmp(key, "SetPhysicsPriority") == 0) {
		lua_pushcfunction(L, lua_SetVehiclePhysicsPriority);
		return 1;
	}
	else if (strcmp(key, "GetPhysicsPriority") == 0) {
		lua_pushcfunction(L, lua_GetVehiclePhysicsPriority);
		return 1;
	}
	else if (strcmp(key, "SetRenderingPriority") == 0) {
		lua_pushcfunction(L, lua_SetVehicleRenderingPriority);
		return 1;
	}
	else if (strcmp(key, "GetRenderingPriority") == 0) {
		lua_pushcfunction(L, lua_GetVehicleRenderingPriority);
		return 1;
	}
	else if (strcmp(key, "SetColor") == 0) {
		lua_pushcfunction(L, lua_SetVehicleColor);
		return 1;
	}
	else if (strcmp(key, "GetColor") == 0) {
		lua_pushcfunction(L, lua_GetVehicleColor);
		return 1;
	}
	else if (strcmp(key, "GetForwardVector") == 0 || strcmp(key, "GetForward") == 0) {
		lua_pushcfunction(L, lua_GetVehicleForwardVector);
		return 1;
	}
	else if (strcmp(key, "GetRightVector") == 0 || strcmp(key, "GetRight") == 0) {
		lua_pushcfunction(L, lua_GetVehicleRightVector);
		return 1;
	}
	else if (strcmp(key, "SetAngle") == 0 || strcmp(key, "SetHeading") == 0) {
		lua_pushcfunction(L, lua_SetVehicleAngle);
		return 1;
	}
	else if (strcmp(key, "GetAngle") == 0 || strcmp(key, "GetHeading") == 0) {
		lua_pushcfunction(L, lua_GetVehicleAngle);
		return 1;
	}
	else if (strcmp(key, "GetDamage") == 0) {
		lua_pushcfunction(L, lua_GetVehicleDamage);
		return 1;
	}
	else if (strcmp(key, "SetDamage") == 0) {
		lua_pushcfunction(L, lua_SetVehicleDamage);
		return 1;
	}
	else if (strcmp(key, "GetNitro") == 0) {
		lua_pushcfunction(L, lua_GetVehicleNitro);
		return 1;
	}
	else if (strcmp(key, "SetNitro") == 0) {
		lua_pushcfunction(L, lua_SetVehicleNitro);
		return 1;
	}
	else if (strcmp(key, "ActivateLamp") == 0 || strcmp(key, "SetLamp") == 0) {
		lua_pushcfunction(L, lua_ActivateVehicleLamp);
		return 1;
	}
	else if (strcmp(key, "ActivateSiren") == 0) {
		lua_pushcfunction(L, lua_ActivateVehicleSiren);
		return 1;
	}
	else if (strcmp(key, "GetDriver") == 0) {
		lua_pushcfunction(L, lua_GetVehicleDriver);
		return 1;
	}
	else if (strcmp(key, "SendManipulationPacket") == 0) {
		lua_pushcfunction(L, lua_SendVehicleManipulationPacket);
		return 1;
	}
	else if (strcmp(key, "Destroy") == 0) {
		lua_pushcfunction(L, lua_DestroyVehicle);
		return 1;
	}
	else if (strcmp(key, "Explode") == 0) {
		lua_pushcfunction(L, lua_ExplodeVehicle);
		return 1;
	}
	else if (strcmp(key, "Fix") == 0 || strcmp(key, "Repair") == 0) {
		lua_pushcfunction(L, lua_FixVehicle);
		return 1;
	}
	else if (strcmp(key, "MakeInfiniteMass") == 0 || strcmp(key, "GiveInfiniteMass") == 0) {
		lua_pushcfunction(L, lua_MakeInfiniteMass);
		return 1;
	}
	else if (strcmp(key, "MakeStatic") == 0) {
		lua_pushcfunction(L, lua_MakeVehicleStatic);
		return 1;
	}
	else if (strcmp(key, "MakeDynamic") == 0) {
		lua_pushcfunction(L, lua_MakeVehicleDynamic);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_SetVehiclePhysicsPriority(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1
	int priority = luaL_checkinteger(L, 2);

	// lol, driving type, I had not idea what to name that back then
	// light type(true) = rendering priority
	// light type(false) = physics priority
	vehicle->SetDrivingType(priority, false);

	return 0;
}

int lua_GetVehiclePhysicsPriority(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	int priority = 0;
	priority = vehicle->GetDrivingType();

	return 1; 
}

int lua_SetVehicleRenderingPriority(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1
	int priority = luaL_checkinteger(L, 2);

	// lol, driving type, I had not idea what to name that back then
	// light type(true) = rendering priority
	// light type(false) = physics priority
	vehicle->SetDrivingType(priority, true);

	return 0;
}

int lua_GetVehicleRenderingPriority(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	int priority = *(int*)(vehicle->GetPointer() + 0x9C);

	return 1;
}

int lua_ExplodeVehicle(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	vehicle->Kaboom();
	vehicle->Explode();

	return 0;
}

int lua_FixVehicle(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	float R = *(float*)((int)vehicle + 140);
	float G = *(float*)((int)vehicle + 144);
	float B = *(float*)((int)vehicle + 148);
	vehicle->ResetDamage();
	vehicle->SetColor(R, G, B);

	return 0;
}

int lua_SetVehicleNitro(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1
	float nitro = luaL_checknumber(L, 2);

	if (vehicle->GetCustomCarData() == NULL)
	{
		sCustomCar* custom = new sCustomCar();

		// sCustomCar::Reset()
		((void(__thiscall*)(sCustomCar*))0x57cb7a)(custom);

		//custom->KitParts = 0; // since this is new, it should be 0

		//// for some reason, the PS2 prototype used flag 0x1000?
		//custom->KitParts = custom->KitParts | 0x10;

		// add nitro part - sCustomCar::AddPart()
		((void(__thiscall*)(sCustomCar*, int, int))0x57ccfe)(custom, 0x10F, 0x80);

		custom->nitro = nitro;

		vehicle->SetCustomCarData(custom);
	}
	else
	{
		sCustomCar* custom = vehicle->GetCustomCarData();
		//custom->KitParts = custom->KitParts | 0x10;
		
		// add nitro part - sCustomCar::AddPart()
		((void(__thiscall*)(sCustomCar*, int, int))0x57ccfe)(custom, 0x10F, 0x80);
		
		custom->nitro = nitro;

		vehicle->SetCustomCarData(custom);
	}

	return 0;
}

int lua_GetVehicleNitro(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	if (vehicle->GetCustomCarData() == NULL)
	{
		sCustomCar* custom = vehicle->GetCustomCarData();
		lua_pushnumber(L, custom->nitro);

		return 1;
	}

	lua_pushnumber(L, 0);
	return 1;
}

int lua_GetVehiclePointer(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	lua_pushinteger(L, (int)vehicle);

	return 1;
}

int lua_GetVehicleType(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	lua_pushinteger(L, *vehicle->GetVehicleType());

	return 1;
}

int lua_GetVehicleDamage(lua_State* L) 
{ 
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	lua_pushinteger(L, vehicle->GetDamage());

	return 0;
}

int lua_SetVehicleDamage(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	float damage = luaL_checknumber(L, 2);

	vehicle->SetDamage(damage);

	return 0;
}

int lua_ActivateVehicleLamp(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	int nargs = lua_gettop(L) - 1; // number of arguments after 'self'

	int partId = luaL_checkinteger(L, 2);
	bool onoff = lua_toboolean(L, 3);
	bool over = false;

	if (nargs == 0)
		return luaL_error(L, "bad argument #1 - expected boolean");

	if (nargs > 2)
		over = lua_toboolean(L, 4);

	vehicle->ActivateLamp((ePartSubType)partId, onoff, over);

	return 0;
}

int lua_ActivateVehicleSiren(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	int nargs = lua_gettop(L) - 1; // number of arguments after 'self'

	bool onoff = lua_toboolean(L, 2);

	if (nargs == 0)
		return luaL_error(L, "bad argument #1 - expected boolean");

	vehicle->ActivateLamp(PST_SIRENLIGHT, onoff, false);

	return 0;
}

int lua_SetVehicleVelocity(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

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
	vehicle->SetVelocity(&pos);

	return 0;  // number of return(s)
}

int lua_GetVehicleForwardVector(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 fwd = Vector4();
	Matrix mt = Matrix();
	vehicle->GetMatrix(&mt);

	fwd.X = mt.forward.X;
	fwd.Y = mt.forward.Y;
	fwd.Z = mt.forward.Z;

	vecRes->X = fwd.X;
	vecRes->Y = fwd.Y;
	vecRes->Z = fwd.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetVehicleRightVector(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 fwd = Vector4();
	Matrix mt = Matrix();
	vehicle->GetMatrix(&mt);

	fwd.X = mt.right.X;
	fwd.Y = mt.right.Y;
	fwd.Z = mt.right.Z;

	vecRes->X = fwd.X;
	vecRes->Y = fwd.Y;
	vecRes->Z = fwd.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_SetVehiclePosition(lua_State* L) 
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

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
	vehicle->SetPosition(&pos);

	return 0;  // number of return(s)
}

int lua_GetVehicleVelocity(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = Vector4();
	vehicle->GetVelocity(&pos);

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetVehiclePosition(lua_State* L) 
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = Vector4();
	vehicle->GetPosition(&pos);

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_SetVehicleColor(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	float r = luaL_checknumber(L, 2);
	float g = luaL_checknumber(L, 3);
	float b = luaL_checknumber(L, 4);

	vehicle->SetColor(r, g, b);

	return 0;
}

int lua_GetVehicleColor(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	float r = 0;
	float g = 0;
	float b = 0;

	Vector col = vehicle->GetColor();

	r = col.X;
	g = col.Y;
	b = col.Z;

	lua_pushnumber(L, r);
	lua_pushnumber(L, g);
	lua_pushnumber(L, b);

	return 0;
}

int lua_SetVehicleAngle(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	double yaw = luaL_checknumber(L, 2);
	double roll = 0;
	double pitch = 0;

	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

	Vector4 q = Vector4();

	q.W = cy * cp * cr + sy * sp * sr;
	q.X = cy * sp * cr + sy * cp * sr;
	q.Y = sy * cp * cr - cy * sp * sr;
	q.Z = cy * cp * sr - sy * sp * cr;

	// normalise
	double magnitude = sqrt(q.W*q.W + q.X*q.X + q.Y*q.Y + q.Z*q.Z);
	q.W /= magnitude;
	q.X /= magnitude;
	q.Y /= magnitude;
	q.Z /= magnitude;

	vehicle->SetDirection(q);

	return 0;
}

int lua_GetVehicleAngle(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	Vector4 q = vehicle->GetDirection(); // param 1
	Vector4 v = Vector4();

	// Pitch (X axis)
	double sinp = 2.0 * (q.W * q.X + q.Y * q.Z);
	double cosp = 1.0 - 2.0 * (q.X * q.X + q.Y * q.Y);
	v.Y = atan2(sinp, cosp);

	// Yaw (Y axis)
	double siny = 2.0 * (q.W * q.Y - q.Z * q.X);
	if (fabs(siny) >= 1.0)
		v.X = copysign(MATH_PI / 2.0, siny); // clamp out of range
	else
		v.X = asin(siny);

	// Roll (Z axis)
	double sinr = 2.0 * (q.W * q.Z + q.X * q.Y);
	double cosr = 1.0 - 2.0 * (q.Y * q.Y + q.Z * q.Z);
	v.Z = atan2(sinr, cosr);

	// Convert back to degrees if you want
	//v.X *= 180.0 / MATH_PI; // yaw
	//v.Y *= 180.0 / MATH_PI; // pitch
	//v.Z *= 180.0 / MATH_PI; // roll

	lua_pushnumber(L, v.X);

	return 1;
}

int lua_SetVehicleRotation(lua_State* L) 
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	int nargs = lua_gettop(L) - 1; // number of arguments after 'self'

	float x, y, z, w;

	if (nargs == 1) {
		// Single argument: expect a Vector
		Lua_Quaternion* vec = *(Lua_Quaternion**)luaL_checkudata(L, 2, g_LuaQuaternionMetaTable);
		x = vec->X;
		y = vec->Y;
		z = vec->Z;
		w = vec->W;
	}
	else if (nargs == 4) {
		// Three numbers
		x = (float)luaL_checknumber(L, 2);
		y = (float)luaL_checknumber(L, 3);
		z = (float)luaL_checknumber(L, 4);
		w = (float)luaL_checknumber(L, 5);
	}
	else {
		return luaL_error(L, "Expected 1 Quaternion or 4 numbers");
	}

	Vector4 rotation = Vector4(x, y, z, w);
	vehicle->SetDirection(&rotation);

	return 0;  // number of return(s)
}

int lua_GetVehicleRotation(lua_State* L) 
{ 
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Quaternion();

	Lua_Quaternion* vecRes = *(Lua_Quaternion**)udata;

	Vector4 rotation = vehicle->GetDirection();

	vecRes->X = rotation.X;
	vecRes->Y = rotation.Y;
	vecRes->Z = rotation.Z;
	vecRes->W = rotation.W;

	luaL_getmetatable(L, g_LuaQuaternionMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetVehicleDriver(lua_State* L) 
{
	CVehicle* vehicle =
		*(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName);

	CCharacter* character = vehicle->GetDriver();

	if (!character)
	{
		lua_pushnil(L);
		return 1;
	}

	// allocate userdata to hold the pointer
	CCharacter** udata = (CCharacter**)lua_newuserdata(L, sizeof(CCharacter*));
	*udata = character;

	// attach the vehicle metatable
	luaL_getmetatable(L, g_CharacterMetaName);
	lua_setmetatable(L, -2);

	return 1;
}

int lua_CreateVehicle(lua_State* L)
{
	int model;
	float x, y, z;
	float angle;

	model = (int)luaL_checkinteger(L, 1);

	x = (float)luaL_checknumber(L, 2);
	y = (float)luaL_checknumber(L, 3);
	z = (float)luaL_checknumber(L, 4);

	angle = (float)luaL_optnumber(L, 5, 0.0);

	SpoolableResourceManager* spr = SpoolableResourceManager::GetInstance();
	spr->SetEntityPriority(SpooledPackageType_Vehicles, model, ESpoolPriority_Required);

	CVehicleManager* manager = CVehicleManager::GetInstance();
	AutoPtr<CVehicle, int> pCar;

	CVehicleSpecification::g_bTankEnable = true;
	AutoPtr<CVehicle, int>* out = manager->CreateVehicle(&pCar, tVehicleModelUID(model), x, y, z, 25, angle, false, true, true);
	pCar.m_pPointer = out->m_pPointer;
	CVehicleSpecification::g_bTankEnable = false;

	if (pCar.m_pPointer != nullptr)
		LifeAcquirableVehicleManager::GetInstance()->AddVehicle(pCar.m_pPointer, 1);

	CVehicle** udata = (CVehicle**)lua_newuserdata(L, sizeof(void*));
	*udata = pCar.m_pPointer;

	luaL_getmetatable(L, g_VehicleMetaName); // return metatable type
	lua_setmetatable(L, -2); // return/set the return

	return 1;
}

int lua_DestroyVehicle(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	CVehicleManager* manager = CVehicleManager::GetInstance();
	LifeAcquirableVehicleManager* lfav = LifeAcquirableVehicleManager::GetInstance();
	
	lfav->RemoveVehicle(vehicle);
	AutoPtr<CVehicle, int> delVeh;
	delVeh.m_pPointer = vehicle;

	manager->FreeVehicle(&delVeh);

	return 0;
}

int lua_MakeInfiniteMass(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	vehicle->MakeInfiniteMass();

	return 0;
}

int lua_MakeVehicleStatic(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	vehicle->MakeStatic();

	return 0;
}

int lua_MakeVehicleDynamic(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	vehicle->MakeDynamic();

	return 0;
}

int lua_SendVehicleManipulationPacket(lua_State* L) 
{ 
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName); // param 1

	int nargs = lua_gettop(L);

	SVehicleManipulationPacket packet;
	float thrust, steerAngle, burnout, hornVol, leanFB;
	bool nitro, handbrake, action1, brakeIsPressed;

	thrust = (int)luaL_checknumber(L, 2);
	steerAngle = (int)luaL_checknumber(L, 3);

	// optional
	burnout = (int)luaL_optnumber(L, 4, 0);
	leanFB = (int)luaL_optnumber(L, 5, 0);
	hornVol = (int)luaL_optnumber(L, 6, 0);

	if (nargs > 6)
		nitro = lua_toboolean(L, 7);
	if (nargs > 7)
		handbrake = lua_toboolean(L, 8);
	if (nargs > 8)
		brakeIsPressed = lua_toboolean(L, 9);
	if (nargs > 9)
		action1 = lua_toboolean(L, 10);

	packet.fThrust = thrust;
	packet.fSteerValue = steerAngle;
	packet.fBurnout = burnout;
	packet.fLeanFB = leanFB;
	packet.fHornVolume = hornVol;
	// 1 = true, 0 = false
	packet.bNitro = nitro; 
	packet.bHandbrake = handbrake;
	packet.bBrakeIsPressed = brakeIsPressed;
	packet.bAction1 = action1;

	if (vehicle)
		vehicle->SendManipulationPacket(&packet);

	return 0;
}