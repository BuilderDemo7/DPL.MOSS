--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	A script for making the player's car a super car by pressing LCtrl + N, you can also press LCtrl + B to print handling information for debugging
--=====================================

local gameStarted = false

function start()
	gameStarted = true
end

function step()
	if gameStarted then
		if (GetAsyncKeyState(VK_LCONTROL) ~= 0 and GetAsyncKeyState(VK_N) & 0x1 ~= 0) then
			local plr = GetPlayerCharacter()
			local veh = plr:GetVehicle()
			if (veh ~= nil) then
				veh:SetNitro(10.0)
				veh:SetProperty(18, 820, "float") -- thrust fwd
				veh:SetProperty(160, 230, "float") -- top speed
				veh:SetProperty(25, 1.05, "float") -- ride-height
				
				--veh:SetProperty(249, veh:GetProperty(249, "float") * 1.05, "float") -- camera Y (height)
				--veh:SetProperty(250, veh:GetProperty(250, "float") * 1.05, "float") -- camera Z (depth - behind)
			end
		end
		if (GetAsyncKeyState(VK_LCONTROL) ~= 0 and GetAsyncKeyState(VK_B) & 0x1 ~= 0) then
			local plr = GetPlayerCharacter()
			local veh = plr:GetVehicle()
			if (veh ~= nil) then
				print("-- VEHICLE PROPERTIES START --")
				for i = 0, 293 - 1 do
					print(string.format("[%d] = %f", i, veh:GetProperty(i, "float")))
				end
			end
		end
	end
end