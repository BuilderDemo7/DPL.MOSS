--=====================================
--	Sample by Snoopii (member & admin of Driver Madness)
--	
--	Snoopii made this based on the cheat he made for D:PL Cheat Table (Cheat Engine), which teleports you to the green marker in the map.
--=====================================

-- Configuration
local SPAWN_CONFIG = {
    KEY_SPAWN = VK_F12,
    HEIGHT_MAP_ADDR = 0x0709838,
    FRAME_COUNT_ADDR = 0x071CE90,
    STABILITY_REQUIRED = 3 -- Frames the height must remain identical to "lock in"
}

-- Global state
local teleportState = "IDLE"
local startFrame = 0
local savedX, savedZ = 0, 0
local lastKeyStatus = false

-- Stability Tracking
local lastObservedHeight = -120.0
local stabilityCounter = 0

-- SAFE READERS --

function SafeReadInt32(address)
    local function getByte(addr)
        local data = memread(addr, 1)
        if data and #data > 0 then return string.byte(data) end
        return 0 
    end
    local b1 = getByte(address)
    local b2 = getByte(address + 1)
    local b3 = getByte(address + 2)
    local b4 = getByte(address + 3)
    return b1 + (b2 * 256) + (b3 * 65536) + (b4 * 16777216)
end

function SafeReadFloat(address)
    local data = memread(address, 4)
    if data and #data == 4 then
        return string.unpack("f", data)
    end
    return 0.0
end

-- LOGIC --

function startTeleport()
    local plr = GetPlayerCharacter()
    local mapItem = GetMapMarkerItem()
    if not plr or not mapItem then return end

    local MapPos = mapItem:GetPosition()
    savedX, savedZ = MapPos.X, MapPos.Z
    
    -- Benchmark start
    startFrame = SafeReadInt32(SPAWN_CONFIG.FRAME_COUNT_ADDR)
    
    -- Reset stability tracking
    lastObservedHeight = -20000.0 -- Different from initial dummy
    stabilityCounter = 0
    
    -- Jump high into the air
    plr:SetPosition(savedX, 80.0, savedZ)
    
    teleportState = "WAITING"
    print("Jumped! Waiting for height to stabilize...")
end

function step()
    -- Trigger handling
    local currentKeyStatus = isKeyDown(SPAWN_CONFIG.KEY_SPAWN)
    if currentKeyStatus and not lastKeyStatus then
        startTeleport()
    end
    lastKeyStatus = currentKeyStatus

    -- Stability Logic
    if teleportState == "WAITING" then
        local currentHeight = SafeReadFloat(SPAWN_CONFIG.HEIGHT_MAP_ADDR)
        
        -- Ignore 0.0 (Unloaded/Void)
        if currentHeight ~= 0.0 then
            
            -- Compare to last frame's height
            -- We use math.abs for float precision safety
            if math.abs(currentHeight - lastObservedHeight) < 0.0001 then
                stabilityCounter = stabilityCounter + 1
            else
                -- Height is still changing (engine is loading/adjusting)
                stabilityCounter = 0
                lastObservedHeight = currentHeight
            end

            -- Only proceed if the height has been the same for X frames
            if stabilityCounter >= SPAWN_CONFIG.STABILITY_REQUIRED then
                local endFrame = SafeReadInt32(SPAWN_CONFIG.FRAME_COUNT_ADDR)
                local plr = GetPlayerCharacter()
                
                if plr then
                    plr:SetPosition(savedX, currentHeight, savedZ)
                    
                    local msg = string.format("Landed! Height: %.2f | Load: %d frames", currentHeight, endFrame - startFrame)
                    ShowMissionComment(4.0, msg)
                    print(msg)
                    
                    teleportState = "IDLE" -- Sequence complete
                end
            end
        end
    end
end

-- Framework hooks
function start() 
    print("Stable Teleport Loaded. Press F12 to begin.")
end