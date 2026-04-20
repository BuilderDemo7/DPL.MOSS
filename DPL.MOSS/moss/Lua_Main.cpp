#include "Lua_Main.h"

#include <windows.h>
#include <iostream>
#include <string>

// metatables
#include "Lua_LifeActor.h"
#include "Lua_Character.h"
#include "Lua_CharacterInstance.h"
#include "Lua_CharacterActor.h"
#include "Lua_Vehicle.h"
#include "Lua_VehicleInstance.h"
#include "Lua_VehicleActor.h"
#include "Lua_Helicopter.h"
#include "Lua_MapItem.h"
#include "Lua_ObjectiveIcon.h"
#include "Lua_Prop.h"
#include "Lua_CameraSelect.h"
#include "Lua_PointActor.h"
#include "Lua_TestVolume.h"
#include "Lua_Camera.h"

// funcs
#include "Lua_MissionFuncs.h"
#include "Lua_ResourceManager.h"
#include "Lua_Hooking.h"

#include "..\Hooks.h"

bool g_bLuaScriptsLoaded = false;
bool g_bLuaScriptsStarted = false;

std::vector<int> g_LuaSteps;	          // step()
std::vector<int> g_LuaPostSteps;          // post_step()
std::vector<int> g_LuaStarts;	          // start()
std::vector<int> g_LuaShutdowns;	      // shutdown()
std::vector<int> g_LuaDrawMissionEvents;  // draw_mission()
std::vector<int> g_LuaDrawTargetManEvents;// draw_targets()

lua_State* L = NULL;

void Init_LuaMisc()
{
	g_bFreeCamOn = false;
	g_pFreeCamPtr = NULL;
}

void Init_LuaScripts()
{
#ifdef _DEBUG
	printf("Init_LuaScripts()\n");
#endif

	L = luaL_newstate();
	luaL_openlibs(L);

	Init_Lua_MetaTables();
	Init_Lua_Constants();
	Init_Lua_Funcs();

	// Load all the files in the folder
	std::string folderPath = LUA_SCRIPTS_FOLDER;
	std::string searchPath = folderPath + "\\*";

	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

	std::cout << "Loading MOSS Lua scripts..." << std::endl;
	if (hFind == INVALID_HANDLE_VALUE)
	{
		std::cout << "Scripts folder not found.\n";
		return;
	}

	int scriptsLoaded = 0;
	int scriptsErrored = 0;
	char fn[348];

	g_SimulationFirstStepTicked = false;
	g_bLuaScriptsLoaded = false;
	g_bSimulationInitalised = false;
	g_bLuaScriptsStarted = false;

	do
	{
		std::string name = findData.cFileName;

		// Skip "." and ".."
		if (name != "." && name != "..")
		{
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				sprintf(fn, "%s\\%s", folderPath.c_str(), name.c_str());

				printf("Loading script %s ...\n", name.c_str());
				int scriptstatus = luaL_dofile(L, fn);

				if (scriptstatus == LUA_OK)
				{
					// check if step() exists
					lua_getglobal(L, "step");

					if (lua_isfunction(L, -1))
					{
						// store reference
						int ref = luaL_ref(L, LUA_REGISTRYINDEX);
						g_LuaSteps.push_back(ref);
					}
					else
					{
						lua_pop(L, 1);
					}

					// check if post_step() exists
					lua_getglobal(L, "post_step");

					if (lua_isfunction(L, -1))
					{
						// store reference
						int ref = luaL_ref(L, LUA_REGISTRYINDEX);
						g_LuaPostSteps.push_back(ref);
					}
					else
					{
						lua_pop(L, 1);
					}

					// check if start() exists
					lua_getglobal(L, "start");

					if (lua_isfunction(L, -1))
					{
						// store reference
						int ref = luaL_ref(L, LUA_REGISTRYINDEX);
						g_LuaStarts.push_back(ref);
					}
					else
					{
						lua_pop(L, 1);
					}

					// check if shutdown() exists
					lua_getglobal(L, "shutdown");

					if (lua_isfunction(L, -1))
					{
						// store reference
						int ref = luaL_ref(L, LUA_REGISTRYINDEX);
						g_LuaShutdowns.push_back(ref);
					}
					else
					{
						lua_pop(L, 1);
					}

					// check if draw_mission() exists
					lua_getglobal(L, "draw_mission");

					if (lua_isfunction(L, -1))
					{
						// store reference
						int ref = luaL_ref(L, LUA_REGISTRYINDEX);
						g_LuaDrawMissionEvents.push_back(ref);
					}
					else
					{
						lua_pop(L, 1);
					}

					// check if draw_targets() exists
					lua_getglobal(L, "draw_targets");

					if (lua_isfunction(L, -1))
					{
						// store reference
						int ref = luaL_ref(L, LUA_REGISTRYINDEX);
						g_LuaDrawTargetManEvents.push_back(ref);
					}
					else
					{
						lua_pop(L, 1);
					}

					// clear global funcs so next script doesn't overwrite
					lua_pushnil(L);
					lua_setglobal(L, "step");
					lua_pushnil(L);
					lua_setglobal(L, "post_step");
					lua_pushnil(L);
					lua_setglobal(L, "start");
					lua_pushnil(L);
					lua_setglobal(L, "shutdown");
					lua_pushnil(L);
					lua_setglobal(L, "draw_mission");
					lua_pushnil(L);
					lua_setglobal(L, "draw_targets");

					scriptsLoaded++;
				}
				else
				{
					printf("Error in loading script %s:\n %s\n", name.c_str(), lua_tostring(L, -1));

					lua_pop(L, 1);

					scriptsErrored++;
				}
			}
		}

	} while (FindNextFileA(hFind, &findData));

	FindClose(hFind);

	g_bLuaScriptsLoaded = true;

	printf("%d scripts were loaded with success in 'moss_scripts' folder, %d with errors.\n", scriptsLoaded, scriptsErrored);

	Init_LuaMisc();
}

void Lua_Start()
{
#ifdef _DEBUG
	printf("Lua_Start()\n");
#endif

	g_bLuaScriptsStarted = true;

	for (size_t i = 0; i < g_LuaStarts.size(); i++)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, g_LuaStarts[i]);

		if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		{
			printf("Lua error: %s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}
}

void OnDrawTargetManager_Lua()
{
	for (size_t i = 0; i < g_LuaDrawTargetManEvents.size(); i++)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, g_LuaDrawTargetManEvents[i]);

		if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		{
			printf("Lua error: %s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}
}

void OnDrawMission_Lua()
{
	for (size_t i = 0; i < g_LuaDrawMissionEvents.size(); i++)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, g_LuaDrawMissionEvents[i]);

		if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		{
			printf("Lua error: %s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}
}

void PostStep_Lua()
{
	for (size_t i = 0; i < g_LuaPostSteps.size(); i++)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, g_LuaPostSteps[i]);

		if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		{
			printf("Lua error: %s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}
}

// brought to you by hooking step__Q22AI4Gamev
void Step_Lua()
{
	/*
	if (g_SimulationFirstStepTicked == false)
	{
		g_SimulationFirstStepTicked = true;

		for (size_t i = 0; i < g_LuaStarts.size(); i++)
		{
			lua_rawgeti(L, LUA_REGISTRYINDEX, g_LuaStarts[i]);

			if (lua_pcall(L, 0, 0, 0) != LUA_OK)
			{
				printf("Lua error: %s\n", lua_tostring(L, -1));
				lua_pop(L, 1);
			}
		}
	}
	*/

	for (size_t i = 0; i < g_LuaSteps.size(); i++)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, g_LuaSteps[i]);

		if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		{
			printf("Lua error: %s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}

}

void Close_Lua()
{
	if (L != NULL)
		lua_close(L);
}

void Reload_Lua()
{
#ifdef _DEBUG
	printf("Reload_Lua()\n");
#endif

	g_SimulationFirstStepTicked = false;
	g_bLuaScriptsLoaded = false;
	g_bSimulationInitalised = false;
	g_bLuaScriptsStarted = false;

	for (size_t i = 0; i < g_LuaShutdowns.size(); i++)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, g_LuaShutdowns[i]);

		if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		{
			printf("Lua error: %s\n", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}

	g_LuaShutdowns.clear();
	g_LuaStarts.clear();
	g_LuaSteps.clear();
	g_LuaPostSteps.clear();
	g_LuaDrawMissionEvents.clear();
	g_LuaDrawTargetManEvents.clear();

	Close_Lua();
}

void Init_Lua_Constants()
{
	lua_pushinteger(L, 0);
	lua_setglobal(L, "Era_Then");
	lua_pushinteger(L, 1);
	lua_setglobal(L, "Era_Now");

	// AIFelonySystemPatrolCarTypeEnum
	lua_pushinteger(L, 0);
	lua_setglobal(L, "E_PATROLCARTYPE_COP");
	lua_pushinteger(L, 1);
	lua_setglobal(L, "E_PATROLCARTYPE_GOON");
	lua_pushinteger(L, 2);
	lua_setglobal(L, "E_PATROLCARTYPE_NUM_OF");
	lua_pushinteger(L, 3);
	lua_setglobal(L, "E_PATROLCARTYPE_NONE");

	// enum - EMapIcon
	lua_pushinteger(L, EMapIcon_Default);
	lua_setglobal(L, "EMapIcon_Default");
	lua_pushinteger(L, EMapIcon_CircuitRace);
	lua_setglobal(L, "EMapIcon_CircuitRace");
	lua_pushinteger(L, EMapIcon_Repoman);
	lua_setglobal(L, "EMapIcon_Repoman");
	lua_pushinteger(L, EMapIcon_SafeHouse);
	lua_setglobal(L, "EMapIcon_SafeHouse");
	lua_pushinteger(L, EMapIcon_StreetRace);
	lua_setglobal(L, "EMapIcon_StreetRace");
	lua_pushinteger(L, EMapIcon_TimeTravel);
	lua_setglobal(L, "EMapIcon_TimeTravel");
	lua_pushinteger(L, EMapIcon_Vedit);
	lua_setglobal(L, "EMapIcon_Vedit");
	lua_pushinteger(L, EMapIcon_78_LoanShark);
	lua_setglobal(L, "EMapIcon_78_LoanShark");
	lua_pushinteger(L, EMapIcon_06_Hitman);
	lua_setglobal(L, "EMapIcon_06_Hitman");

	// enum - EMapItem
	lua_pushinteger(L, EMapItem_Uninitialised);
	lua_setglobal(L, "EMapItem_Uninitialised");
	lua_pushinteger(L, EMapItem_Camera);
	lua_setglobal(L, "EMapItem_Camera");
	lua_pushinteger(L, EMapItem_Player);
	lua_setglobal(L, "EMapItem_Player");
	lua_pushinteger(L, EMapItem_Vehicle);
	lua_setglobal(L, "EMapItem_Vehicle");
	lua_pushinteger(L, EMapItem_Character);
	lua_setglobal(L, "EMapItem_Character");
	lua_pushinteger(L, EMapItem_CopCar);
	lua_setglobal(L, "EMapItem_CopCar");
	lua_pushinteger(L, EMapItem_GoonCar);
	lua_setglobal(L, "EMapItem_GoonCar");
	lua_pushinteger(L, EMapItem_Target);
	lua_setglobal(L, "EMapItem_Target");
	lua_pushinteger(L, EMapItem_PlotMission);
	lua_setglobal(L, "EMapItem_PlotMission");
	lua_pushinteger(L, EMapItem_MiniMission);
	lua_setglobal(L, "EMapItem_MiniMission");
	lua_pushinteger(L, EMapItem_SafeHouse);
	lua_setglobal(L, "EMapItem_SafeHouse");
	lua_pushinteger(L, EMapItem_VEditGarage);
	lua_setglobal(L, "EMapItem_VEditGarage");
	lua_pushinteger(L, EMapItem_Network_Portal);
	lua_setglobal(L, "EMapItem_Network_Portal");
	lua_pushinteger(L, EMapItem_Network_Player);
	lua_setglobal(L, "EMapItem_Network_Player");
	lua_pushinteger(L, EMapItem_Positional_Marker);
	lua_setglobal(L, "EMapItem_Positional_Marker");
	lua_pushinteger(L, EMapItem_COUNT);
	lua_setglobal(L, "EMapItem_COUNT");

	// enum - key code
	lua_pushinteger(L, VK_UP);
	lua_setglobal(L, "VK_UP");
	lua_pushinteger(L, VK_DOWN);
	lua_setglobal(L, "VK_DOWN");
	lua_pushinteger(L, VK_RIGHT);
	lua_setglobal(L, "VK_RIGHT");
	lua_pushinteger(L, VK_LEFT);
	lua_setglobal(L, "VK_LEFT");
	
	lua_pushinteger(L, VK_PRIOR); // page up
	lua_setglobal(L, "VK_PRIOR");
	lua_pushinteger(L, VK_NEXT); // page down
	lua_setglobal(L, "VK_NEXT");

	lua_pushinteger(L, VK_END); 
	lua_setglobal(L, "VK_END");
	lua_pushinteger(L, VK_HOME);
	lua_setglobal(L, "VK_HOME");

	lua_pushinteger(L, VK_INSERT);
	lua_setglobal(L, "VK_INSERT");

	// EGadgetType
	lua_pushinteger(L, EGadgetType::_11DRUGBOX); lua_setglobal(L, "_11DRUGBOX");
	lua_pushinteger(L, EGadgetType::_2BOX); lua_setglobal(L, "_2BOX");
	lua_pushinteger(L, EGadgetType::_1BOMB); lua_setglobal(L, "_1BOMB");
	lua_pushinteger(L, EGadgetType::_1BOMBNOW); lua_setglobal(L, "_1BOMBNOW");
	lua_pushinteger(L, EGadgetType::_2BRIEFCASE); lua_setglobal(L, "_2BRIEFCASE");
	lua_pushinteger(L, EGadgetType::AR10); lua_setglobal(L, "AR10");
	lua_pushinteger(L, EGadgetType::ARMOUREDCAR); lua_setglobal(L, "ARMOUREDCAR");
	lua_pushinteger(L, EGadgetType::BERETTA); lua_setglobal(L, "BERETTA");
	lua_pushinteger(L, EGadgetType::BINBIGBLUE); lua_setglobal(L, "BINBIGBLUE");
	lua_pushinteger(L, EGadgetType::BULLPUP); lua_setglobal(L, "BULLPUP");
	lua_pushinteger(L, EGadgetType::CHEVRON36MSTRAIGHT); lua_setglobal(L, "CHEVRON36MSTRAIGHT");
	lua_pushinteger(L, EGadgetType::CIRCUITRACE); lua_setglobal(L, "CIRCUITRACE");
	lua_pushinteger(L, EGadgetType::CONECONED); lua_setglobal(L, "CONECONED");
	lua_pushinteger(L, EGadgetType::DESERTEAGLE); lua_setglobal(L, "DESERTEAGLE");
	lua_pushinteger(L, EGadgetType::DESTRUCTIONDERBY); lua_setglobal(L, "DESTRUCTIONDERBY");
	lua_pushinteger(L, EGadgetType::DRIVERGP); lua_setglobal(L, "DRIVERGP");
	lua_pushinteger(L, EGadgetType::FENCELARGEPLYWOOD4M); lua_setglobal(L, "FENCELARGEPLYWOOD4M");
	lua_pushinteger(L, EGadgetType::GLOCK18); lua_setglobal(L, "GLOCK18");
	lua_pushinteger(L, EGadgetType::GRENADE); lua_setglobal(L, "GRENADE");
	lua_pushinteger(L, EGadgetType::GRENADELAUNCHER); lua_setglobal(L, "GRENADELAUNCHER");
	lua_pushinteger(L, EGadgetType::HealthPack_Now); lua_setglobal(L, "HealthPack_Now");
	lua_pushinteger(L, EGadgetType::HEALTHPACK_Then); lua_setglobal(L, "HEALTHPACK_Then");
	lua_pushinteger(L, EGadgetType::HELICOPTER_NOW); lua_setglobal(L, "HELICOPTER_NOW");
	lua_pushinteger(L, EGadgetType::HELICOPTER_THEN); lua_setglobal(L, "HELICOPTER_THEN");
	lua_pushinteger(L, EGadgetType::HELICOPTERBLACK); lua_setglobal(L, "HELICOPTERBLACK");
	lua_pushinteger(L, EGadgetType::HELICOPTERCIV); lua_setglobal(L, "HELICOPTERCIV");
	lua_pushinteger(L, EGadgetType::HITMAN); lua_setglobal(L, "HITMAN");
	lua_pushinteger(L, EGadgetType::LOANSHARK); lua_setglobal(L, "LOANSHARK");
	lua_pushinteger(L, EGadgetType::MACHINEGUNMUZZLEFLASH); lua_setglobal(L, "MACHINEGUNMUZZLEFLASH");
	lua_pushinteger(L, EGadgetType::MAGNUM); lua_setglobal(L, "MAGNUM");
	lua_pushinteger(L, EGadgetType::MainRotor); lua_setglobal(L, "MainRotor");
	lua_pushinteger(L, EGadgetType::MINIGUN); lua_setglobal(L, "MINIGUN");
	lua_pushinteger(L, EGadgetType::MOTOCROSS); lua_setglobal(L, "MOTOCROSS");
	lua_pushinteger(L, EGadgetType::MP7); lua_setglobal(L, "MP7");
	lua_pushinteger(L, EGadgetType::NITROFLASH); lua_setglobal(L, "NITROFLASH");
	lua_pushinteger(L, EGadgetType::P90); lua_setglobal(L, "P90");
	lua_pushinteger(L, EGadgetType::PERFECTDELIVERY); lua_setglobal(L, "PERFECTDELIVERY");
	lua_pushinteger(L, EGadgetType::PISTOLMUZZLEFLASH); lua_setglobal(L, "PISTOLMUZZLEFLASH");
	lua_pushinteger(L, EGadgetType::POSITIONMARKERCONE); lua_setglobal(L, "POSITIONMARKERCONE");
	lua_pushinteger(L, EGadgetType::POSITIONMARKERFLARE); lua_setglobal(L, "POSITIONMARKERFLARE");
	lua_pushinteger(L, EGadgetType::POSITIONMARKERSHORTFAT); lua_setglobal(L, "POSITIONMARKERSHORTFAT");
	lua_pushinteger(L, EGadgetType::POSITIONMARKERSHORTSKINNY); lua_setglobal(L, "POSITIONMARKERSHORTSKINNY");
	lua_pushinteger(L, EGadgetType::POSITIONMARKERTALLFAT); lua_setglobal(L, "POSITIONMARKERTALLFAT");
	lua_pushinteger(L, EGadgetType::POSITIONMARKERTALLSKINNY); lua_setglobal(L, "POSITIONMARKERTALLSKINNY");
	lua_pushinteger(L, EGadgetType::PRISONTRANSPORT); lua_setglobal(L, "PRISONTRANSPORT");
	lua_pushinteger(L, EGadgetType::RAMP); lua_setglobal(L, "RAMP");
	lua_pushinteger(L, EGadgetType::REPOMAN); lua_setglobal(L, "REPOMAN");
	lua_pushinteger(L, EGadgetType::REVOLVER); lua_setglobal(L, "REVOLVER");
	lua_pushinteger(L, EGadgetType::ROADWORKBARRIER4M); lua_setglobal(L, "ROADWORKBARRIER4M");
	lua_pushinteger(L, EGadgetType::ROADWORKSMALLBARRIER); lua_setglobal(L, "ROADWORKSMALLBARRIER");
	lua_pushinteger(L, EGadgetType::ROCKET); lua_setglobal(L, "ROCKET");
	lua_pushinteger(L, EGadgetType::ROCKETLAUNCHER); lua_setglobal(L, "ROCKETLAUNCHER");
	lua_pushinteger(L, EGadgetType::SAFEHOUSE); lua_setglobal(L, "SAFEHOUSE");
	lua_pushinteger(L, EGadgetType::SHOTGUN); lua_setglobal(L, "SHOTGUN");
	lua_pushinteger(L, EGadgetType::SLINKSPACKAGE2); lua_setglobal(L, "SLINKSPACKAGE2");
	lua_pushinteger(L, EGadgetType::SPEEDGUN); lua_setglobal(L, "SPEEDGUN");
	lua_pushinteger(L, EGadgetType::STICKUP); lua_setglobal(L, "STICKUP");
	lua_pushinteger(L, EGadgetType::STREETRACE); lua_setglobal(L, "STREETRACE");
	lua_pushinteger(L, EGadgetType::STYER); lua_setglobal(L, "STYER");
	lua_pushinteger(L, EGadgetType::SURVIVAL); lua_setglobal(L, "SURVIVAL");
	lua_pushinteger(L, EGadgetType::TailRotor); lua_setglobal(L, "TailRotor");
	lua_pushinteger(L, EGadgetType::TAXI); lua_setglobal(L, "TAXI");
	lua_pushinteger(L, EGadgetType::Token); lua_setglobal(L, "Token");
	lua_pushinteger(L, EGadgetType::TRAIN); lua_setglobal(L, "TRAIN");
	lua_pushinteger(L, EGadgetType::UZI); lua_setglobal(L, "UZI");
	lua_pushinteger(L, EGadgetType::UZIMUZZLEFLASH); lua_setglobal(L, "UZIMUZZLEFLASH");
	lua_pushinteger(L, EGadgetType::VEDIT); lua_setglobal(L, "VEDIT");
	lua_pushinteger(L, EGadgetType::VENDERDONUTS); lua_setglobal(L, "VENDERDONUTS");
	lua_pushinteger(L, EGadgetType::VENDERFOOD); lua_setglobal(L, "VENDERFOOD");

	// SpooledPackageType
	lua_pushinteger(L, SpooledPackageType::SpooledPackageType_Vehicles); lua_setglobal(L, "SpooledPackageType_Vehicles");
	lua_pushinteger(L, SpooledPackageType::SpooledPackageType_Missions); lua_setglobal(L, "SpooledPackageType_Missions");
	lua_pushinteger(L, SpooledPackageType::SpooledPackageType_CharacterSkins); lua_setglobal(L, "SpooledPackageType_CharacterSkins");
	lua_pushinteger(L, SpooledPackageType::SpooledPackageType_CharacterAnimations); lua_setglobal(L, "SpooledPackageType_CharacterAnimations");
	lua_pushinteger(L, SpooledPackageType::SpooledPackageType_Audio); lua_setglobal(L, "SpooledPackageType_Audio");
	lua_pushinteger(L, SpooledPackageType::SpooledPackageType_Localisation); lua_setglobal(L, "SpooledPackageType_Localisation");
	lua_pushinteger(L, SpooledPackageType::SpooledPackageType_Subtitles); lua_setglobal(L, "SpooledPackageType_Subtitles");
	lua_pushinteger(L, SpooledPackageType::SpooledPackageType_numSpooledPackageTypes); lua_setglobal(L, "SpooledPackageType_numSpooledPackageTypes");
	lua_pushinteger(L, SpooledPackageType::SpooledPackageType_Uninitialised); lua_setglobal(L, "SpooledPackageType_Uninitialised");
	
	lua_pushinteger(L, ESpoolPriority::ESpoolPriority_Uninitialised); lua_setglobal(L, "ESpoolPriority_Uninitialised");
	lua_pushinteger(L, ESpoolPriority::ESpoolPriority_Required); lua_setglobal(L, "ESpoolPriority_Required");
	lua_pushinteger(L, ESpoolPriority::ESpoolPriority_Preferred); lua_setglobal(L, "ESpoolPriority_Preferred");

	// ECameraSelectType
	lua_pushinteger(L, ECameraSelectType::ECameraSelectType_UNDEFINED); lua_setglobal(L, "ECameraSelectType_UNDEFINED");
	lua_pushinteger(L, ECameraSelectType::ECameraSelectType_CameraActor); lua_setglobal(L, "ECameraSelectType_CameraActor");
	lua_pushinteger(L, ECameraSelectType::ECameraSelectType_VehicleCam); lua_setglobal(L, "ECameraSelectType_VehicleCam");
	lua_pushinteger(L, ECameraSelectType::ECameraSelectType_ThrillCam); lua_setglobal(L, "ECameraSelectType_ThrillCam");
	lua_pushinteger(L, ECameraSelectType::ECameraSelectType_IGCSOff); lua_setglobal(L, "ECameraSelectType_IGCSOff");
	lua_pushinteger(L, ECameraSelectType::ECameraSelectType_FPSCamera); lua_setglobal(L, "ECameraSelectType_FPSCamera");

	// ECameraSelect_VehicleCamType
	lua_pushinteger(L, ECameraSelect_VehicleCamType::ECameraSelect_VehicleCamType_Bonnet); lua_setglobal(L, "ECameraSelect_VehicleCamType_Bonnet");
	lua_pushinteger(L, ECameraSelect_VehicleCamType::ECameraSelect_VehicleCamType_Boot); lua_setglobal(L, "ECameraSelect_VehicleCamType_Boot");
	lua_pushinteger(L, ECameraSelect_VehicleCamType::ECameraSelect_VehicleCamType_Chase); lua_setglobal(L, "ECameraSelect_VehicleCamType_Chase");
	lua_pushinteger(L, ECameraSelect_VehicleCamType::ECameraSelect_VehicleCamType_Driver); lua_setglobal(L, "ECameraSelect_VehicleCamType_Driver");
	lua_pushinteger(L, ECameraSelect_VehicleCamType::ECameraSelect_VehicleCamType_Bumper); lua_setglobal(L, "ECameraSelect_VehicleCamType_Bumper");
	lua_pushinteger(L, ECameraSelect_VehicleCamType::ECameraSelect_VehicleCamType_First); lua_setglobal(L, "ECameraSelect_VehicleCamType_First");
	lua_pushinteger(L, ECameraSelect_VehicleCamType::ECameraSelect_VehicleCamType_LWheel); lua_setglobal(L, "ECameraSelect_VehicleCamType_LWheel");
	lua_pushinteger(L, ECameraSelect_VehicleCamType::ECameraSelect_VehicleCamType_RWheel); lua_setglobal(L, "ECameraSelect_VehicleCamType_RWheel");

	// ObjectiveIconDisplayType
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_VEDIT); lua_setglobal(L, "DisplayType_VEDIT");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_POSITIONMARKERTALLFAT); lua_setglobal(L, "DisplayType_POSITIONMARKERTALLFAT");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_ARMOUREDCAR); lua_setglobal(L, "DisplayType_ARMOUREDCAR");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_CIRCUITRACE); lua_setglobal(L, "DisplayType_CIRCUITRACE");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_HITMAN); lua_setglobal(L, "DisplayType_HITMAN");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_MOTOCROSS); lua_setglobal(L, "DisplayType_MOTOCROSS");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_PERFECTDELIVERY); lua_setglobal(L, "DisplayType_PERFECTDELIVERY");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_REPOMAN); lua_setglobal(L, "DisplayType_REPOMAN");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_SAFEHOUSE); lua_setglobal(L, "DisplayType_SAFEHOUSE");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_STICKUP); lua_setglobal(L, "DisplayType_STICKUP");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_STREETRACE); lua_setglobal(L, "DisplayType_STREETRACE");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_TAXI); lua_setglobal(L, "DisplayType_TAXI");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_LOANSHARK); lua_setglobal(L, "DisplayType_LOANSHARK");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_POSITIONMARKERTALLSKINNY); lua_setglobal(L, "DisplayType_POSITIONMARKERTALLSKINNY");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_POSITIONMARKERSHORTSKINNY); lua_setglobal(L, "DisplayType_POSITIONMARKERSHORTSKINNY");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_POSITIONMARKERSHORTFAT); lua_setglobal(L, "DisplayType_POSITIONMARKERSHORTFAT");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_POSITIONMARKERCONE); lua_setglobal(L, "DisplayType_POSITIONMARKERCONE");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_PRISONTRANSPORT); lua_setglobal(L, "DisplayType_PRISONTRANSPORT");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_GARAGEPOSITIONMARKERSHORTFAT); lua_setglobal(L, "DisplayType_GARAGEPOSITIONMARKERSHORTFAT");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_GARAGEPOSITIONMARKERSHORTSKINNY); lua_setglobal(L, "DisplayType_GARAGEPOSITIONMARKERSHORTSKINNY");
	lua_pushinteger(L, ObjectiveIconDisplayType::DisplayType_GARAGEPOSITIONMARKERTALLSKINNY); lua_setglobal(L, "DisplayType_GARAGEPOSITIONMARKERTALLSKINNY");

	// ObjectiveIconVisibility
	lua_pushinteger(L, ObjectiveIconVisibility::ObjVisibility_MinimapAndModel); lua_setglobal(L, "ObjVisibility_MinimapAndModel");
	lua_pushinteger(L, ObjectiveIconVisibility::ObjVisibility_MinimapOnly); lua_setglobal(L, "ObjVisibility_MinimapOnly");
	lua_pushinteger(L, ObjectiveIconVisibility::ObjVisibility_ModelOnly); lua_setglobal(L, "ObjVisibility_ModelOnly");

	// EPrimitiveType
	lua_pushinteger(L, EPrimitiveType::InvalidPrimitive); lua_setglobal(L, "EPrimitiveType_Invalid");
	lua_pushinteger(L, EPrimitiveType::Cylinder); lua_setglobal(L, "EPrimitiveType_Cylinder");
	lua_pushinteger(L, EPrimitiveType::Box); lua_setglobal(L, "EPrimitiveType_Box");
	lua_pushinteger(L, EPrimitiveType::Sphere); lua_setglobal(L, "EPrimitiveType_Sphere");
	lua_pushinteger(L, EPrimitiveType::Plane); lua_setglobal(L, "EPrimitiveType_Plane");

	// alphanumerics
	lua_pushinteger(L, '0');
	lua_setglobal(L, "VK_0");
	lua_pushinteger(L, '1');
	lua_setglobal(L, "VK_1");
	lua_pushinteger(L, '2');
	lua_setglobal(L, "VK_2");
	lua_pushinteger(L, '3');
	lua_setglobal(L, "VK_3");
	lua_pushinteger(L, '4');
	lua_setglobal(L, "VK_4");
	lua_pushinteger(L, '5');
	lua_setglobal(L, "VK_5");
	lua_pushinteger(L, '6');
	lua_setglobal(L, "VK_6");
	lua_pushinteger(L, '7');
	lua_setglobal(L, "VK_7");
	lua_pushinteger(L, '8');
	lua_setglobal(L, "VK_8");
	lua_pushinteger(L, '9');
	lua_setglobal(L, "VK_9");

	// alphabet
	lua_pushinteger(L, 'A');
	lua_setglobal(L, "VK_A");
	lua_pushinteger(L, 'B');
	lua_setglobal(L, "VK_B");
	lua_pushinteger(L, 'C');
	lua_setglobal(L, "VK_C");
	lua_pushinteger(L, 'D');
	lua_setglobal(L, "VK_D");
	lua_pushinteger(L, 'E');
	lua_setglobal(L, "VK_E");
	lua_pushinteger(L, 'F');
	lua_setglobal(L, "VK_F");
	lua_pushinteger(L, 'G');
	lua_setglobal(L, "VK_G");
	lua_pushinteger(L, 'H');
	lua_setglobal(L, "VK_H");
	lua_pushinteger(L, 'I');
	lua_setglobal(L, "VK_I");
	lua_pushinteger(L, 'J');
	lua_setglobal(L, "VK_J");
	lua_pushinteger(L, 'K');
	lua_setglobal(L, "VK_K");
	lua_pushinteger(L, 'L');
	lua_setglobal(L, "VK_L");
	lua_pushinteger(L, 'M');
	lua_setglobal(L, "VK_M");
	lua_pushinteger(L, 'N');
	lua_setglobal(L, "VK_N");
	lua_pushinteger(L, 'O');
	lua_setglobal(L, "VK_O");
	lua_pushinteger(L, 'P');
	lua_setglobal(L, "VK_P");
	lua_pushinteger(L, 'Q');
	lua_setglobal(L, "VK_Q");
	lua_pushinteger(L, 'R');
	lua_setglobal(L, "VK_R");
	lua_pushinteger(L, 'S');
	lua_setglobal(L, "VK_S");
	lua_pushinteger(L, 'T');
	lua_setglobal(L, "VK_T");
	lua_pushinteger(L, 'U');
	lua_setglobal(L, "VK_U");
	lua_pushinteger(L, 'V');
	lua_setglobal(L, "VK_V");
	lua_pushinteger(L, 'W');
	lua_setglobal(L, "VK_W");
	lua_pushinteger(L, 'X');
	lua_setglobal(L, "VK_X");
	lua_pushinteger(L, 'Y');
	lua_setglobal(L, "VK_Y");
	lua_pushinteger(L, 'Z');
	lua_setglobal(L, "VK_Z");

	lua_pushinteger(L, VK_CONTROL);
	lua_setglobal(L, "VK_CONTROL");
	lua_pushinteger(L, VK_SHIFT);
	lua_setglobal(L, "VK_SHIFT");
	lua_pushinteger(L, VK_LCONTROL);
	lua_setglobal(L, "VK_LCONTROL");
	lua_pushinteger(L, VK_LSHIFT);
	lua_setglobal(L, "VK_LSHIFT");
	lua_pushinteger(L, VK_RCONTROL);
	lua_setglobal(L, "VK_RCONTROL");
	lua_pushinteger(L, VK_RSHIFT);
	lua_setglobal(L, "VK_RSHIFT");

	lua_pushinteger(L, VK_NUMPAD0);
	lua_setglobal(L, "VK_NUMPAD0");
	lua_pushinteger(L, VK_NUMPAD1);
	lua_setglobal(L, "VK_NUMPAD1");
	lua_pushinteger(L, VK_NUMPAD2);
	lua_setglobal(L, "VK_NUMPAD2");
	lua_pushinteger(L, VK_NUMPAD3);
	lua_setglobal(L, "VK_NUMPAD3");
	lua_pushinteger(L, VK_NUMPAD4);
	lua_setglobal(L, "VK_NUMPAD4");
	lua_pushinteger(L, VK_NUMPAD5);
	lua_setglobal(L, "VK_NUMPAD5");
	lua_pushinteger(L, VK_NUMPAD6);
	lua_setglobal(L, "VK_NUMPAD6");
	lua_pushinteger(L, VK_NUMPAD7);
	lua_setglobal(L, "VK_NUMPAD7");
	lua_pushinteger(L, VK_NUMPAD8);
	lua_setglobal(L, "VK_NUMPAD8");
	lua_pushinteger(L, VK_NUMPAD9);
	lua_setglobal(L, "VK_NUMPAD9");

	lua_pushinteger(L, VK_RETURN);
	lua_setglobal(L, "VK_RETURN");

	lua_pushinteger(L, VK_F1);
	lua_setglobal(L, "VK_F1");
	lua_pushinteger(L, VK_F2);
	lua_setglobal(L, "VK_F2");
	lua_pushinteger(L, VK_F3);
	lua_setglobal(L, "VK_F3");
	lua_pushinteger(L, VK_F4);
	lua_setglobal(L, "VK_F4");
	lua_pushinteger(L, VK_F5);
	lua_setglobal(L, "VK_F5");
	lua_pushinteger(L, VK_F6);
	lua_setglobal(L, "VK_F6");
	lua_pushinteger(L, VK_F7);
	lua_setglobal(L, "VK_F7");
	lua_pushinteger(L, VK_F8);
	lua_setglobal(L, "VK_F8");
	lua_pushinteger(L, VK_F9);
	lua_setglobal(L, "VK_F9");
	lua_pushinteger(L, VK_F10);
	lua_setglobal(L, "VK_F10");
	lua_pushinteger(L, VK_F11);
	lua_setglobal(L, "VK_F11");
	lua_pushinteger(L, VK_F12);
	lua_setglobal(L, "VK_F12");
}

void Init_Lua_Funcs()
{
	// TODO: fill all the necessary functions
	lua_register(L, "GetPlayerCharacter", lua_GetPlayerCharacter); // Character GetPlayerCharacter()
	lua_register(L, "GetPlayerActor", lua_GetPlayerActor); // Character_Actor GetPlayerActor()
	lua_register(L, "ShowMissionComment", lua_ShowMissionComment); // void ShowMissionComment(float duration, string message)
	lua_register(L, "EndAllLifeEvents", lua_EndAllLifeEvents); // void EndAllLifeEvents()

	lua_register(L, "SetGameDifficulty", lua_SetGameDifficulty); // void SetGameDifficulty(int difficultyLevel)
	lua_register(L, "GetGameDifficulty", lua_GetGameDifficulty); // int GetGameDifficulty()

	lua_register(L, "GetEra", lua_GetEra); // Era GetEra()
	lua_register(L, "EnableCops", lua_EnableCops); // void EnableCops(bool onOff)
	lua_register(L, "DeleteAllChaseEntities", lua_DeleteAllChaseEntities); // void DeleteAllChaseEntities(AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "AddChaseCarWeaponType", lua_AddChaseCarWeaponType); // void AddChaseCarWeaponType(EWeapons weapon, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "AddChaseCarVehicleType", lua_AddChaseCarVehicleType); // void AddChaseCarVehicleType(int vehicleType, bool isSecondaryVehicle, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "RemoveChaseCarVehicleType", lua_RemoveChaseCarVehicleType); // void RemoveChaseCarVehicleType(int vehicleType, bool isSecondaryVehicle, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "AddChaseCarCharacterType", lua_AddChaseCarCharacterType); // void AddChaseCarCharacterType(int skinID, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "RemoveChaseCarCharacterType", lua_RemoveChaseCarCharacterType); // void RemoveChaseCarCharacterType(int skinID, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "SetChaseCarPatrolDensity", lua_SetChaseCarPatrolDensity); // void SetChaseCarPatrolDensity(float density, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)

	lua_register(L, "CreateVehicleInstance", lua_CreateVehicle); // Vehicle CreateVehicleInstance(int model, float x, float y, float z, [ float angle = 0.0)
	lua_register(L, "CreateVehicle", lua_CreateVehicleActor); // Vehicle_Actor CreateVehicle(int model, float x, float y, float z, [ float angle = 0.0, bool startCreated = true, int tintValue = 1, float initialSpeed = 0.0, float initialFelony = 0.0, impactSoftness = 1.0, explosionSoftness = 1.0, bulletSoftness = 1.0, impactFragility = 1.0, bool useRandomTint)
	lua_register(L, "DestroyVehicleInstance", lua_DestroyVehicle); // void DestroyVehicleInstance(Vehicle vehicle)
	lua_register(L, "DestroyVehicle", lua_DestroyVehicleActor); // void DestroyVehicle(Vehicle_Actor vehicle)
	lua_register(L, "CreateHelicopter", lua_CreateHelicopter); // Helicopter CreateHelicopter(float x, float y, float z, [ float velx = 0.0, float vely = 0.0, float velz = 0.0, float angle = 0.0, bool isGoonHeli = true, bool destroyable = false, bool isLanded = false, bool helicopterOnlySpline = false)

	lua_register(L, "ActivatePager", lua_ActivatePager); // void ActivatePager()
	lua_register(L, "LaunchVEdit", lua_LaunchVEdit); // void LaunchVEdit()

	lua_register(L, "CreateCharacter", lua_CreateCharacterActor); // Character_Actor CreateCharacter(int skin, float x, float y, float z, [ float angle = 0.0, bool startCreated = true, EWeapons weapon, float initialHealth = 1.0, float initialFelony = 0.0, Vehicle_Actor initialVehicle = nil, int initialVehicleSeat = 0, bool addToFelonyManager = false, bool doNotUseIdleAnims, bool isPlayer = false)

	lua_register(L, "SetMusicTrack", lua_SetMusicTrack); // void SetMusicTrack(int trackId);
	lua_register(L, "GetMileometer", lua_GetMileometer); // float GetMileometer();
	lua_register(L, "lua_GetMoney", lua_GetMoney); // int GetMoney()
	lua_register(L, "lua_SetMoney", lua_SetMoney); // void SetMoney(int amount)

	lua_register(L, "SetVehicleFelonyLevel", lua_SetVehicleFelonyLevel); // void SetVehicleFelonyLevel(Vehicle vehicle, float felony, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "SetFelonyLevel", lua_SetFelonyLevel); // void SetFelonyLevel(Character character, float felony, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "GetFelonyLevel", lua_GetFelonyLevel); // float GetFelonyLevel(Character character, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "SetChaseCarMaxChasers", lua_SetChaseCarMaxChasers); // void SetChaseCarMaxChasers(int maxChasers, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)

	lua_register(L, "CreatePatrolHelicopterUnit", lua_CreatePatrolHelicopterUnit); // void CreatePatrolHelicopterUnit(float x, float y, float z, [ float angle, AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP) : void CreatePatrolHelicopterUnit(Vector position, [ float angle, AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "CreatePatrolCharacterOnFoot", lua_CreatePatrolCharacterOnFoot); // void CreatePatrolCharacterOnFoot(float x, float y, float z, [ float angle, AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP) : void CreatePatrolCharacterOnFoot(Vector position, [ float angle, AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP)
	lua_register(L, "CreatePatrolVehicleUnit", lua_CreatePatrolVehicleUnit); // void CreatePatrolVehicleUnit(float x, float y, float z, float angle, [ AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP, bool snapToTerrain = false, bool useSecondaryVehicleType = false) : void CreatePatrolVehicleUnit(Vector position, [ float angle,  AIFelonySystemPatrolCarTypeEnum patrolType = E_PATROLCARTYPE_COP,  bool snapToTerrain = false, bool useSecondaryVehicleType = false)

	lua_register(L, "SetEntityPriority", lua_SetEntityPriority); // void SetEntityPriority(SpooledPackageType package, int entityID, ESpoolPriority priority)
	lua_register(L, "RequestEntity", lua_RequestEntity); // void RequestEntity(SpooledPackageType package, int entityID, ESpoolPriority priority)
	lua_register(L, "IsEntityLoaded", lua_IsEntityLoaded); // bool IsEntityLoaded(SpooledPackageType package, int entityID)
	lua_register(L, "IsEntityPresent", lua_IsEntityPresent); // bool IsEntityPresent(SpooledPackageType package, int entityID)

	lua_register(L, "IsPlayerFreeAiming", lua_IsPlayerFreeAiming); // bool IsPlayerFreeAiming()
	lua_register(L, "HasPlayerShotRecently", lua_HasPlayerShotRecently); // bool HasPlayerShotRecently()
	lua_register(L, "AddAllWeaponsForPlayer", lua_AddAllWeaponsForPlayer); // void AddAllWeaponsForPlayer()
	
	lua_register(L, "AddMapItem", lua_AddMapItem); // MapItem AddMapItem(int type, Vector position, float angle) : MapItem AddMapItem(int type, float x, float y, float z, float angle)
	lua_register(L, "GetMapItems", lua_GetMapItems); // { MapItem } GetMapItems()
	lua_register(L, "GetMapMarkerActive", lua_GetMapMarkerActive); // bool GetMapMarkerActive()
	lua_register(L, "SetMapMarkerActive", lua_SetMapMarkerActive); // void SetMapMarkerActive(bool active)
	lua_register(L, "GetPlayerMapItem", lua_GetPlayerMapItem); // MapItem GetPlayerMapItem()
	lua_register(L, "GetCameraMapItem", lua_GetCameraMapItem); // MapItem GetCameraMapItem()
	lua_register(L, "GetMapMarkerItem", lua_GetMapMarkerItem); // MapItem GetMapMarkerItem()

	lua_register(L, "SetGameSpeed", lua_SetMasterSpeedMultiplier);
	lua_register(L, "SetMasterSpeedMultiplier", lua_SetMasterSpeedMultiplier);

	// hooking funcs
	lua_register(L, "memwrite", lua_memwrite); // void memwrite(uint address, string buffer, uint size)
	lua_register(L, "memread", lua_memread); // string memread(uint address, uint size)
	lua_register(L, "mempatch", lua_mempatch); // void mempatch(uint address, intptr_t labelPtr)
	lua_register(L, "meminject", lua_meminject); // void meminject(uint address, intptr_t labelPtr, int type); 
	lua_register(L, "memalloc", lua_memalloc); // intptr_t memalloc(uint size)
	lua_register(L, "memfree", lua_memfree); // void memfree(intptr_t blockPtr)

	// cast funcs
	lua_register(L, "castfloat", lua_castfloat); // float castfloat(string buffer, [ int offset = 0) 
	lua_register(L, "castdouble", lua_castdouble); // double castdouble(string buffer, [ int offset = 0)
	lua_register(L, "castint", lua_castint); // int castint(string buffer, [ int offset = 0)
	lua_register(L, "castuint", lua_castuint); // uint castuint(string buffer, [ int offset = 0)
	lua_register(L, "castshort", lua_castshort); // short castshort(string buffer, [ int offset = 0)
	lua_register(L, "castushort", lua_castushort); // ushort castushort(string buffer, [ int offset = 0)

	// class cast funcs
	lua_register(L, "castCharacter", lua_castCharacter); // Character castCharacter(intptr_t address) 
	lua_register(L, "castVehicle", lua_castVehicle); // Vehicle castVehicle(intptr_t address) 
	lua_register(L, "castHelicopter", lua_castHelicopter); // Helicopter castHelicopter(intptr_t address) 
	lua_register(L, "castMapItem", lua_castMapItem); // MapItem castMapItem(intptr_t address) 

	// math space stuff (outside of vector)
	lua_register(L, "GetDistanceBetweenPoints2D", lua_GetDistanceBetweenPoints2D); // float GetDistanceBetweenPoints2D(float x1, float y1, float x2, float y2)
	lua_register(L, "GetDistanceBetweenPoints3D", lua_GetDistanceBetweenPoints3D); // float GetDistanceBetweenPoints2D(float x1, float y1, float z1, float x2, float y2, z2)

	// input
	lua_register(L, "GetAsyncKeyState", lua_GetAsyncKeyState); // int GetAsyncKeyState(int keycode); 
	lua_register(L, "GetInputInfo", lua_GetInputInfo); // float: value, bool: debounce GetInputInfo(EInputAction action);

	// camera
	lua_register(L, "SetCameraPosition", lua_SetCameraPosition); // void SetCameraPosition(Vector pos)
	lua_register(L, "CreateCameraSelect", lua_CreateCameraSelect); // CameraSelect CreateCameraSelect(ECameraSelectType cameraType, LifeActor target, ECameraSelect_VehicleCamType vehiclePosition, [ float duration = 60.0, float zoom = 1.0, float motionBlur = 0.0, float speed = 1.0, float blendTime = 0.0)
	lua_register(L, "CreateCamera", lua_CreateCamera); // Camera CreateCamera(Vector position, Quaternion rotation, [ LifeActor attachTo = nil, LifeActor lookAt = nil)
	lua_register(L, "ToggleFreeCam", lua_ToggleFreeCam); // void ToggleFreeCam(bool status, [ int gamepadId = 0)

	// IGCs
	lua_register(L, "ToggleIGCS", lua_ToggleIGCS); // void ToggleIGCS(bool status)

	// prop
	lua_register(L, "CreateProp", lua_CreateProp); // Prop CreateProp(Vector position, EGadgetType gadgetType, [ Quaternion rotation, bool canbeTargeted = false, bool startCreated = true)

	// point actor
	lua_register(L, "CreatePoint", lua_CreatePoint); // Point_Actor CreatePoint(Vector position, [ Quaternion rotation = Quaternion(0, 0, 0, 0))

	// test volume actor
	lua_register(L, "CreateTestVolume", lua_CreateTestVolume); // TestVolume CreateTestVolume(Vector position, [ Quaternion rotation = Quaternion(0, 0, 0, 0), EPrimitiveType primType = EPrimitiveType_Cylinder, float widthOrRadius = 2.5, float length = 0.0, height = 5.0, LifeActor attachTo = nil)
}

void Init_Lua_MetaTables()
{
	// from MOSS
	Init_Lua_MetaTable_Character();
	Init_Lua_MetaTable_Vehicle();
	Init_Lua_MetaTable_VehicleActor();
	Init_Lua_MetaTable_VehicleInstance();
	Init_Lua_MetaTable_Helicopter();
	Init_Lua_MetaTable_MapItem();
	Init_Lua_MetaTable_ObjectiveIcon();
	Init_Lua_MetaTable_Prop();
	Init_Lua_MetaTable_CameraSelect();
	Init_Lua_MetaTable_CharacterInstance();
	Init_Lua_MetaTable_CharacterActor();
	Init_Lua_MetaTable_PointActor();
	Init_Lua_MetaTable_TestVolume();
	Init_Lua_MetaTable_Camera();
	// TODO: vehicle (object), life system, vehicle manager, maybe do gadgets (props, etc.)

	// extern
	Init_Lua_MetaTable_Vector(L);
	Init_Lua_MetaTable_Quaternion(L);
}