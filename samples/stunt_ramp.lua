--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	A sample of a ramp that spawns when the player presses the 'I' key, the purpose is for testing the Prop class
--=====================================

local Ramp_Distance = 10
local Ramp_Time = 0
local Ramp_LifeTime = 45 -- 45 secs
local Ramp_On = false
local Ramp_Prop = nil
local Ramp_Key = VK_I -- letter 'I'

function calculateRampPosAndRotation()
	local plr = GetPlayerCharacter()
	
	if (plr ~= nil) then
		local pos = plr:GetPosition()
	
		local fwd = plr:GetForward()
		if (math.abs(fwd.Y) > 1.5) then -- height snap
			fwd = Vector.new(fwd.X, 0, fwd.Z)
		end
	
		local rampPos = pos + (fwd * Vector.new(Ramp_Distance, Ramp_Distance, Ramp_Distance))
		local rampRotation = Quaternion.FromEuler(math.deg(plr:GetAngle()) + 180, 0, 0)
					
		if (plr:GetVehicle() ~= nil) then
			-- sometimes the ramp spawns too high to jump
			rampPos = Vector.new(rampPos.X, rampPos.Y - 0.6, rampPos.Z) -- lower it a bit	
		end
		
		return rampPos, rampRotation
	end
end

function step()
	if (GetAsyncKeyState(Ramp_Key) & 0x1 ~= 0) then
		local plr = GetPlayerCharacter()
	
		if (plr ~= nil) then
			if Ramp_On then
				-- reset if the player presses it again
				Ramp_Time = 0
				
				if (Ramp_Prop ~= nil) then
					Ramp_Prop:Delete()
					
					local pos = plr:GetPosition()
			
					local rampPos,rampRotation = calculateRampPosAndRotation()
					
					Ramp_Prop:SetPosition(rampPos)
					Ramp_Prop:SetRotation(rampRotation)
					
					Ramp_Prop:Instantiate()
				end
			end
		
			if not Ramp_On then
				local rampPos,rampRotation = calculateRampPosAndRotation()
	
				Ramp_On = true
				print("Creating ramp in front of player!")
				if Ramp_Prop == nil then
					Ramp_Prop = CreateProp(rampPos, 83, rampRotation, false, false)
				end
				if (Ramp_Prop ~= nil) then
					Ramp_Prop:SetPosition(rampPos)
					Ramp_Prop:SetRotation(rampRotation)
					
					Ramp_Prop:Instantiate()
				end
			end
		end
	end
	
	if Ramp_On then
		Ramp_Time = Ramp_Time + 0.0166666667 -- add the time, it's ok since there's no delta time but the game have a speed dependent system for the frames.
				
		-- make it be absorved by the ground (animation)
		--if (Ramp_Prop.Created) then
			if (Ramp_Time >= Ramp_LifeTime / 2) then
				local pos = Ramp_Prop:GetPosition()
				Ramp_Prop:SetPosition(pos + Vector.new(0, -0.005, 0)) -- lower it down according to time
			end
		--end
				
		if (Ramp_Time >= Ramp_LifeTime) then
			print("Destroying ramp!")
			Ramp_On = false
			Ramp_Time = 0
			Ramp_Prop:Delete() -- when deleted, it won't be nil, so we can use Instantiate() function again
		end
	end
end