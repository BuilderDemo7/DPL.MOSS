#include "InputManager.h"
#include "VisualsInputManager.h"

Input_impl * CInputManager::GetModifiableInput(EInputAction eAction)
{
	int index = eAction - (*(int*)(this + 0x4)); // eAction - this->m_iStartInput;
	return (Input_impl*)((this + 0x10) + (index * sizeof(Input_impl)));
}

Input_impl* CInputManager::get_input_HACK(Input_impl *__return_storage_ptr__, EInputAction eAction)
{
	return ((Input_impl*(__thiscall*)(CInputManager*, Input_impl *__return_storage_ptr__, EInputAction eAction))*(int*)(GetVTableAddress() + 4))(this, __return_storage_ptr__, eAction);
}

int CInputManager::GetVTableAddress()
{
	return *(int*)(this);
}

CInputManager* GetSimulationInputManager()
{
	return *(CInputManager**)0x70c6ec;
}

CInputManager* GetFrontendInputManager()
{
	return *(CInputManager**)0x70c6f4;
}

CInputManager* GetInputManagerByAction(EInputAction input)
{
	CInputManager* manager = NULL;

	if (input < EInputAction_Frontend_End && input > EInputAction_Frontend_Begin)
	{
		manager = GetFrontendInputManager();
	}
	else if (input < EInputAction_Simulation_End && input > EInputAction_Simulation_Begin)
	{
		manager = GetSimulationInputManager();
	}
	else if (input < EInputAction_Visuals_End && input > EInputAction_Visuals_Begin)
	{
		manager = (CInputManager*)GetVisualsInputManager();
	}

	return manager;
}