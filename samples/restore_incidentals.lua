--=====================================
--	Script by BuilderDemo7 (creator of MOSS)
--	
-- Script that restores incidentals in free-roam or mostly in any condition.
--=====================================

local gameStarted = false
local timer_incidental = 0
local timer_genStep = 0.008333

function start()
	gameStarted = true
	EnableIncidentalSpooling()
end

function step()
	-- silly every 1 minute it will re-enable incidentals :P
	if gameStarted then
		timer_incidental = timer_incidental + timer_genStep
		if timer_incidental >= 60 then
			EnableIncidentalSpooling()
		end
	end
end