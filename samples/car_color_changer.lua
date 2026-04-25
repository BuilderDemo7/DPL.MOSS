--=====================================
--	Sample by S-Core03
--	
--	Car Color Changer Script
--=====================================

function isKeyDown(key)
    return GetAsyncKeyState(key) ~= 0
end

local lastPress0 = false
local lastPress1 = false
local colorIndex = 1

-- Palette of 20 RGB colors (values 0.0 to 1.0)
local colors = {
    {1.0, 1.0, 1.0}, -- 1. Pure White
    {0.05, 0.05, 0.05}, -- 2. Black/Dark Grey
    {1.0, 0.0, 0.0}, -- 3. Bright Red
    {0.0, 0.8, 0.0}, -- 4. Forest Green
    {0.0, 0.0, 1.0}, -- 5. Royal Blue
    {1.0, 0.9, 0.0}, -- 6. Sunshine Yellow
    {1.0, 0.4, 0.0}, -- 7. Orange
    {0.6, 0.0, 0.8}, -- 8. Deep Purple
    {0.0, 1.0, 1.0}, -- 9. Cyan
    {1.0, 0.2, 0.6}, -- 10. Pink
    {0.5, 0.3, 0.1}, -- 11. Chocolate Brown
    {0.7, 0.7, 0.7}, -- 12. Silver / Grey
    {0.2, 0.4, 0.2}, -- 13. Olive / Military
    {0.0, 0.2, 0.4}, -- 14. Navy Blue
    {0.9, 0.7, 0.5}, -- 15. Sand / Beige
    {0.3, 0.0, 0.0}, -- 16. Maroon
    {0.8, 1.0, 0.8}, -- 17. Mint Green
    {1.0, 1.0, 0.6}, -- 18. Cream
    {0.4, 0.4, 0.6}, -- 19. Slate Blue
    {0.1, 0.5, 0.4}  -- 20. Teal
}

function start()
    print("Vehicle Tool Loaded: [0] Repair, [1] Cycle Colors")
end

function step()
    local player = GetPlayerCharacter()
    if player == nil then return end
    
    local veh = player:GetVehicle()
    if veh == nil then return end

    -- KEY [0]: REPAIR VEHICLE
    local k0 = isKeyDown(VK_0)
    if k0 and not lastPress0 then
        -- Uses address 0x5AD2A8 from Vehicle.cpp
        veh:ResetDamage() 
        ShowMissionComment(1.5, "Vehicle Repaired")
        print("Vehicle status: Repaired")
    end
    lastPress0 = k0

    -- KEY [1]: CYCLE THROUGH 20 COLORS
    local k1 = isKeyDown(VK_1)
    if k1 and not lastPress1 then
        colorIndex = colorIndex + 1
        if colorIndex > #colors then colorIndex = 1 end
        
        local c = colors[colorIndex]
        -- Writes RGB to offsets 140, 144, 148
        veh:SetColor(c[1], c[2], c[3])
        
        ShowMissionComment(1.0, "Color " .. colorIndex .. "/20")
        print("Color changed to index: " .. colorIndex)
    end
    lastPress1 = k1
end