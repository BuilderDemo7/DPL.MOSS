--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
-- Passenger mode for player, press L to get inside a vehicle (doesn't work in driver's door/seat!)
--=====================================

function step()
	if (GetAsyncKeyState(VK_L) & 0x1 ~= 0) then
		local plrChara = GetPlayerCharacter()
		
		if plrChara:GetVehicle() ~= nil then
			return -- player's already on a vehicle
		end
		
		local veh,door = FindClosestVehicleForEntry(plrChara, false, false, true)
		if (door == nil) then door = 0; print("assert -> door = 0") end -- hack: prevent game crash or script errors
		
		if veh ~= nil and (door ~= 0) then -- if door's not the driver's door
			plrChara:EnterVehicle(veh, door, false) -- enter as passenger (without hi-jacking)
			print("--> entering as passenger!")
		else
			print("assert: veh ~= nil and (door ~= 0) -> false")
		end
	end
end