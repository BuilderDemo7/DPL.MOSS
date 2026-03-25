#pragma once
#include "Input.h"
#include "EInputAction.h"

class CInputManager
{
public:
	// _vt$20CInputManager
	virtual ~CInputManager() = default;

	// Input_impl input;
	// input = get_input(&input, EInputAction_Pause);
	virtual Input_impl* get_input(Input_impl *__return_storage_ptr__, EInputAction eAction) = 0;

	Input_impl * GetModifiableInput(EInputAction eAction);
};

CInputManager* GetSimulationInputManager();
CInputManager* GetFrontendInputManager();

CInputManager* GetInputManagerByAction(EInputAction input);