-- test.lua

local obj = {
    string1 = "Hi! My name is LiXianlin",
    string2 = "aa\tbb\rcc\ndd\\ee\"ff",
    string3 = "a\\tb\\rc\\n\\\\ee\"ff",
    int = 9527,
    float = 3.1415,
    bool = true,
    array = {
        1, 2, 3,
        {
            a = 21,
            b = 22,
            c = 23,
        },
    },
    table = {
        x = 100,
        y = 200,
        w = 960,
        h = 640,
    },
    [88] = 88888,
    [9.7] = 22222,
}
print(debug.dump(obj))

--[[
{
	["string1"] = "Hi! My name is LiXianlin",
	[9.7] = 22222,
	["table"] = {
			["y"] = 200,
			["x"] = 100,
			["h"] = 640,
			["w"] = 960,
	},
	[88] = 88888,
	["string2"] = "aa\tbb\rcc\ndd\\ee\"ff",
	["int"] = 9527,
	["string3"] = "a\\tb\\rc\\n\\\\ee\"ff",
	["bool"] = true,
	["array"] = {
			1,
			2,
			3,
			{
					["b"] = 22,
					["a"] = 21,
					["c"] = 23,
			},
	},
	["float"] = 3.1415,
} 
--]]