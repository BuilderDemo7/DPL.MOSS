--=====================================
--	Sample by BuilderDemo7 (creator of MOSS)
--	
--	A sample that shows 7 different variants for drawing text
--=====================================

local gameStarted = false

function start()
	gameStarted = true
end

function draw_mission()
	if gameStarted then
		-- DrawText(text,   x,y,   align,    sx,sy,   r,g,b,a,   spacing,    w)
		DrawText("Left + aligned", 0, 0.5,   EJustify_Left,   1.0,  1.0,      1.0, 1.0, 1.0, 1.0,   1)
		DrawText("Right + aligned", 0, 0.5,   EJustify_Right,   1.0,  1.0,      1.0, 1.0, 1.0, 1.0,   1)
		
		DrawText("Spaced + centered", 0, 0.5,   EJustify_Centered,   1.0,  1.0,      1.0, 1.0, 1.0, 1.0,   5)
		DrawText("Red", 0, 0.6,   EJustify_Centered,   1.0,  1.0,      1.0, 0.0, 0.0, 1.0,   1)
		DrawText("Semi-transparent", 0, 0.7,   EJustify_Centered,   1.0,  1.0,      1.0, 1.0, 1.0, 0.5,   1)
		DrawText("Top + aligned", 0, 0,   EJustify_Centered,   1.0,  1.0,      1.0, 1.0, 1.0, 1.0,   1)
		DrawText("Bottom + aligned", 0, 0.9,   EJustify_Centered,   1.0,  1.0,      1.0, 1.0, 1.0, 1.0,   1)
	end
end