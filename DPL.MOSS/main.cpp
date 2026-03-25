/*
	Driver: Parallel Lines ASI Mod

	Mod Oriented Scripting System (MOSS)

	Author: BuilderDemo7
*/

#include "pch.h"
#include "main.h"
#include "Hooks.h"

#include "MOSS/Lua_Main.h"

void OnInitializePlugin()
{
	Nop(0x45c07a, 7);
	InjectHook(0x45c07a, CState__LoadMission__Hook, PATCH_JUMP);
	InjectHook(0x4df3ec, CState_Simulation__Initialise__Hook, PATCH_JUMP);
	
	// for post step func
	Nop(0x4722f1, 6);
	InjectHook(0x4722f1, CLifeSystem__Step__Hook, PATCH_JUMP);

	Nop(0x55d904, 5);
	InjectHook(0x55d904, visuals_draw__DrawMission__Hook, PATCH_JUMP);
	
	InjectHook(0x4a945e, CState_Reload__OnEnterState_Hook, PATCH_JUMP);

	Nop(0x4a7732, 6);
	InjectHook(0x4a7732, CLoadingScreen__Deactivate__Hook, PATCH_JUMP);
	
	InjectHook(0x4dee88, Step_Lua, PATCH_CALL);
}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		OnInitializePlugin();
	}
}


