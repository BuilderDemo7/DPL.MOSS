#include "Lua_MissionFuncs.h"
#include "Lua_Character.h"
#include "Lua_Vehicle.h"
#include "Lua_CharacterActor.h"

#include "..\dpl\AIFelonySystemFelonyManager.h"
#include "..\dpl\CLifeSystemCommentLog.h"
#include "..\dpl\CLifeSystem.h"
#include "..\dpl\CCharacterManager.h"
#include "..\dpl\CCharacterCategoryManager.h"
#include "..\dpl\CLifeEventDataManager.h"
#include "..\dpl\GameOverlayManager.h"
#include "..\dpl\AmbientSoundManager.h"
#include "..\dpl\ProfileSettings.h"
#include "..\dpl\GameCamera.h"
#include "..\dpl\Speed.h"
#include "..\dpl\InputManager.h"
#include "..\dpl\CLifeActor_Character.h"
#include "..\dpl\CFontManager.h"
#include "..\dpl\Factory.h"
#include "..\dpl\MathFuncs.h"
#include "..\dpl\CPlaylist.h"
#include "..\dpl\LifeEnvironment.h"
#include "..\dpl\AIManager.h"

#include <iostream>

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

int lua_SetVehicleDensity(lua_State* L)
{
	float density = luaL_checknumber(L, 1);
	int vehicleDensityType = luaL_optinteger(L, 2, -1);

	AIManager* aiMan = AIManager::GetInstance();
	if (aiMan != NULL)
	{
		if (vehicleDensityType != -1)
			aiMan->SetVehicleDensity((AIManagerVehicleTypeEnum)vehicleDensityType, density);
		else
		{
			for (int i = 0; i < AIManagerVehicleTypeEnum::NumberOf; i++)
			{
				aiMan->SetVehicleDensity((AIManagerVehicleTypeEnum)i, density);
			}
		}
	}

	return 0;
}

int lua_SetGameDifficulty(lua_State* L)
{
	int diff = luaL_checkinteger(L, 1);

	CProfileSettings* ps = GetProfileSettings();
	if (ps != NULL)
	{
		ps->SetGameDifficulty(diff);
	}

	return 0;
}

int lua_GetGameDifficulty(lua_State* L)
{
	int diff = 0;

	CProfileSettings* ps = GetProfileSettings();
	if (ps != NULL)
	{
		diff = ps->GetGameDifficulty();
	}

	lua_pushinteger(L, diff);
	return 1;
}

int lua_GetPlaylistOrder(lua_State* L)
{
	CPlaylist* musicPlaylist = (CPlaylist*)0x6cfd08;

	lua_newtable(L); // result table
	int count = musicPlaylist->m_TrackCount;

	for (int i = 0; i < count; i++)
	{
		if (musicPlaylist->m_Tracks[i] != TRACK_END)
		{
			if (musicPlaylist->m_Tracks[i] != TRACK_MISSING && musicPlaylist->m_Tracks[i] != TRACK_INVALID)
				lua_pushinteger(L, musicPlaylist->m_Tracks[i]);
			else
				lua_pushnil(L);

			// insert into array
			lua_rawseti(L, -2, i + 1);
		}
	}

	return 1; // return the table
}

int lua_GetPlaylistFileNames(lua_State* L)
{
	CPlaylist* musicPlaylist = (CPlaylist*)0x6cfd08;

	lua_newtable(L); // result table
	int count = musicPlaylist->m_TrackCount;

	for (int i = 0; i < count; i++)
	{
		lua_pushstring(L, musicPlaylist->m_TrackFilenames->m_tracks[i].m_szName);

		// insert into array
		lua_rawseti(L, -2, i + 1);
	}

	return 1; // return the table
}

int lua_GetVehicleInstances(lua_State* L)
{
	CVehicleManager* vman = CVehicleManager::GetInstance();

	if (vman == NULL)
	{
		lua_pushnil(L);
		return 1;
	}

	lua_newtable(L); // result table
	int count = 96;

	for (int i = 0; i < count; i++)
	{
		if (vman->m_piVehicles[i].m_pPointer != NULL)
		{
			CVehicle** udata = (CVehicle**)lua_newuserdata(L, sizeof(void*));
			*udata = vman->m_piVehicles[i].m_pPointer;

			// set metatable
			luaL_getmetatable(L, g_VehicleMetaName);
			lua_setmetatable(L, -2);

			// insert into array
			lua_rawseti(L, -2, i + 1);
		}
	}

	return 1; // return the table
}

int lua_GetCharacterInstances(lua_State* L)
{
	CCharacterManager* cman = CCharacterManager::GetInstance();

	int role = luaL_optinteger(L, 1, -1);

	if (cman == NULL)
	{
		lua_pushnil(L);
		return 1;
	}

	lua_newtable(L); // result table

	SCharacterContainer* container = NULL;
	if (role != -1)
	{
		container = &cman->m_charactersPerRole[role];
		int count = container->m_numCharacters;

		for (int i = 0; i < count; i++)
		{
			if (container->m_characters[i].m_pPointer != NULL)
			{
				CCharacter** udata = (CCharacter**)lua_newuserdata(L, sizeof(void*));
				*udata = container->m_characters[i].m_pPointer;

				// set metatable
				luaL_getmetatable(L, g_CharacterMetaName);
				lua_setmetatable(L, -2);

				// insert into array
				lua_rawseti(L, -2, i + 1);
			}
		}
	}
	else
	{
		for (int roleId = 0; roleId < eCharacterRole_End; roleId++)
		{
			SCharacterContainer* autoContainer = &cman->m_charactersPerRole[roleId];
			int count = autoContainer->m_numCharacters;

			for (int i = 0; i < count; i++)
			{
				if (autoContainer->m_characters[i].m_pPointer != NULL)
				{
					CCharacter** udata = (CCharacter**)lua_newuserdata(L, sizeof(void*));
					*udata = autoContainer->m_characters[i].m_pPointer;

					// set metatable
					luaL_getmetatable(L, g_CharacterMetaName);
					lua_setmetatable(L, -2);

					// insert into array
					lua_rawseti(L, -2, i + 1);
				}
			}
		}
	}

	return 1; // return the table
}

int lua_SetSpoolCentre(lua_State* L)
{
	float x = luaL_checknumber(L, 1);
	float z = luaL_checknumber(L, 2);

	CLifeSystem* lsys = CLifeSystem::GetInstance();
	if (lsys != NULL)
	{
		lsys->SetSpoolCentre(x, z);
	}
	return 0;
}

int lua_ParkVehicle(lua_State* L)
{
	CVehicle* vehicle = *(CVehicle**)luaL_checkudata(L, 1, g_VehicleMetaName);
	if (vehicle != NULL)
	{
		// ParkVehicle__FGQ27hamstert8CAutoPtr2Z8IVehicleZi
		((void(__stdcall*)(CVehicle*))0x460be6)(vehicle);
	}
	return 0;
}

int lua_GetWorldTime(lua_State* L)
{
	float& timeHour = *(float*)((int)GetEnvironment() + 272);
	lua_pushnumber(L, timeHour / 3600.0f);

	return 1;
}

int lua_SetWorldTime(lua_State* L)
{
	float newHour = luaL_checknumber(L, 1);

	float& timeHour = *(float*)((int)GetEnvironment() + 272);
	timeHour = newHour * 3600.0f;

	return 0;
}

int lua_FindClosestVehicleForEntry(lua_State* L)
{
	int nargs = lua_gettop(L); // number of arguments

	CCharacter* character = *(CCharacter**)luaL_checkudata(L, 1, g_CharacterMetaName);

	CVehicle* retStorage = NULL;
	EVehicleDoor eDoor = EVehicleDoor_FrontLeft;

	bool shyOfPassengers = false;
	bool willDrive = true;
	bool checkBack = true;

	if (nargs > 1)
		shyOfPassengers = lua_toboolean(L, 2);
	if (nargs > 2)
		willDrive = lua_toboolean(L, 3);
	if (nargs > 3)
		checkBack = lua_toboolean(L, 4);

	CVehicle** veh = ((CVehicle**(__fastcall*)(CVehicle**, EVehicleDoor*, CCharacter*, bool bShyOfPassengers, bool bWillDrive, bool bCheckBack, bool bCheckOrientation))0x46a16f)(&retStorage, &eDoor, character, shyOfPassengers, willDrive, checkBack, true);

	CVehicle* actualVeh = NULL;
	if (veh != NULL)
		actualVeh = *veh;

	if (!actualVeh)
	{
		lua_pushnil(L);
		lua_pushinteger(L, eDoor);
		return 1;
	}

	// allocate userdata to hold the pointer
	CVehicle** udata = (CVehicle**)lua_newuserdata(L, sizeof(CVehicle*));
	*udata = actualVeh;

	// attach the vehicle metatable
	luaL_getmetatable(L, g_VehicleMetaName);
	lua_setmetatable(L, -2);

	lua_pushinteger(L, eDoor);
	return 2;
}

int lua_DrawText(lua_State* L)
{
	CPCViewport* genVP = CPCViewport::GetSimulationViewport();
	FontSpecs specs = FontSpecs();

	size_t text_size = 0;
	const char* text = luaL_checklstring(L, 1, &text_size);
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	int justifyText = luaL_optinteger(L, 4, 2); // justify centered
	float sx = luaL_optnumber(L, 5, 1.0f);
	float sy = luaL_optnumber(L, 6, 1.0f);

	// color, 0 - 1.0
	float r = luaL_optnumber(L, 7, 1.0f);
	float g = luaL_optnumber(L, 8, 1.0f);
	float b = luaL_optnumber(L, 9, 1.0f);
	float a = luaL_optnumber(L, 10, 1.0f);

	float spacing = luaL_optnumber(L, 11, 1.0f);
	float w = luaL_optnumber(L, 12, 1.0f);

	char* resultText = (char*)text;
	char utf16Conv[512];
	bool isUtf16 = false;

	for (int i = 0; i < text_size; i++)
	{
		if (resultText[i] > 0x7f)
		{
			isUtf16 = true;
		}
	}

	// utf-8 to utf-16
	if (!isUtf16)
	{
		memset((void*)&utf16Conv, 0, sizeof(utf16Conv));
		for (int i = 0; i < text_size; i++)
		{
			utf16Conv[i * sizeof(wchar_t)] = resultText[i];
		}

		// zero-terminated string
		//utf16Conv[(text_size * 2)] = 0x0; 
		//utf16Conv[(text_size * 2) - 1] = 0x0; 
		//utf16Conv[(text_size * 2) + 1] = 0x0; 

		resultText = (char*)&utf16Conv;
	}

	specs.x = x;
	specs.y = y;
	specs.w = w;
	specs.xScale = sx;
	specs.yScale = sy;

	specs.colour.X = r;
	specs.colour.Y = g;
	specs.colour.Z = b;
	specs.colour.W = a;

	specs.justify = (EJustify)justifyText;
	specs.spacing = spacing;

	specs.textType = 0;

	if (genVP != NULL)
	{
		CFontManager* fman = CFontManager::GetInstance();
		if (fman != NULL)
		{
			AutoPtr<CPCViewport, int> aGenVP = AutoPtr<CPCViewport, int>();
			aGenVP.m_pPointer = genVP;

			fman->Print(aGenVP, specs, (wchar_t*)resultText);
		}
	}

	return 0;
}

bool g_bFreeCamOn = false;
void* g_pFreeCamPtr = NULL;

int lua_ToggleFreeCam(lua_State* L)
{
	bool status = lua_toboolean(L, 1);
	int gamepad = luaL_optinteger(L, 2, 0);

	// if already in that status
	if (g_bFreeCamOn == status)
		return 0;

	g_bFreeCamOn = status;
	CLifeSystem* lfs = CLifeSystem::GetInstance();

	if (status)
	{
		Matrix mtx = Matrix();

		mtx.forward = Vector(0, 0, 1);
		mtx.up = Vector(0, 1, 0);
		mtx.right = Vector(1, 0, 0);

		if (lfs)
		{
			CLifePlayer* player = lfs->GetPlayer();
			if (player)
			{
				CCharacter* chara = player->GetDriverBehaviour()->GetCharacter();
				Matrix* pMtx = chara->GetMatrix();

				Vector4 q = Vector4(0, 0, 0, 0);
				mtx = math_initFromQandV3(&q, pMtx->pos);
				//mtx.forward = pMtx->forward;
				//mtx.right = pMtx->right;
				//mtx.up = pMtx->up;
			}
		}

		g_pFreeCamPtr = hamster::CreateObject(EFactoryType_Camera_Free);
		if (g_pFreeCamPtr != NULL)
		{
			// Initialise__12CFixedCameraRC4MAm4fff
			((void(__thiscall*)(void*, Matrix*, int ePadID))0x557beb)(g_pFreeCamPtr, &mtx, gamepad);

			if (GameCamera::GetInstance() != NULL)
			{
				// SetOverrideCamera__10GameCameraGQ27hamstert8CAutoPtr2Z7ICameraZii
				((void(__thiscall*)(GameCamera*, void* piCamera, int blendtime))0x55a6de)(GameCamera::GetInstance(), g_pFreeCamPtr, 0);
			}
		}
		else
		{
			g_bFreeCamOn = false;
		}
	}
	else
	{
		// SetOverrideCamera__10GameCameraGQ27hamstert8CAutoPtr2Z7ICameraZii
		((void(__thiscall*)(GameCamera*, void* piCamera, int blendtime))0x55a6de)(GameCamera::GetInstance(), NULL, 0);
		if (g_pFreeCamPtr != NULL)
		{
			// void operator()<class_IInterface> (void * pPointer)
			void* unknown = g_pFreeCamPtr;
			((void(__thiscall*)(void**, void*))0x4ad031)(&unknown, g_pFreeCamPtr);

			g_pFreeCamPtr = NULL;
		}
	}

	return 0;
}

int lua_ToggleIGCS(lua_State* L)
{
	bool status = lua_toboolean(L, 1);

	CLifeSystem* lfs = CLifeSystem::GetInstance();
	
	if (status)
	{
		if (lfs)
		{
			CLifePlayer* player = lfs->GetPlayer();
			player->m_bEnabled = false;

			// disable HUD
			void* Singleton_GameOverlayManager = *(void**)0x70c71c;

			// EnableOverlays__19CGameOverlayManagerb
			((void(__thiscall*)(void*, bool))0x4b754a)(Singleton_GameOverlayManager, false);
			// EnableOverheadMap__19CGameOverlayManagerb
			((void(__thiscall*)(void*, bool))0x4b76d7)(Singleton_GameOverlayManager, false);

			// disable Chara. sounds
			void* Singleton_CharacterSoundManager = *(void**)0x70c69c;

			((void(__thiscall*)(void*, bool))0x4e0f5a)(Singleton_CharacterSoundManager, false);

			// clear fragments
			void* Singleton_FragmentManager = *(void**)0x70c680;

			// RemoveFragments__15FragmentManagerQ28fragment5EType
			((void(__thiscall*)(void*, int))0x536cbc)(Singleton_FragmentManager, 6);
			((void(__thiscall*)(void*, int))0x536cbc)(Singleton_FragmentManager, 4);
			((void(__thiscall*)(void*, int))0x536cbc)(Singleton_FragmentManager, 0);
			((void(__thiscall*)(void*, int))0x536cbc)(Singleton_FragmentManager, 1);
			((void(__thiscall*)(void*, int))0x536cbc)(Singleton_FragmentManager, 2);
			((void(__thiscall*)(void*, int))0x536cbc)(Singleton_FragmentManager, 3);

			CCharacter* chara = player->GetDriverBehaviour()->GetCharacter();
			CVehicle* vehi = chara->GetVehicle();
			if (vehi)
			{
				// activate handbrake
				SVehicleManipulationPacket packet = SVehicleManipulationPacket();
				packet.bHandbrake = true;

				vehi->SendManipulationPacket(&packet);
			}
		}
	}
	else
	{
		if (lfs)
		{
			CLifePlayer* player = lfs->GetPlayer();
			player->m_bEnabled = true;

			// re-enable HUD
			void* Singleton_GameOverlayManager = *(void**)0x70c71c;

			// EnableOverlays__19CGameOverlayManagerb
			((void(__thiscall*)(void*, bool))0x4b754a)(Singleton_GameOverlayManager, true);
			// EnableOverheadMap__19CGameOverlayManagerb
			((void(__thiscall*)(void*, bool))0x4b76d7)(Singleton_GameOverlayManager, true);

			// re-enable Chara. sounds
			void* Singleton_CharacterSoundManager = *(void**)0x70c69c;

			((void(__thiscall*)(void*, bool))0x4e0f5a)(Singleton_CharacterSoundManager, true);
		}
	}

	return 0;
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

int lua_GetPlayerActor(lua_State* L)
{
	CLifeActor_Character* character = NULL;

	CLifeSystem* lsys = CLifeSystem::GetInstance();

	if (lsys != NULL)
	{
		character = (CLifeActor_Character*)lsys->m_pPlayerActor;
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
	CLifeActor_Character** udata =
		(CLifeActor_Character**)lua_newuserdata(L, sizeof(CLifeActor_Character*));

	*udata = character;

	luaL_getmetatable(L, g_CharacterActorMetaName);
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

int lua_GetCameraPosition(lua_State* L)
{
	GameCamera* cam = GameCamera::GetInstance();

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = Vector4(cam->m_Matrix.pos.X, cam->m_Matrix.pos.Y, cam->m_Matrix.pos.Z, 1.0f);

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}

int lua_GetCameraForwardVector(lua_State* L)
{
	GameCamera* cam = GameCamera::GetInstance();

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = Vector4(cam->m_Matrix.forward.X, cam->m_Matrix.forward.Y, cam->m_Matrix.forward.Z, 1.0f);

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}


int lua_GetCameraRightVector(lua_State* L)
{
	GameCamera* cam = GameCamera::GetInstance();

	// Allocate Lua-managed memory for the struct directly
	void** udata = (void**)lua_newuserdata(L, sizeof(void*));
	*udata = new Lua_Vector();

	Lua_Vector* vecRes = *(Lua_Vector**)udata;

	Vector4 pos = Vector4(cam->m_Matrix.right.X, cam->m_Matrix.right.Y, cam->m_Matrix.right.Z, 1.0f);

	vecRes->X = pos.X;
	vecRes->Y = pos.Y;
	vecRes->Z = pos.Z;

	luaL_getmetatable(L, g_LuaVectorMetaTable);
	lua_setmetatable(L, -2);

	return 1; // number of return(s)
}
