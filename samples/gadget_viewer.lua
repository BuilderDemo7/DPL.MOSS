local gadgets = {
    { id = _11DRUGBOX, name = "_11DRUGBOX" },
    { id = _2BOX, name = "_2BOX" },
    { id = _1BOMB, name = "_1BOMB" },
    { id = _1BOMBNOW, name = "_1BOMBNOW" },
    { id = _2BRIEFCASE, name = "_2BRIEFCASE" },
    { id = AR10, name = "AR10" },
    { id = ARMOUREDCAR, name = "ARMOUREDCAR" },
    { id = BERETTA, name = "BERETTA" },
    { id = BINBIGBLUE, name = "BINBIGBLUE" },
    { id = BULLPUP, name = "BULLPUP" },
    { id = CHEVRON36MSTRAIGHT, name = "CHEVRON36MSTRAIGHT" },
    { id = CIRCUITRACE, name = "CIRCUITRACE" },
    { id = CONECONED, name = "CONECONED" },
    { id = DESERTEAGLE, name = "DESERTEAGLE" },
    { id = DESTRUCTIONDERBY, name = "DESTRUCTIONDERBY" },
    { id = DRIVERGP, name = "DRIVERGP" },
    { id = FENCELARGEPLYWOOD4M, name = "FENCELARGEPLYWOOD4M" },
    { id = GLOCK18, name = "GLOCK18" },
    { id = GRENADE, name = "GRENADE" },
    { id = GRENADELAUNCHER, name = "GRENADELAUNCHER" },
    { id = HealthPack_Now, name = "HealthPack_Now" },
    { id = HEALTHPACK_Then, name = "HEALTHPACK_Then" },
    { id = HELICOPTER_NOW, name = "HELICOPTER_NOW" },
    { id = HELICOPTER_THEN, name = "HELICOPTER_THEN" },
    { id = HELICOPTERBLACK, name = "HELICOPTERBLACK" },
    { id = HELICOPTERCIV, name = "HELICOPTERCIV" },
    { id = HITMAN, name = "HITMAN" },
    { id = LOANSHARK, name = "LOANSHARK" },
    { id = MACHINEGUNMUZZLEFLASH, name = "MACHINEGUNMUZZLEFLASH" },
    { id = MAGNUM, name = "MAGNUM" },
    { id = MainRotor, name = "MainRotor" },
    { id = MINIGUN, name = "MINIGUN" },
    { id = MOTOCROSS, name = "MOTOCROSS" },
    { id = MP7, name = "MP7" },
    { id = NITROFLASH, name = "NITROFLASH" },
    { id = P90, name = "P90" },
    { id = PERFECTDELIVERY, name = "PERFECTDELIVERY" },
    { id = PISTOLMUZZLEFLASH, name = "PISTOLMUZZLEFLASH" },
    { id = POSITIONMARKERCONE, name = "POSITIONMARKERCONE" },
    { id = POSITIONMARKERFLARE, name = "POSITIONMARKERFLARE" },
    { id = POSITIONMARKERSHORTFAT, name = "POSITIONMARKERSHORTFAT" },
    { id = POSITIONMARKERSHORTSKINNY, name = "POSITIONMARKERSHORTSKINNY" },
    { id = POSITIONMARKERTALLFAT, name = "POSITIONMARKERTALLFAT" },
    { id = POSITIONMARKERTALLSKINNY, name = "POSITIONMARKERTALLSKINNY" },
    { id = PRISONTRANSPORT, name = "PRISONTRANSPORT" },
    { id = RAMP, name = "RAMP" },
    { id = REPOMAN, name = "REPOMAN" },
    { id = REVOLVER, name = "REVOLVER" },
    { id = ROADWORKBARRIER4M, name = "ROADWORKBARRIER4M" },
    { id = ROADWORKSMALLBARRIER, name = "ROADWORKSMALLBARRIER" },
    { id = ROCKET, name = "ROCKET" },
    { id = ROCKETLAUNCHER, name = "ROCKETLAUNCHER" },
    { id = SAFEHOUSE, name = "SAFEHOUSE" },
    { id = SHOTGUN, name = "SHOTGUN" },
    { id = SLINKSPACKAGE2, name = "SLINKSPACKAGE2" },
    { id = SPEEDGUN, name = "SPEEDGUN" },
    { id = STICKUP, name = "STICKUP" },
    { id = STREETRACE, name = "STREETRACE" },
    { id = STYER, name = "STYER" },
    { id = SURVIVAL, name = "SURVIVAL" },
    { id = TailRotor, name = "TailRotor" },
    { id = TAXI, name = "TAXI" },
    { id = Token, name = "Token" },
    { id = TRAIN, name = "TRAIN" },
    { id = UZI, name = "UZI" },
    { id = UZIMUZZLEFLASH, name = "UZIMUZZLEFLASH" },
    { id = VEDIT, name = "VEDIT" },
    { id = VENDERDONUTS, name = "VENDERDONUTS" },
    { id = VENDERFOOD, name = "VENDERFOOD" },
}

local gadget_selector_format = "%s %d(%.4X)"
local gadget_selector_format_small = "%s"

local gadget_selector_togglekey = VK_F2
local gadget_selector_prevkey = VK_LEFT
local gadget_selector_nextkey = VK_RIGHT

local gadget_selector_spawnkey = VK_Q
local gadget_selector_deletekey = VK_E

local gadget_selector_currentgadgetidx = 1
local gadget_selector_currentgadget = gadgets[gadget_selector_currentgadgetidx].id
local gadget_selector_prop = nil

local gadget_selector_on = false
local gadget_selector_propcreated = false

local function FindGadgetName(id)
    for _, g in ipairs(gadgets) do
        if g.id == id then
            return g.name
        end
    end
    return "UNKNOWN"
end

function InitGadgetSelector()
	if (gadget_selector_prop == nil) then
		local plr = GetPlayerCharacter()
	
		if (plr ~= nil) then
			local pos = plr:GetPosition()
			
			gadget_selector_prop = CreateProp(pos, gadget_selector_currentgadget, Quaternion.new(0,0,0,0), false, false)
		end
	end
end

function ShutdownGadgetSelector()
	if(gadget_selector_prop ~= nil) then
		gadget_selector_prop:Delete()
	end
end

function UpdateGadgetSelector_Text()
	local text = string.format(gadget_selector_format, FindGadgetName(gadget_selector_currentgadget), gadget_selector_currentgadget, gadget_selector_prop:GetModelHandle())
	local text_small = string.format(gadget_selector_format_small, FindGadgetName(gadget_selector_currentgadget))
	ShowMissionComment(10, text_small)
	print(text)
end

function UpdateGadgetProp()
	gadget_selector_prop:Delete()
	gadget_selector_prop:SetGadgetType(gadget_selector_currentgadget)
	if (gadget_selector_propcreated) then
		local plr = GetPlayerCharacter()
		gadget_selector_prop:SetPosition(plr:GetPosition())
		gadget_selector_prop:Instantiate()
	end
end

function NextGadget()
	gadget_selector_currentgadgetidx = gadget_selector_currentgadgetidx + 1;
	if (gadget_selector_currentgadgetidx > #gadgets) then
		gadget_selector_currentgadgetidx = 1
	end
	gadget_selector_currentgadget = gadgets[gadget_selector_currentgadgetidx].id
	UpdateGadgetSelector_Text()
	UpdateGadgetProp()
end

function PreviousGadget()
	gadget_selector_currentgadgetidx = gadget_selector_currentgadgetidx - 1;
	if (gadget_selector_currentgadgetidx <= 0) then
		gadget_selector_currentgadgetidx = #gadgets
	end
	gadget_selector_currentgadget = gadgets[gadget_selector_currentgadgetidx].id
	UpdateGadgetSelector_Text()
	UpdateGadgetProp()
end

function CreateGadget()
	gadget_selector_prop:Create()
	gadget_selector_propcreated = true
end

function DeleteGadget()
	gadget_selector_prop:Delete()
	gadget_selector_propcreated = false
end

function UpdateGadgetSelector()
	if (GetAsyncKeyState(gadget_selector_nextkey) & 0x1 ~= 0) then
		NextGadget()
	end
	if (GetAsyncKeyState(gadget_selector_prevkey) & 0x1 ~= 0) then
		PreviousGadget()
	end
	if (GetAsyncKeyState(gadget_selector_spawnkey) & 0x1 ~= 0) then
		print("CreateGadget()")
		CreateGadget()
	end
	if (GetAsyncKeyState(gadget_selector_deletekey) & 0x1 ~= 0) then
		print("DeleteGadget()")
		DeleteGadget()
		
	end
end

function step()
	if (gadget_selector_on) then
		UpdateGadgetSelector()
	end

	if (GetAsyncKeyState(gadget_selector_togglekey) & 0x1 ~= 0) then
		gadget_selector_on = not gadget_selector_on
		
		if (gadget_selector_on) then
			ShowMissionComment(2, "GADGET SELECTOR ON")
			InitGadgetSelector()
		else
			ShowMissionComment(2, "GADGET SELECTOR OFF")
			ShutdownGadgetSelector()
		end
	end
end