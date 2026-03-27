#include "Hooks.h"
#include "Hooks_Redirect.h"

#include "moss/Lua_Main.h"

#include "dpl\CPCViewport.h"

int g_iTickLoadingScreenDeactivation = 0;
bool g_bSimulationInitalised = false;

void __declspec(naked) CState__LoadMission__Hook()
{
	static int jumpback_0x45c081 = 0x45c081;

	// Register save
	static int org_eax = 0;
	static int org_ebx = 0;
	static int org_ecx = 0;
	static int org_edx = 0;
	_asm {
		mov[org_eax], eax
		mov[org_ebx], ebx
		mov[org_ecx], ecx
		mov[org_edx], edx
	}

	// Custom code
	OnLoadMission();

	// Register restoration
	_asm {
		mov ecx, [org_ecx]
		mov eax, [org_eax]
		mov ebx, [org_ebx]
		mov edx, [org_edx]
	}

	// Original code
	_asm {
		mov ecx, eax
	}

	// Jump back
	_asm {
		jmp jumpback_0x45c081
	}
}

// 4a945e
void __declspec(naked) CState_Reload__OnEnterState_Hook()
{
	static int jumpback_0x4a9463 = 0x4a9463;
	static int calladdr_0x467e04 = 0x467e04;

	// Register save
	static int org_eax = 0;
	static int org_ebx = 0;
	static int org_ecx = 0;
	static int org_edx = 0;
	_asm {
		mov[org_eax], eax
		mov[org_ebx], ebx
		mov[org_ecx], ecx
		mov[org_edx], edx
	}

	// Custom code
	OnReloadGame();

	// Register restoration
	_asm {
		mov ecx, [org_ecx]
		mov eax, [org_eax]
		mov ebx, [org_ebx]
		mov edx, [org_edx]
	}

	// Original code
	_asm {
		call calladdr_0x467e04
	}

	// Jump back
	_asm {
		jmp jumpback_0x4a9463
	}
}

void __declspec(naked) CState_Simulation__Initialise__Hook()
{
	//static int jumpback_0x45c081 = 0x45c081;

	// Register save
	static int org_eax = 0;
	static int org_ebx = 0;
	static int org_ecx = 0;
	static int org_edx = 0;
	_asm {
		mov[org_eax], eax
		mov[org_ebx], ebx
		mov[org_ecx], ecx
		mov[org_edx], edx
	}

	// Custom code
	g_bSimulationInitalised = true;

	// Register restoration
	_asm {
		mov ecx, [org_ecx]
		mov eax, [org_eax]
		mov ebx, [org_ebx]
		mov edx, [org_edx]
	}

	// Original code
	_asm {
		pop esi
		mov esp,ebp
		pop ebp
		ret
	}

	// Jump back
	//_asm {
	//	jmp jumpback_0x45c081
	//}
}

void __declspec(naked) CLifeSystem__Step__Hook()
{
	//static int jumpback_0x45c081 = 0x45c081;

	// Register save
	static int org_eax = 0;
	static int org_ebx = 0;
	static int org_ecx = 0;
	static int org_edx = 0;
	_asm {
		mov[org_eax], eax
		mov[org_ebx], ebx
		mov[org_ecx], ecx
		mov[org_edx], edx
	}

	// Custom code
	OnPostStep();

	// Register restoration
	_asm {
		mov ecx, [org_ecx]
		mov eax, [org_eax]
		mov ebx, [org_ebx]
		mov edx, [org_edx]
	}

	// Original code
	_asm {
		pop ebx
		add ebp,0x78
		leave
		ret
	}

	// Jump back
	//_asm {
	//	jmp jumpback_0x45c081
	//}
}

void __declspec(naked) visuals_draw__DrawMission__Hook()
{
	static int jumpback_0x55d909 = 0x55d909;

	// Register save
	static int org_eax = 0;
	static int org_ebx = 0;
	static int org_ecx = 0;
	static int org_edx = 0;
	static int org_esp = 0;
	static CPCViewport* in_vp = 0;
	_asm {
		mov[org_eax], eax
		mov[org_ebx], ebx
		mov[org_ecx], ecx
		mov[org_edx], edx
		mov[org_esp], esp
	}

	_asm
	{
		mov [in_vp],esi // in_vp = piViewport
	}

	// Custom code
	OnDrawMission(in_vp);

	// Register restoration
	_asm {
		mov ecx, [org_ecx]
		mov eax, [org_eax]
		mov ebx, [org_ebx]
		mov edx, [org_edx]
		mov esp, [org_esp]
	}

	// Original code
	_asm {
		push ecx
		mov eax, esp
		mov dword ptr [eax],esi
	}

	// Jump back
	_asm {
		jmp jumpback_0x55d909
	}
}

void __declspec(naked) CTargetManager__Draw__Hook()
{
	static int jumpback_0x473cfc = 0x473cfc;

	// Register save
	static int org_eax = 0;
	static int org_ebx = 0;
	static int org_ecx = 0;
	static int org_edx = 0;
	static int org_esp = 0;
	static int org_esi = 0;
	static int org_edi = 0;
	_asm {
		mov[org_eax], eax
		mov[org_ebx], ebx
		mov[org_ecx], ecx
		mov[org_edx], edx
		mov[org_esp], esp
		mov[org_esi], esi
		mov[org_edi], edi
	}

	// Custom code
	OnDrawTargetManager();

	// Register restoration
	_asm {
		mov ecx, [org_ecx]
		mov eax, [org_eax]
		mov ebx, [org_ebx]
		mov edx, [org_edx]
		mov esp, [org_esp]
		mov esi, [org_esi]
		mov edi, [org_edi]
	}

	// Original code
	_asm {
		lea esi,[ecx+0x194]
	}

	// Jump back
	_asm {
		jmp jumpback_0x473cfc
	}
}

void __declspec(naked) CLoadingScreen__Deactivate__Hook()
{
	static int jumpback_0x4a7738 = 0x4a7738;

	// Register save
	static int org_eax = 0;
	static int org_ebx = 0;
	static int org_ecx = 0;
	static int org_edx = 0;
	static int org_esp = 0;
	static int org_ebp = 0;
	_asm {
		mov[org_eax], eax
		mov[org_ebx], ebx
		mov[org_ecx], ecx
		mov[org_edx], edx
		mov[org_ebp], ebp
		mov[org_esp], esp
	}

	// Custom code
	if (g_bLuaScriptsLoaded && !g_bLuaScriptsStarted)
	{
		Lua_Start();
	}

	// Register restoration
	_asm {
		mov ecx, [org_ecx]
		mov eax, [org_eax]
		mov ebx, [org_ebx]
		mov edx, [org_edx]
		mov esp, [org_esp]
	}

	// Original code
	_asm {
		lea eax,[ecx+0x3d9]
	}

	// Jump back
	_asm {
		jmp jumpback_0x4a7738
	}
}