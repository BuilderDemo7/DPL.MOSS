--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	Example sample for Vehicle_Actor and Character_Actor, including AI wanderer feature
--  NOTE: Sample as AI_wanderer.lua script but modified for a reckless driving AI
--=====================================

-- spawn position: Jersey - Ray's Autos (close to the parking lot's street)
local x,y,z,angle = -2080.482, 0.5, 3744.280, math.rad(90)

-- variables
aiCharacter = nil
aiCar = nil

-- settings
driveAsCivilian = false -- changed for reckless driving
wanderSpeed = 35
wanderAcceleration = 1.15 -- optional to tweak
wanderTraction = 1.0 -- optional to tweak

-- logic
goneWander = false

-- start() - called when the loading screen is done and the player is about to play the game
function start()
	aiCar = CreateVehicle(53, x,y,z, angle, true, 1, 1) -- Andec
	aiCharacter = CreateCharacter(0x59, x,y,z, angle, true, 0, 1.0, 0.0, aiCar, 0) -- Ray from 1978
end

-- step() - called every frame the game updates
function step()
	if not goneWander then -- if not already wandering
		if aiCharacter ~= nil then -- if the character was created
			local chara = aiCharacter:GetInstance() -- returns a Character
			if (chara ~= nil) then -- checks if the character instance was spooled in (when you're close to it) 
				aiCharacter:GoWander(wanderSpeed, wanderAcceleration, 1.0, 1.0, driveAsCivilian) -- start the wander AI on the street, BE CAREFUL when changing the spawn position if it's off-road then the game will crash
				goneWander = true
			end
		end
	end
end