--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	A basic sample showing the key input state.
--=====================================

-- helper functions
function isKeyDown(key)
    return GetAsyncKeyState(key) ~= 0
end

local fTime = 0
local thekey = VK_R -- VK means virtual key, which is a built-in enum/constant by MOSS
local firstPress = false
local firstRelease = false
local pressed = false

-- start() - called everytime the loading screen is finished and the player is ready for action
function start()
	print("Please press and hold R!")
end

-- step() - called every frame (when the game is unpaused)
function step()
	if (isKeyDown(thekey)) then
		pressed = true
		firstRelease = false
		if not firstPress then
			firstPress = true
			print("Hold it down as long as you want and I will tell you the time you held it")
		end
	else
		pressed = false	
		firstPress = false
		if not firstRelease then
			firstRelease = true
			fTime = 0
			print(string.format("You held down that key for %.1f seconds!", fTime))
		end
	end
	
	if (pressed) then
		fTime = fTime + 0.0166666667 -- increase the time, since there's no delta time we can use a constant number which is fine for the game's speed dependent system
	end
end