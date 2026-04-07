--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	18-wheeler anarchy mode test inspired by Driv3r.
--=====================================

local goon_vehicle = 59 -- Boldius (truck)
local goon_character = 0x1D -- TheKid_Then

function start()
	-- disable cops first
	SetChaseCarMaxChasers(0, E_PATROLCARTYPE_COP)
	--EnableCops(false) -- may be disabling the goons as well
	
	-- initialise goons assets
	local wep = (GetEra() == Era_Then) and 3 or 9 -- Uzi (1978) or P90 (2006)
	goon_character = (GetEra() == Era_Then) and 0x1D or 0x4 -- TheKid_Then (1978) or TheDriver_Now (2006)
	
	-- load models up
	SetEntityPriority(SpooledPackageType_Vehicles, goon_vehicle, ESpoolPriority_Required) -- load vehicle model
	SetEntityPriority(SpooledPackageType_CharacterSkins, goon_character, ESpoolPriority_Required) -- load character skin
	
	-- initialise their weapons, vehicle and character skin
	AddChaseCarWeaponType(wep, E_PATROLCARTYPE_GOON)
	AddChaseCarVehicleType(goon_vehicle, false, E_PATROLCARTYPE_GOON)
	AddChaseCarCharacterType(goon_character, E_PATROLCARTYPE_GOON)
	
	-- make them to be able to spawn
	SetChaseCarMaxChasers(5, E_PATROLCARTYPE_GOON)
	SetChaseCarPatrolDensity(4.5, E_PATROLCARTYPE_GOON)
	
	-- make them chase you >:)
	SetFelonyLevel(GetPlayerCharacter(), 5.0, E_PATROLCARTYPE_GOON) -- 500% felony!
	
	-- make them intense
	SetGameDifficulty(6)
end