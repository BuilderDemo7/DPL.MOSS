--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	A sample that flips your car upright after 10 seconds.
--=====================================

local fTime = 0.0
local timeForFlip = 10.0

function start()
	print("-- FLIP CAR SCRIPT - START --")
end

function shutdown()
	print("-- FLIP CAR SCRIPT - SHUTDOWN --")
end

-- helper function
function getVehicleSpeed(vehicle)
	local velocity = vehicle:GetVelocity()
	
	return velocity.Magnitude
end

-- step() - called every frame (when the game is unpaused)
function step()
	local plr = GetPlayerCharacter()

	if (plr ~= nil) then
		local veh = plr:GetVehicle()
		
		-- if the player is inside a vehicle (if vehicle isn't null)
		if (veh ~= nil) then
			local rotation = veh:GetRotation()
			local speed = getVehicleSpeed(veh)
			
			-- check if the car is sideways or upside down
			-- the original game checks if no wheels are on the ground but instead we will use the rotation to check.
			if ((math.abs(rotation.Z) >= 0.27 and math.abs(rotation.W) >= 0.27) or math.abs(rotation.X) > 0.27) and speed < 4 then
			
				-- first tick/time
				if (fTime <= 0) then
					print("debug: you car is upside down")
				end
			
				fTime = fTime + 0.0166666667 -- add the time, it's ok since there's no delta time but the game have a speed dependent system for the frames.
				if (fTime > timeForFlip) then
					local theRotation = veh:GetRotation()
					local newRotation = Quaternion.new(0, theRotation.Y, 0, theRotation.W) -- reset X and Z axis
				
					fTime = 0
					
					veh:SetRotation(newRotation) -- apply the rotation
					veh:SetVelocity(Vector.new(0,0,0)) -- make the car steady and wake up it's physics
					print("debug: your car has been flipped back upright!")
				end
			else
				if not (fTime > 0) then
					fTime = 0 -- cancel (conditions not matched)
				end
			end
		else
			if not (fTime > 0) then
				fTime = 0 -- cancel (player's not inside a vehicle)
			end
		end
	end
end