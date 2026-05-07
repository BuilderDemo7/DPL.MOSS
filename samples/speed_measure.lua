--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	A sample that measures speed in KM/H and MPH (miles per hour), RPM and as well the magnitude of the velocity (speed)
--=====================================

local gameStarted = false
local gear = 0
local rpm = 0
local speed = 0
local speedMPH = 0
local speedKPH = 0
local inCar = false

local textX = 0.005
local textY = 0.35
local textSize = 0.75
local digitMeasurement = 4 -- 0.0000, increase for higher precision for math calculations!!!!!

function start()
	gameStarted = true
end

function step()
	if gameStarted then
		local plrChr = GetPlayerCharacter()
		if (plrChr ~= nil) then
			local veh = plrChr:GetVehicle()
			if (veh ~= nil) then
				rpm = veh:GetRPM()
				local vel = veh:GetVelocity()
				speed = vel.Magnitude
				
				 -- to mph according to the game's speedometer
				--speedMPH = speed * 0.4522509091
				--speedMPH = speed * 1.7204301075 -- closer we got
				speedMPH = speed * 2.258244453 -- that's a lot better!
				--speedMPH = speed * 0.443768856
				speedKPH = speedMPH * 1.609 -- to km/h according to real-life measurement
				gear = veh:GetGear()
				
				inCar = true
			else
				inCar = false
			end
		end
	end
end

function draw_mission()
	if gameStarted then
		if inCar then
			DrawText(string.format("GEAR: %d", gear), textX, textY,   EJustify_Left,   textSize,  textSize,      1.0, 1.0, 1.0, 1.0,   1)
			DrawText(string.format("RPM: %."..tostring(digitMeasurement).."f", rpm), textX, textY+(textSize/10),   EJustify_Left,   textSize,  textSize,      1.0, 1.0, 1.0, 1.0,   1)
			DrawText(string.format("SPEED: %."..tostring(digitMeasurement).."f", speed), textX, textY+((textSize/10)*2),   EJustify_Left,   textSize,  textSize,      1.0, 1.0, 1.0, 1.0,   1)
			DrawText(string.format("SPEED(MPH): %."..tostring(digitMeasurement).."f", speedMPH), textX, textY+((textSize/10)*3),   EJustify_Left,   textSize,  textSize,      1.0, 1.0, 1.0, 1.0,   1)
			DrawText(string.format("SPEED(KPH): %."..tostring(digitMeasurement).."f", speedKPH), textX, textY+((textSize/10)*4),   EJustify_Left,   textSize,  textSize,      1.0, 1.0, 1.0, 1.0,   1)
		end
	end
end