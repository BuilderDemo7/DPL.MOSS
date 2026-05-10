--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	Sample for playing a sound effect when the player presses LCtrl + N
--=====================================

local gameStarted = false
local audio = nil

function start()
	gameStarted = true
	print("audio play test -> start!!")
	RequestEntity(SpooledPackageType_Audio, 0, ESpoolPriority_Required)
	
	audio = CreateAudio(0, 3,     1.0, false, nil) -- audio bank ID - 0, audio sample ID - 3
end

function step()
	if gameStarted then
		if (GetAsyncKeyState(VK_LCONTROL) ~= 0 and GetAsyncKeyState(VK_N) & 0x1 ~= 0) then
			if audio ~= nil then
				audio:Play() -- play the audio
				print("audio:Play()")
				if not IsEntityLoaded(SpooledPackageType_Audio, 0) then
					RequestEntity(SpooledPackageType_Audio, 0, ESpoolPriority_Required)
				end
			end
		end
	end
end