--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	Sample for showing a text under the HUD minimap for when the player enters a new zone.
--=====================================

-- from = left-top corner of zone
-- to = right-bottom corner of zone
-- name = zone name
local zones = {
	-- [put on top of other districts to be detected properly in the table]
	{
		from = Vector.new(-2541.63, 320.84, -1039.99),
		to = Vector.new(-1566.69, 334.07, -450.83),
		name = "Edgewater"
	},
	{
		from = Vector.new(-2433.13, 261.95, -3653.44),
		to = Vector.new(-1116.62, 216.65, -2809.88),
		name = "Englewood"
	},
	{
		from = Vector.new(2146.230, 246.17, -1018.44),
		to = Vector.new(3268.52, 517.48, -249.83),
		name = "Steinway"
	},
	{
		from = Vector.new(2024.89, 306.28, 4232.02),
		to = Vector.new(3462.65, 616.94, 5000.06),
		name = "Coney"
	},
	{
		from = Vector.new(360.60, 403.10, 3927.43),
		to = Vector.new(1698.53, 510.16, 4665.08),
		name = "Redhook"
	},
	{
		from = Vector.new(2565.33, 279.57, 1537.83),
		to = Vector.new(3862.68, 399.21, 1765.04),
		name = "Long Island"
	},
	{
		from = Vector.new(-306.33, 336.88, 2199.98),
		to = Vector.new(196.24, 573.84, 3060.15),
		name = "Financial"
	},
	{
		from = Vector.new(0, 1052.26, -1885.70),
		to = Vector.new(802.59, 995.77, -416.87),
		name = "Central Park"
	},
	{
		from = Vector.new(637.93, 0, 1935.60),
		to = Vector.new(900.13, 0, 2304.06),
		name = "Chinatown"
	},
	{
		from = Vector.new(186.59, 170.31, 1073.75),
		to = Vector.new(839.35, 336.33, 1922.77),
		name = "Village"
	},
	{
		from = Vector.new(758.78, 380.09, -1890.77),
		to = Vector.new(1065.05, 447.96, -420.68),
		name = "Uptown"
	},
	{
		from = Vector.new(-482.25, 678.96, -170.37),
		to = Vector.new(1205.13, 748.72, 628.96),
		name = "Midtown"
	},
	{
		from = Vector.new(2056.33, 616.71, 1807.27),
		to = Vector.new(4052.88, 1552.97, 2970.77),
		name = "Jamaica"
	},	
	{
		from = Vector.new(4143.57, 13.22, -649.33),
		to = Vector.new(3584.61, 14, -462.63),
		name = "Rikers"
	},	

	----------------------------------------------

	{
		from = Vector.new(1994.87, 543.55, 106.35),
		to = Vector.new(3889.02, 277.07, 1331.55),
		name = "Queens"
	},
	{
		from = Vector.new(1914.02, 631.64, -4847.60),
		to = Vector.new(2747.86, 699.33, -3373.58),
		name = "Hunt's Point"
	},
	{
		from = Vector.new(3477.76, 921.72, -1918.82),
		to = Vector.new(4006.48, 949.42, -1313.04),
		name = "Riker's Island"
	},
	{
		from = Vector.new(3653.483, 958.43, -1123.01),
		to = Vector.new(5006.00, 1176.51, -407.97),
		name = "La Guardia"
	},
	{
		from = Vector.new(517.84, 431.10, -3712.35),
		to = Vector.new(1719.29, 464.01, -2729.20),
		name = "Bronx"
	},
	{
		from = Vector.new(-2564.23, 102.64, 1826.27),
		to = Vector.new(-1180.99, 34.75, 4496.349),
		name = "Jersey"
	},
	{
		from = Vector.new(-4109.49, 432.827, -1277.912),
		to = Vector.new(-1176.38, 176.34, 1787.79),
		name = "Kearny"
	},
	{
		from = Vector.new(-3260.84, 1023.35, -4054.60),
		to = Vector.new(-1111.62, 923.47, -1458.05),
		name = "New Jersey"
	},
	{
		from = Vector.new(-439.80, 1099.04, -2648.30),
		to = Vector.new(1776.94, 1073.87, -1968.76),
		name = "Harlem"
	},
	{
		from = Vector.new(-260.795, 21.60, -3319.15),
		to = Vector.new(171.36, 284.92, -2306.70),
		name = "Harlem"
	},
	{
		from = Vector.new(-168.70, 994.48, -398.51),
		to = Vector.new(1052.40, 931.56, 1212.15),
		name = "Manhattan"
	},
	{
		from = Vector.new(-388.799, 926.85, 1311.60),
		to = Vector.new(1143.734, 815.80, 2354.70),
		name = "Downtown"
	},
	{
		from = Vector.new(-310.30, 815.80, 2335.03),
		to = Vector.new(483.449, 768.780, 3536.59),
		name = "Downtown"
	},
	{
		from = Vector.new(475.96, 755.08, 3571.18),
		to = Vector.new(1877.18, 713.44, 4640.54),
		name = "Brooklyn"
	},
	{
		from = Vector.new(1824.45, 868.40, 3159.38),
		to = Vector.new(3988.24, 832.91, 4083.62),
		name = "Brooklyn"
	},
}

local currentZone = ""
local currentZone_text = ""

local gameStarted = false
local textSize = 0.75
local textX = -0.05
local textY = 0.9566

local textTypeIdx = 1
local textTypeMiniTimer = 0
local textTypePerSecond = 0.15

local textAnimTimer = 0
local textAnimTimer_max = 5
local textAnimTimer_fadeOut = 1
local textAnimTimer_fadeIn = textAnimTimer_max - 1

function start()
	gameStarted = true
end

function getCurrentZone()
	local pos = GetPlayerCharacter():GetPosition()
	local x,y,z = pos.X, pos.Y, pos.Z
	
	for i,zone in ipairs(zones) do	
		local x1,y1,z1 = zone.from.X,zone.from.Y,zone.from.Z
		local x2,y2,z2 = zone.to.X,zone.to.Y,zone.to.Z
		
		local minX, maxX = math.min(x1,x2), math.max(x1,x2)
		local minY, maxY = math.min(y1,y2), math.max(y1,y2)
		local minZ, maxZ = math.min(z1,z2), math.max(z1,z2)
		
		if (x >= minX and x <= maxX)
		   -- and (y >= minY and y <= maxY) -- Y is height so shouldn't count!
		   and (z >= minZ and z <= maxZ)
		then
			return zone.name, zone
		end
	end
	
	return nil
end

function onAreaChanged(oldArea, newArea)
	textTypeIdx = 1
	textTypeMiniTimer = 0
	currentZone_text = "" 
	textAnimTimer = textAnimTimer_max
	--print(oldArea,newArea)
end

function step()
	local newArea,_ = getCurrentZone()
	if newArea ~= currentZone and newArea ~= nil then
		local oldArea = currentZone
		currentZone = newArea
		onAreaChanged(oldArea,newArea)
		--print("onAreaChanged(oldArea,newArea)")
	end
	
	if (textAnimTimer > 0) then
		textAnimTimer = textAnimTimer - 0.008333
		--print(textAnimTimer)
		if (textAnimTimer < 0) then textAnimTimer = 0 end
	end
	
	if (GetEra() == Era_Now) then
		currentZone_text = string.sub(currentZone, 1, textTypeIdx)
		if (textTypeIdx < #currentZone) then
			textTypeMiniTimer = textTypeMiniTimer + 0.008333
			if (textTypeMiniTimer > textTypePerSecond) then
				textTypeMiniTimer = 0
				textTypeIdx = textTypeIdx + 1
			end
		end
	else
		currentZone_text = currentZone
	end
end

function draw_mission()
	if gameStarted then
		local alpha = 1.0
		local r,g,b = 1.0,1.0,0.25
		if (GetEra() == Era_Now) then
			b = 0.96
			
			r = 0.364
			g = 0.741
		end
		if (textAnimTimer > 0) then
			if (textAnimTimer <= textAnimTimer_fadeOut) then
				alpha = 1 - (textAnimTimer_fadeOut - textAnimTimer)
			end
			if (textAnimTimer >= textAnimTimer_fadeIn) then
				alpha = 1 - (textAnimTimer - textAnimTimer_fadeIn)
			end
		else
			alpha = 0.0
		end
	
		if (alpha > 0.001) then
			DrawText(string.format("%s", currentZone_text), textX, textY,   EJustify_Right,   textSize,  textSize,      r, g, b, alpha,   1)
		end
	end
end