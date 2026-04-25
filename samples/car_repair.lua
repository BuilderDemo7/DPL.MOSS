--=====================================
--	Sample by S-Core03
--	
--	A simple car repair script.
--=====================================

function isKeyDown(key)
    return GetAsyncKeyState(key) ~= 0
end

local lastPress = false

function start()
    print("Vehicle Repaired.")
end

function step()
    local player = GetPlayerCharacter()
    if player == nil then return end
    
    local veh = player:GetVehicle()
    if veh == nil then return end

    local keyState = isKeyDown(VK_0)
    if keyState and not lastPress then
     
        veh:Repair()
        
        veh:SetDamage(0.0)
        
        print("Vehicle Repaired!")
        ShowMissionComment(2.0, "Vehicle Repaired")
    end
    lastPress = keyState
end