--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
-- Spinning camera sample for testing custom cameras, some of them doesn't support velocity, so movement interpolation is a little bit weird sometimes.
--=====================================

local ourCam = nil
local cam_gameStarted = false
local degYaw = 0
local camDist = 3.0
local camHeight = 2.0

function start()
	degYaw = 0

	local plrActor = GetPlayerActor()

	ourCam = CreateCamera(plrActor:GetPosition() + Vector.new(0,2,0), Quaternion.FromEuler(0, 0, 0), nil, nil) -- default camera position
	local cSelect = CreateCameraSelect(ECameraSelectType_CameraActor, ourCam)
	
	cSelect:Enable() -- activate the camera
	
	print(ourCam)
	print(string.format("%.8X", ourCam:GetPointer()))
	
	cam_gameStarted = true
end

function step()
	if cam_gameStarted then
		local playerChara = GetPlayerCharacter()
		if (playerChara ~= nil) and ourCam ~= nil then
			local pos = playerChara:GetPosition() + Vector.new(math.sin(math.rad(degYaw)) * camDist, camHeight, math.cos(math.rad(degYaw)) * camDist)
			
			-- pose the camera
			ourCam:SetPosition(pos)
			ourCam:SetRotation(Quaternion.FromEuler(degYaw, -25, 0))
		end
		
		degYaw = degYaw + 0.25
	end
end

function shutdown()
	cam_gameStarted = false
end