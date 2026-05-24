--=====================================
--	Script by BuilderDemo7 (creator of MOSS)
--	
-- 2 players script for Driver: Parallel Lines
--
-- Controls:
-- 		Alpha 6 -> Toggle 2P mode
-- 		Alpha 5 -> Restore 2P camera
-- 		Alpha 4 -> Bring P2 to P1
-- 		J key -> Turn camera to right
-- 		K key -> Turn camera to left
-- P2 Controls (keyboard-only, can be changed in g_2p_bindings table):
--		Forwards -> Up arrow
--		Left -> Left arrow
--		Backwards -> Down arrow
--		Right -> Right arrow
--		
--		Enter/Exit Vehicle -> O key
--		Handbrake -> Y
--		Horn -> T
--		Nitro -> Alpha 8
--		Action1 (release hooked tow-truck car) -> Alpha 9
--=====================================

-- Settings/variables

mode_2p = false
g_2p_skin = 0x59 -- Ray (then) as player two
g_2p_togglekey = VK_6
g_2p_restoreCamkey = VK_5
g_2p_bringPlayerTwoKey = VK_4
g_2p_character = nil
g_2p_initialVehicle = nil
g_p1actor = nil -- player 1 actor

g_2p_cam = nil
g_2p_camSelect = nil
	
g_2p_cameraMaxDistance = 100-23.3	
g_2p_cameraDisableAreaLimit = false -- for debugging only, true = on, false = off

g_2p_cameraAutoAdjustYaw = true
g_2p_cameraAdjustDistance = 12.5	
g_2p_cameraAdjustSpeed = 0.03	

g_2p_cameraDontAdjustTimer = 0
g_2p_cameraDontAdjustTimerMax = 5

g_2p_cameraMaxHeight = 125	
g_2p_cameraMinHeight = 12.5	
g_2p_cameraOffHeight = 0
g_2p_cameraOffHeight_Ride = 10
g_2p_cameraOffHeight_Vehicle = 5

g_2p_cameraTiltAngle = 33.3	
g_2p_cameraTiltAngle_VehicleOffset = 8	
g_2p_cameraYawAngle = 392 -- in degrees, use 392 for facing north or 180 for inverting angle
g_2p_cameraInvertTiltAngle = false
g_2p_cameraInvertYawAngle = false

g_2p_bindings = {
	forward = VK_UP,
	left = VK_LEFT,
	backward = VK_DOWN,
	right = VK_RIGHT,
	
	car_enter_exit = VK_O,
	
	car_handbrake = VK_Y,
	car_horn = VK_H,
	car_nitro = VK_8,
	car_action1 = VK_9,
}

-- helper func
function lerp(a,b,t)
	return a + (b - a) * t
end

function lerpVec(a,b,t)
	local x = lerp(a.X,b.X,t)
	local y = lerp(a.Y,b.Y,t)
	local z = lerp(a.Z,b.Z,t)
	return Vector.new(x,y,z)
end

-- 2P mode

function create2Pcharacter()
	local plrChara = GetPlayerCharacter()
	local pos = Vector.new(0,0,0)
	local health = 1.0
	if plrChara ~= nil then
		pos = plrChara:GetPosition()
		health = plrChara:GetHealth()
	end

	if g_2p_character == nil then
		local ignorePlayerRegister = true
		local isPlayer = false
		local spawnDist = 1
		
		-- when player one is in a vehicle, make them spawn in a vehicle too
		if (plrChara:GetVehicle() ~= nil) or g_2p_initialVehicle ~= nil then
			spawnDist = 5
			g_2p_initialVehicle = CreateVehicle(53, pos.X+spawnDist,pos.Y,pos.Z+spawnDist, 0, false, 1, 1)
		end
		g_2p_character = CreateCharacter(g_2p_skin, pos.X+spawnDist,pos.Y,pos.Z+spawnDist, 0, false, 0, health, 0.0, g_2p_initialVehicle, 0, 0.5, true, false, isPlayer, ignorePlayerRegister, false, 1)
	end
end

function init2Pmode()
	local plrChara = GetPlayerCharacter()
	local pos = Vector.new(0,0,0)
	if plrChara ~= nil then
		pos = plrChara:GetPosition()
	end

	RequestEntity(SpooledPackageType_CharacterSkins, g_2p_skin, ESpoolPriority_Required)
	
	-- hack: disable ExitVehicle on character life instances
	memwrite(0x436b58, "\x90\x90\x90\x90\x90\x90\x90\x90\x90", 9)
	
	g_2p_cam = CreateCamera(pos, Quaternion.FromEuler(0, 0, 0), nil, nil) -- default camera position
	g_2p_camSelect = CreateCameraSelect(ECameraSelectType_CameraActor, g_2p_cam)
	
	create2Pcharacter()
end

function start2Pmode()
	local plrChara = GetPlayerCharacter()
	local pos = Vector.new(0,0,0)
	if plrChara ~= nil then
		pos = plrChara:GetPosition()
	end

	if (g_2p_character ~= nil) then
		g_2p_character:SetPosition(pos + Vector.new(1, 0, 1))
		g_2p_character:Instantiate()
	end

	create2Pcharacter() -- create if needed

	if (g_2p_initialVehicle ~= nil) then
		g_2p_initialVehicle:Instantiate()
	end
	
	if (g_2p_character:GetLifeInstance() ~= nil) then
		local linst = g_2p_character:GetLifeInstance()
		
		print("g_2p_character:GetLifeInstance() ->",string.format("%.8X",linst:GetPointer()))
	end
	if (g_p1actor ~= nil) then
		if (g_p1actor:GetLifeInstance() ~= nil) then
			local linst = g_p1actor:GetLifeInstance()
		
			print("g_p1actor:GetLifeInstance() ->",string.format("%.8X",linst:GetPointer()))
		end
	end
	
	-- use ObjVisibility_MinimapAndModel for debugging!
	local visi = ObjVisibility_MinimapOnly
	g_2p_character:AddObjectiveIcon(DisplayType_POSITIONMARKERCONE, visi, true)
	
	g_2p_camSelect:Enable()
end

-- unused stuff, maybe can be done later ...
local minimap_camPos = Vector.new(0,0,0)
local minimap_camAngle = 0
function step2Pmode_cameraMinimap(vinBetweenPos, yawAngle)
	local cMapItem = GetCameraMapItem()
	
	if cMapItem ~= nil then
		minimap_camPos = vinBetweenPos
		minimap_camAngle = math.rad(yawAngle+180)
		
		cMapItem:SetPosition(minimap_camPos)
		cMapItem:SetAngle(minimap_camAngle)
	end
end

-- unused
-- may lag I think
--function draw_mission()
--	if mode_2p then
--		local cMapItem = GetCameraMapItem()
--	
--		if cMapItem ~= nil then
--			cMapItem:SetPosition(minimap_camPos)
--			cMapItem:SetAngle(minimap_camAngle)
--		end	
--	end
--end

function step2Pmode_camera()
	local pos1 = GetPlayerCharacter():GetPosition()
	local pos2 = g_2p_character:GetPosition()

	local inBetweenPos = lerpVec(pos1,pos2,0.5)

	local dist = GetDistanceBetweenPoints3D(pos1.X,pos1.Y,pos1.Z,pos2.X,pos2.Y,pos2.Z)
	local height = dist
	if (height > g_2p_cameraMaxHeight) then height = g_2p_cameraMaxHeight end
	if (height < g_2p_cameraMinHeight) then height = g_2p_cameraMinHeight end
	
	local p1VehPtr = 0
	local p2VehPtr = 1
	local p1Veh = GetPlayerCharacter():GetVehicle()
	local p2Veh = g_2p_character:GetInstance():GetVehicle()
	if (p1Veh ~= nil) then
		p1VehPtr = p1Veh:GetPointer()
	end
	if (p2Veh ~= nil) then
		p2VehPtr = p2Veh:GetPointer()
	end
	
	height = height + g_2p_cameraOffHeight
	
	local tiltAngle = g_2p_cameraInvertTiltAngle and -g_2p_cameraTiltAngle or g_2p_cameraTiltAngle
	local YawAngle = g_2p_cameraInvertYawAngle and -g_2p_cameraYawAngle or g_2p_cameraYawAngle
	
	-- if both players are in the same vehicle
	if (p1VehPtr == p2VehPtr) then
		height = height + g_2p_cameraOffHeight_Ride
		tiltAngle = tiltAngle - 15
		if (tiltAngle < 10) then tiltAngle = 10 end
	elseif (p1VehPtr ~= 0) and (p2VehPtr ~= 1) then -- else if both are in different cars
		height = height + g_2p_cameraOffHeight_Vehicle
		tiltAngle = tiltAngle - g_2p_cameraTiltAngle_VehicleOffset
		if (tiltAngle < 10) then tiltAngle = 10 end
	end
	
	local tiltVec = Vector.new(math.sin(math.rad(YawAngle)), math.sin(math.rad(tiltAngle)), math.cos(math.rad(YawAngle)))
	--local tiltVec = Vector.new(0, math.sin(math.rad(tiltAngle)), math.cos(math.rad(tiltAngle)))
	--local yawVec = Vector.new(math.sin(math.rad(YawAngle)), 0, math.cos(math.rad(YawAngle)))
	
	local camPos = (inBetweenPos + (tiltVec * Vector.new(height, height, height)))
	
	g_2p_cam:SetPosition(camPos)
	g_2p_cam:SetRotation(Quaternion.FromEuler(YawAngle, -tiltAngle, 0))
	
	if (g_2p_cameraAutoAdjustYaw) and g_2p_cameraDontAdjustTimer <= 0.001 then
		local fwd = GetCameraForwardVector()
		
		local posDot1 = pos1 - inBetweenPos
		--local posDot2 = pos2 - inBetweenPos
		
		local dot1 = (posDot1.X*fwd.X + posDot1.Y*fwd.Y + posDot1.Z*fwd.Z)
		--local dot2 = (posDot2.X*fwd.X + posDot2.Y*fwd.Y + posDot2.Z*fwd.Z)
		
		local frontPlayer = nil
		if (dot1 > 0) then
			frontPlayer = g_2p_character:GetInstance()
		end
		if dot1 < 0 then
			frontPlayer = GetPlayerCharacter()
		end
		
		if frontPlayer ~= nil then
			local fPos = frontPlayer:GetPosition()
			
			local distBetweenCenter = GetDistanceBetweenPoints3D(fPos.X,fPos.Y,fPos.Z,inBetweenPos.X,inBetweenPos.Y,inBetweenPos.Z)
			if (distBetweenCenter > g_2p_cameraAdjustDistance) then
				--if frontPlayer:GetPointer() == g_2p_character:GetInstance():GetPointer() then
				--	print("frontPlayer = p2", dot1)
				--else
				--	print("frontPlayer = p1", dot1)
				--end
			
				local toAngle = math.atan(inBetweenPos.X-fPos.X,inBetweenPos.Z-fPos.Z)
				local fromAngle = math.rad(g_2p_cameraYawAngle)
				local newAngle = lerp(fromAngle,toAngle,g_2p_cameraAdjustSpeed)
				
				g_2p_cameraYawAngle = math.deg(newAngle)
			end
		end
	end
	
	-- unused
	--step2Pmode_cameraMinimap(inBetweenPos, YawAngle)
end

function step2Pmode_cameraLimit()
	local pos1 = GetPlayerCharacter():GetPosition()
	local pos2 = g_2p_character:GetPosition()

	local inBetweenPos = lerpVec(pos1,pos2,0.5)

	local cmFwd = GetCameraForwardVector()
	local cmRgt = GetCameraRightVector()

	local maxDist = g_2p_cameraMaxDistance
	
	local dist = GetDistanceBetweenPoints3D(pos1.X,pos1.Y,pos1.Z,pos2.X,pos2.Y,pos2.Z)
	local p1DistFromCam = GetDistanceBetweenPoints3D(pos1.X,pos1.Y,pos1.Z, inBetweenPos.X,inBetweenPos.Y,inBetweenPos.Z)
	local p2DistFromCam = GetDistanceBetweenPoints3D(pos2.X,pos2.Y,pos2.Z, inBetweenPos.X,inBetweenPos.Y,inBetweenPos.Z)
	local throwBackVel1 = inBetweenPos - pos1 
	local throwBackVel2 = inBetweenPos - pos2 
	local throwBackVel1_normal = Vector.new(throwBackVel1.X / throwBackVel1.MagnitudeSqr,throwBackVel1.Y / throwBackVel1.MagnitudeSqr,throwBackVel1.Z / throwBackVel1.MagnitudeSqr)
	local throwBackVel2_normal = Vector.new(throwBackVel2.X / throwBackVel2.MagnitudeSqr,throwBackVel2.Y / throwBackVel2.MagnitudeSqr,throwBackVel2.Z / throwBackVel2.MagnitudeSqr)
	
	local throwBackCarSpeed = g_2p_cameraMaxDistance / 2.5
	local throwBackOnfootSpeed = 2
	
	if (p1DistFromCam > maxDist+0.2) then
		local plrChara = GetPlayerCharacter()
		local veh = plrChara:GetVehicle()
		
		if (veh ~= nil) then
			veh:SetVelocity(throwBackVel1_normal * Vector.new(throwBackCarSpeed,throwBackCarSpeed,throwBackCarSpeed))
		else
			plrChara:SetPosition(plrChara:GetPosition() + (throwBackVel1_normal  * Vector.new(throwBackOnfootSpeed,throwBackOnfootSpeed,throwBackOnfootSpeed)))
		end
	end
	if (p2DistFromCam > maxDist+0.12) then
		local plrChara = g_2p_character:GetInstance()
		if plrChara ~= nil then
			local veh = plrChara:GetVehicle()
		
			if (veh ~= nil) then
				veh:SetVelocity(throwBackVel2_normal * Vector.new(throwBackCarSpeed,throwBackCarSpeed,throwBackCarSpeed))
			else
				plrChara:SetPosition(plrChara:GetPosition() + (throwBackVel2_normal * Vector.new(throwBackOnfootSpeed,throwBackOnfootSpeed,throwBackOnfootSpeed)))
			end
		end
	end
end

function step2Pmode()
	if g_2p_character ~= nil then
		local l2p_charaInst = g_2p_character:GetInstance()
	
		local cmFwd = GetCameraForwardVector()
		local cmRgt = GetCameraRightVector()
		
		if l2p_charaInst ~= nil then
			local veh = l2p_charaInst:GetVehicle()
		
			local fwd = (GetAsyncKeyState(g_2p_bindings.forward) ~= 0) and 1 or 0
			local bcd = (GetAsyncKeyState(g_2p_bindings.backward) ~= 0) and 1 or 0
			local lft = (GetAsyncKeyState(g_2p_bindings.left) ~= 0) and 1 or 0
			local rgt = (GetAsyncKeyState(g_2p_bindings.right) ~= 0) and 1 or 0
		
			local backforward = fwd > 0 and fwd or -bcd
			local leftright = lft > 0 and lft or -rgt
			if veh == nil then
				local vel1 = cmFwd * Vector.new(backforward, backforward, backforward)
				local vel2 = cmRgt * Vector.new(leftright, leftright, leftright)
			
				local exitenter = (GetAsyncKeyState(g_2p_bindings.car_enter_exit) ~= 0)
			
				if (exitenter) then
					local entryVeh,eDoor = FindClosestVehicleForEntry(l2p_charaInst)
					if eDoor == nil then eDoor = 0 end
					
					if (entryVeh ~= nil) then
						local p1VehPtr = 0
						local p1Veh = GetPlayerCharacter():GetVehicle()
						if (p1Veh ~= nil) then
							p1VehPtr = p1Veh:GetPointer()
						end
						local hijack = entryVeh:GetPointer() ~= p1VehPtr
						if (eDoor == 0) then -- if driver seat/door
							hijack = true
						end
						l2p_charaInst:EnterVehicle(entryVeh, tonumber(eDoor), hijack)
					end
				end
			
				local allVel = vel1+vel2
				if (math.abs(backforward) > 0.001 or math.abs(leftright) > 0.001) then
					local velVec = Vector.new(-allVel.X, 0, -allVel.Z) -- velocity without height (Y axis) + inverted Z
					
					l2p_charaInst:Walk(velVec * Vector.new(120, 120, 120), false, false, 120)
				
					-- hack: move player by position lol
					local angle = velVec.Heading
					l2p_charaInst:SetAngle(angle)
					l2p_charaInst:SetPosition(l2p_charaInst:GetPosition() + (velVec * Vector.new(0.05, 0.05, 0.05)))
				end
			else
				local nitro = (GetAsyncKeyState(g_2p_bindings.car_nitro) ~= 0)
				local handbrake = (GetAsyncKeyState(g_2p_bindings.car_handbrake) ~= 0)
				local action1 = (GetAsyncKeyState(g_2p_bindings.car_action1) ~= 0)
				local horn = (GetAsyncKeyState(g_2p_bindings.car_horn) ~= 0)
			
				local exitenter = (GetAsyncKeyState(g_2p_bindings.car_enter_exit) ~= 0)
				if exitenter then
					l2p_charaInst:ExitVehicle()
				end
			
				veh:SendManipulationPacket(backforward, -leftright, 0, 0, horn and 1 or 0, nitro, handbrake, false, action1)
				veh:SetPhysicsPriority(1) -- player priority
			end
			
			step2Pmode_camera()
		end
		if not g_2p_cameraDisableAreaLimit then
			step2Pmode_cameraLimit()
		end
	end
end

function shutdown2Pmode()
	g_2p_camSelect:Disable()

	if (g_2p_initialVehicle ~= nil) then
		g_2p_initialVehicle:Delete()
	end

	if (g_2p_character ~= nil) then
		g_2p_character:RemoveObjectiveIcon(DisplayType_POSITIONMARKERCONE, ObjVisibility_MinimapOnly, true)
		g_2p_character:Delete()
	end
end

function restore2Pcamera()
	g_2p_camSelect:Disable()
	g_2p_camSelect:Enable()
end

function bringSecondPlayerToPlayerOne()
	local plrChara = GetPlayerCharacter()
	local pos = plrChara:GetPosition()

	if g_2p_character ~= nil then
		local l2p_charaInst = g_2p_character:GetInstance()
		
		if l2p_charaInst ~= nil then
			local veh = l2p_charaInst:GetVehicle()
			if (veh ~= nil) then
				veh:SetVelocity(Vector.new(0,0.5,0))
				veh:SetPosition(pos + Vector.new(5,0,5))
			end
		end
		
		g_2p_character:SetPosition(pos + Vector.new(1,0,1))
	end
end

function toggle2Pmode()
	mode_2p = not mode_2p
	if mode_2p then
		print("start2Pmode()")
		start2Pmode()
	else
		print("shutdown2Pmode()")
		shutdown2Pmode()
	end
end

function start()
	print("--- 2 PLAYERS MODE SCRIPT - START ---")

	g_p1actor = GetPlayerActor()

	if (GetEra() == Era_Now) then 
		g_2p_skin = 0xAA -- Ray (now) as player two
	end
	
	init2Pmode()
end

function step()
	if mode_2p then
		step2Pmode()
	end
	
	if (g_2p_cameraDontAdjustTimer > 0) then
		g_2p_cameraDontAdjustTimer = g_2p_cameraDontAdjustTimer - 0.0166666
		if (g_2p_cameraDontAdjustTimer < 0) then
			g_2p_cameraDontAdjustTimer = 0
		end
	end
	
	if GetAsyncKeyState(g_2p_togglekey) & 0x1 ~= 0 then
		print("toggle2Pmode()")
		toggle2Pmode()
	end
	if GetAsyncKeyState(g_2p_restoreCamkey) & 0x1 ~= 0 then
		print("restore2Pcamera()")
		restore2Pcamera()
	end
	if GetAsyncKeyState(g_2p_bringPlayerTwoKey) & 0x1 ~= 0 then
		print("bringSecondPlayerToPlayerOne()")
		bringSecondPlayerToPlayerOne()
	end
	
	if GetAsyncKeyState(VK_J) ~= 0 then
		g_2p_cameraYawAngle = g_2p_cameraYawAngle - 0.5
		g_2p_cameraDontAdjustTimer = g_2p_cameraDontAdjustTimerMax
	end
	if GetAsyncKeyState(VK_K) ~= 0 then
		g_2p_cameraYawAngle = g_2p_cameraYawAngle + 0.5
		g_2p_cameraDontAdjustTimer = g_2p_cameraDontAdjustTimerMax
	end
	
	-- debug
	--if GetAsyncKeyState(VK_H) ~= 0 then
		--print(tostring(g_2p_cameraYawAngle))
	--end
end

function shutdown()
	print("--- 2 PLAYERS MODE SCRIPT - SHUT DOWN ---")
	mode_2p = false
end