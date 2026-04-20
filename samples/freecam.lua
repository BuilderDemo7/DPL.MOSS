--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	Free camera (debug fly camera) sample
--
-- Controls:
-- 	Keyboard -> NumPad
-- 	Controller #1 -> left analogic stick - movement, right analogic stick - rotation
--=====================================

freeCamOn = false
freeCamKey = VK_0 -- alphanumeric 0 key

function onToggleFreeCam()
	freeCamOn = not freeCamOn
	ToggleFreeCam(freeCamOn)
end

function stepFreeCamBtn()
	if (GetAsyncKeyState(freeCamKey) & 0x1 ~= 0) then -- if pushed once
		onToggleFreeCam()
	end
end

function step()
	stepFreeCamBtn()
end

function start()
	freeCamOn = false
end

function shutdown()
	freeCamOn = false
	--ToggleFreeCam(false) -- crashes the game, also it deletes interfaced classes every time it shutdowns automatically
end