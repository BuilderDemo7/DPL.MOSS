--=====================================
--	Script by BuilderDemo7 (creator of MOSS)
--	
-- Noclip script, to activate it, press Q + R on the keyboard and use WASD to move, LShift to go down and LCtrl to go up.
--=====================================

local gameStarted = false

function start()
	noclip_on = false
	gameStarted = true
end

noclip_on = false

-- like a combination: Q + R = toggle noclip
local noclip_togglekey1 = VK_Q
local noclip_togglekey2 = VK_R

local noclip_forwardkey = VK_W
local noclip_backwardkey = VK_S

local noclip_leftkey = VK_A
local noclip_rightkey = VK_D

local noclip_downkey = VK_LSHIFT
local noclip_upkey = VK_LCONTROL

local noclip_speed = 0.5

local noclip_pos = Vector.new(0,0,0)

function toggle_noclip()
	noclip_pos = GetPlayerCharacter():GetPosition()
	noclip_on = not noclip_on
	ClearMessages()
	if (noclip_on) then
		ShowMissionComment(1.0, "NOCLIP ON")
	else
		ShowMissionComment(1.0, "NOCLIP OFF")
	end
end

--function draw_mission()
--	DrawText(tostring(GetDeltaTime()), 0.5, 0.5)
--end

function step_noclip()
	local throttle = 0
	local strafe = 0
	local flyThrottle = 0
	if (GetAsyncKeyState(noclip_forwardkey) ~= 0) then
		throttle = 1
	elseif (GetAsyncKeyState(noclip_backwardkey) ~= 0) then
		throttle = -1
	end
	if (GetAsyncKeyState(noclip_leftkey) ~= 0) then
		strafe = 1
	elseif (GetAsyncKeyState(noclip_rightkey) ~= 0) then
		strafe = -1
	end
	if (GetAsyncKeyState(noclip_upkey) ~= 0) then
		flyThrottle = 1
	elseif (GetAsyncKeyState(noclip_downkey) ~= 0) then
		flyThrottle = -1
	end
	
	local element = GetPlayerCharacter()
	local isVehicle = false
	if (GetPlayerCharacter():GetVehicle() ~= nil) then
		element = GetPlayerCharacter():GetVehicle()
		isVehicle = true
	end
	element:SetVelocity(Vector.new(0,0,0))
	if (isVehicle) then
		element:SetAngularVelocity(Quaternion.new(0,0,0,0))
		element:SetAngle(element:GetAngle()) -- force up-right
	end
	
	local dt = (GetDeltaTime() * 60)*2
	local dtVec = Vector.new(dt, dt, dt)
	
	local generalSpeed = noclip_speed * dt
	
	local throttleSpeed = throttle * noclip_speed
	local strafeSpeed = strafe * noclip_speed
	local flySpeed = flyThrottle * noclip_speed
	
	local throttleVec = element:GetForwardVector() * Vector.new(throttleSpeed,throttleSpeed,throttleSpeed)
	local strafeVec = element:GetRightVector() *  Vector.new(strafeSpeed,strafeSpeed,strafeSpeed)
	local flyVec = element:GetUpVector() * Vector.new(flySpeed,flySpeed,flySpeed)

	if element ~= nil then
		if (isVehicle) then
			strafeVec = Vector.new(0,0,0)
			strafeVec_dt = Vector.new(0,0,0)
			
			local angleSpeed = 0
			if math.abs(strafe) > 0.001 then
				angleSpeed = math.rad(2) * strafeSpeed
			end
			
			if (math.abs(angleSpeed) >= 0.001) then
				element:SetAngle(element:GetAngle() + angleSpeed)
			end
		end
		
		local totalVelocity = throttleVec + strafeVec + flyVec
		
		noclip_pos = noclip_pos + totalVelocity
		
		element:SetPosition(noclip_pos)
		element:SetVelocity(totalVelocity * dtVec)
		
		if not isVehicle then
			local fwdCam = GetCameraForwardVector()
			local camAngle = math.atan(fwdCam.X,fwdCam.Z) + math.pi
		
			element:SetAngle(camAngle)
		end
	end
end

function step()
	if GetAsyncKeyState(noclip_togglekey1) ~= 0 and WasKeyPressedOnce(noclip_togglekey2) then
		toggle_noclip()
	end
	
	if (noclip_on and gameStarted) then
		step_noclip()
	end
end