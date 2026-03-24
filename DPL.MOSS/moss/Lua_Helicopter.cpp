#include "Lua_Helicopter.h"
#include "..\dpl\Vector4.h"

#include "..\dpl\SpoolableResourceManager.h"

const char* g_HelicopterMetaName = "Helicopter";

void Init_Lua_MetaTable_Helicopter()
{
	luaL_newmetatable(L, g_HelicopterMetaName);

	// set __index
	lua_pushcfunction(L, lua_HelicopterIndex);
	lua_setfield(L, -2, "__index");

	lua_pop(L, 1);
}

int lua_HelicopterIndex(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);
	const char* key = lua_tostring(L, 2);

	// NOTE: methods are like a _thiscall [MyFunc(void* this, ...)]

	if (strcmp(key, "SetPosition") == 0 || strcmp(key, "SetDesiredPosition") == 0) {
		lua_pushcfunction(L, lua_SetHelicopterDesiredPosition);
		return 1;
	}
	else if (strcmp(key, "StepTo") == 0) {
		lua_pushcfunction(L, lua_HelicopterStepTo);
		return 1;
	}
	else if (strcmp(key, "GetPosition") == 0) {
		lua_pushcfunction(L, lua_GetHelicopterPosition);
		return 1;
	}
	else if (strcmp(key, "GetDesiredPosition") == 0) {
		lua_pushcfunction(L, lua_GetHelicopterDesiredPosition);
		return 1;
	}
	else if (strcmp(key, "GetPointer") == 0) {
		lua_pushcfunction(L, lua_GetHelicopterPointer);
		return 1;
	}
	else if (strcmp(key, "SetHeading") == 0 || strcmp(key, "SetAngle") == 0) {
		lua_pushcfunction(L, lua_SetHelicopterDesiredHeading);
		return 1;
	}
	else if (strcmp(key, "GetHeading") == 0 || strcmp(key, "GetAngle") == 0) {
		lua_pushcfunction(L, lua_GetHelicopterDesiredHeading);
		return 1;
	}
	else if (strcmp(key, "GetVelocity") == 0) {
		lua_pushcfunction(L, lua_GetHelicopterVelocity);
		return 1;
	}
	else if (strcmp(key, "GetDesiredVelocity") == 0) {
		lua_pushcfunction(L, lua_GetHelicopterDesiredVelocity);
		return 1;
	}
	else if (strcmp(key, "SetDesiredVelocity") == 0) {
		lua_pushcfunction(L, lua_SetHelicopterDesiredVelocity);
		return 1;
	}
	else if (strcmp(key, "GetForwardVector") == 0 || strcmp(key, "GetForward") == 0) {
		lua_pushcfunction(L, lua_GetHelicopterForwardVector);
		return 1;
	}
	else if (strcmp(key, "GetRightVector") == 0 || strcmp(key, "GetRight") == 0) {
		lua_pushcfunction(L, lua_GetHelicopterRightVector);
		return 1;
	}
	else if (strcmp(key, "GetDamage") == 0) {
		lua_pushcfunction(L, lua_GetHelicopterDamage);
		return 1;
	}
	else if (strcmp(key, "SetDamage") == 0) {
		lua_pushcfunction(L, lua_SetHelicopterDamage);
		return 1;
	}
	else if (strcmp(key, "UpdateMotion") == 0) {
		lua_pushcfunction(L, lua_UpdateHelicopterMotion);
		return 1;
	}
	else {
		lua_pushnil(L);
	}

	return 1;
}

int lua_GetHelicopterPointer(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	lua_pushinteger(L, (int)heli);

	return 1;
}

// TODO
int lua_GetHelicopterDamage(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	float damage = heli->m_rDamage;
	lua_pushnumber(L, damage);

	return 1;
}

int lua_SetHelicopterDamage(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	float damage = luaL_checknumber(L, 1);

	heli->m_rDamage = damage;

	return 0;
}

int lua_SetHelicopterDesiredPosition(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

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
		return luaL_error(L, "bad argument #1 - Expected 1 Vector or 3 numbers");
	}

	Vector4 pos = Vector4(x, y, z, 1);
	heli->m_v4DesiredPosition = pos;

	return 0;  // number of return(s)
}

float WrapAngle(float angle)
{
	const float PI = 3.14159265f;

	while (angle > PI)  angle -= 2 * PI;
	while (angle < -PI) angle += 2 * PI;

	return angle;
}

float StepAngle(float current, float target, float maxStep)
{
	float delta = WrapAngle(target - current);

	// clamp rotation step
	if (delta > maxStep)  delta = maxStep;
	if (delta < -maxStep) delta = -maxStep;

	return current + delta;
}

int lua_HelicopterStepTo(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	int nargs = lua_gettop(L);

	float x2, y2, z2 = 0;
	float angle = 0;
	float speed = 0;

	if (lua_isuserdata(L, 1) != 1) {
		// Three numbers
		x2 = (float)luaL_checknumber(L, 2);
		y2 = (float)luaL_checknumber(L, 3);
		z2 = (float)luaL_checknumber(L, 4);
		angle = (float)luaL_optnumber(L, 5, heli->m_rDesiredHeading);
		speed = (int)luaL_optnumber(L, 6, 25.0f);
	}
	else if (lua_isuserdata(L, 1) == 1) {
		// Vector
		Lua_Vector* vec = *(Lua_Vector**)luaL_checkudata(L, 2, g_LuaVectorMetaTable);
		x2 = vec->X;
		y2 = vec->Y;
		z2 = vec->Z;
		angle = (float)luaL_optnumber(L, 3, heli->m_rDesiredHeading);
		speed = (int)luaL_optnumber(L, 4, 25.0f);
	}
	else {
		return luaL_error(L, "Bad argument #1 - expected 1 Vector or 3 numbers");
	}

	// interpolation mode, but I want linear mode!!!
	//float lerpT = speed / 500; // 10 = very slow, 100 very fast
	//if (lerpT > 1)
	//	lerpT = 1;

	float x1 = heli->m_v4DesiredPosition.X;
	float y1 = heli->m_v4DesiredPosition.Y;
	float z1 = heli->m_v4DesiredPosition.Z;
	//heli->m_v4DesiredPosition.X = x1 + (x2 - x1) * lerpT;
	//heli->m_v4DesiredPosition.Y = y1 + (y2 - y1) * lerpT;
	//heli->m_v4DesiredPosition.Z = z1 + (z2 - z1) * lerpT;
	//
	//heli->m_v4DesiredVelocity.X = (x2 - x1) * lerpT;
	//heli->m_v4DesiredVelocity.Y = (y2 - z1) * lerpT;
	//heli->m_v4DesiredVelocity.Z = (y2 - z1) * lerpT;

	//heli->m_rDesiredHeading = heli->m_rDesiredHeading + (angle - heli->m_rDesiredHeading) * lerpT;

	Vector4 a = Vector4(x1, y1, z1, 1);
	Vector4 b = Vector4(x2, y2, z2, 1);
	Vector4 delta = Vector4(b.X - a.X, b.Y - a.Y, b.Z - a.Z, 1);
	float deltaSpeed = speed / 100;
	float distance = delta.GetMagnitude();

	delta = Vector4(delta.X / distance, delta.Y / distance, delta.Z / distance, 1);

	Vector4 velocity = Vector4(delta.X * deltaSpeed, delta.Y * deltaSpeed, delta.Z * deltaSpeed, 0);

	heli->m_v4DesiredVelocity = velocity;

	if (distance <= 0.005f)
	{
		heli->m_v4DesiredVelocity = Vector4(0, 0, 0, 0);
		heli->m_v4Position = b;
		heli->m_v4DesiredPosition = b;
		lua_pushboolean(L, true);
	}
	else
	{
		lua_pushboolean(L, false);
		heli->m_v4DesiredPosition = Vector4(heli->m_v4DesiredPosition.X + velocity.X, heli->m_v4DesiredPosition.Y + velocity.Y, heli->m_v4DesiredPosition.Z + velocity.Z);
	}

	float turnSpeed = deltaSpeed / 10;

	heli->m_rDesiredHeading = StepAngle(heli->m_rDesiredHeading, angle, turnSpeed);

	return 1;  // number of return(s)
}

int lua_SetHelicopterDesiredVelocity(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

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
		return luaL_error(L, "bad argument #1 - Expected 1 Vector or 3 numbers");
	}

	Vector4 pos = Vector4(x, y, z, 1);
	heli->m_v4DesiredVelocity = pos;

	return 0;  // number of return(s)
}

// TODO
int lua_GetHelicopterPosition(lua_State* L) 
{ 
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = heli->m_v4Position;
	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s) 
}

int lua_GetHelicopterVelocity(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = heli->m_v4Velocity;
	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s) 
}

int lua_GetHelicopterDesiredPosition(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = heli->m_v4DesiredPosition;
	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s) 
}

int lua_GetHelicopterDesiredVelocity(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = heli->m_v4DesiredVelocity;
	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s) 
}

int lua_GetHelicopterForwardVector(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 fwd = Vector4();
	Matrix mt = Matrix();
	heli->GetMatrix(&mt);

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

int lua_GetHelicopterRightVector(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 fwd = Vector4();
	Matrix mt = Matrix();
	heli->GetMatrix(&mt);

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

int lua_SetHelicopterDesiredHeading(lua_State* L) 
{ 
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	double heading = luaL_checknumber(L, 2);

	heli->m_rDesiredHeading = (float)heading;

	return 0;
}

int lua_GetHelicopterDesiredHeading(lua_State* L) 
{ 
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	double heading = (double)heli->m_rDesiredHeading;
	lua_pushnumber(L, heading);

	return 1;
}

int lua_CreateHelicopter(lua_State* L)
{
	int nargs = lua_gettop(L);

	float x, y, z = 0;
	float vx, vy, vz = 0;
	float angle = 0;
	bool isGoonHeli = true;
	bool isLanded = false;
	bool helicopterOnlySpline = false;
	bool destroyable = false;

	x = (float)luaL_checknumber(L, 1);
	y = (float)luaL_checknumber(L, 2);
	z = (float)luaL_checknumber(L, 3);

	vx = (float)luaL_optnumber(L, 4, 0.0);
	vy = (float)luaL_optnumber(L, 5, 0.0);
	vz = (float)luaL_optnumber(L, 6, 0.0);

	angle = (float)luaL_optnumber(L, 7, 0.0);
	if (nargs > 7)
		isGoonHeli = lua_toboolean(L, 8);
	if (nargs > 8)
		destroyable = lua_toboolean(L, 9);
	if (nargs > 9)
		isLanded = lua_toboolean(L, 10);
	if (nargs > 10)
		helicopterOnlySpline = lua_toboolean(L, 11);

	Vector4 pos = Vector4(x, y, z, 1);
	Vector4 vel = Vector4(vx, vy, vz, 0);

	AIHelicopterClass* heli = CreateHelicopter(pos, vel, angle, isGoonHeli, helicopterOnlySpline, isLanded, destroyable);

	AIHelicopterClass** udata = (AIHelicopterClass**)lua_newuserdata(L, sizeof(void*));
	*udata = heli;

	luaL_getmetatable(L, g_HelicopterMetaName); // return metatable type
	lua_setmetatable(L, -2); // return/set the return

	return 1;
}

// TODO
int lua_DestroyHelicopter(lua_State* L)
{
	return 0;
}

int lua_UpdateHelicopterMotion(lua_State* L)
{
	AIHelicopterClass* heli = *(AIHelicopterClass**)luaL_checkudata(L, 1, g_HelicopterMetaName);

	heli->UpdateHelicopterMotion();

	return 0;
}