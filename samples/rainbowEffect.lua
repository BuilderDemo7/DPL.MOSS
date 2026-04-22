--=====================================
--	Sample by S-Core03
--	
--	Rainbow effect sample for any vehicle that the player is inside
--=====================================

local animTimer = 0

rainbowEffectOnOff = false
rainbowEffect = VK_END

function step()
  if GetAsyncKeyState(rainbowEffect) & 0x1 ~= 0 then
    rainbowEffectOnOff = not rainbowEffectOnOff 
  end
  if rainbowEffectOnOff then
    local r = math.sin(animTimer)
    local g = math.sin(animTimer+1)
    local b = math.sin(animTimer+2)

      local vehicle = GetPlayerCharacter():GetVehicle()
      if vehicle ~= nil then
             vehicle:SetColor(r,g,b)
      end

    animTimer = animTimer+0.016666

  end
end