-- globals.lua
-- show all global variables

local seen={}
local function_list={}
local function_count=0

function list_functions(t,i, prev)
    seen[t]=true
    local s={}
    local n=0
	local next_prev
    for k in pairs(t) do
        n=n+1 s[n]=k
    end
    table.sort(s)
	
    for k,v in ipairs(s) do
        if type(v)=="table" then
			next_prev = "" 
		else
			if string.len(prev) > 0 then
				function_list[function_count] = prev.."."..v
				function_count = function_count + 1
			end
			next_prev = v
		end
		v=t[v]
        if type(v)=="table" and not seen[v] then
            list_functions(v,i.."\t", next_prev)
        end
    end
end

function list_all_functions()
	list_functions(_G, "", "")
	return function_list
end