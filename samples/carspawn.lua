--=====================================
--	Sample by Snoopii (member & admin of Driver Madness)
--	
--	A simple car spawner.
--=====================================

-- Configuration
local SPAWN_CONFIG = {
    MODEL_ID = 1,          -- Change this ID for different cars
    SPAWN_DISTANCE = 5.0,   -- How many units in front of the player to spawn
    KEY_SPAWN = VK_F9       -- Press F9 to spawn
}

-- Main State
local LastVehicle = nil

function showMessage(msg, duration)
    ShowMissionComment(duration or 2, msg)
end

function isKeyDown(key)
    return GetAsyncKeyState(key) ~= 0
end

function spawnCar()
    local plr = GetPlayerCharacter()
    if not plr then return end

    -- 1. Calculate Position (In front of player)
    local pos = plr:GetPosition()
    local forward = plr:GetForward()
    local angle = plr:GetAngle()

    local spawnPos = Vector.new(
        pos.X + (forward.X * SPAWN_CONFIG.SPAWN_DISTANCE),
        pos.Y, -- Keeping Y the same so it doesn't spawn in the air/ground
        pos.Z + (forward.Z * SPAWN_CONFIG.SPAWN_DISTANCE)
    )

    -- 2. Cleanup old vehicle (Optional: prevents cluttering the world)
    if LastVehicle then
        DestroyVehicleInstance(LastVehicle) -- Uncomment if you only want 1 car at a time
    end

    -- 3. Create the Vehicle
    -- CreateVehicleInstance(model, x, y, z, angle)
    local veh = CreateVehicleInstance(SPAWN_CONFIG.MODEL_ID, spawnPos.X, spawnPos.Y, spawnPos.Z, angle)
    
    if veh then
        LastVehicle = veh
        showMessage("Vehicle Spawned!", 2)

        -- 4. Teleport Player into seat 0 (Driver)
        plr:TeleportIntoVehicle(veh, 0)
    else
        showMessage("Failed to spawn vehicle.", 2)
    end
end

-- Core Framework Functions
function start() 
    print("Car Spawner Loaded. Press F9 to spawn.")
end

function shutdown() 
    print("Car Spawner Unloaded.")
end

local lastKeyStatus = false
function step()
    local currentKeyStatus = isKeyDown(SPAWN_CONFIG.KEY_SPAWN)
    
    -- "Rising Edge" detection: only triggers once per press
    if currentKeyStatus and not lastKeyStatus then
        spawnCar()
    end
    
    lastKeyStatus = currentKeyStatus
end