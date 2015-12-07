-- package.path = string.format("%s;%s/?.lua", package.path, "D:/File/OpenSource/Unity/Tools/LuaLibs/src")
package.path = string.format("%s;%s/?.lua", package.path, "E:/Self/Self/Tools/Tools/LuaLibs/src")
require "Libs.Core.Prerequisites"

local function main()
    -- testArray()
    -- testLen()
    testFuncEnv()
end

function testArray()
    array = GlobalNS.Array:new()
    array:add(1)
    array:add(2)
    array:add(3)
    
    array:remove(2)
end

function testLen()
    local tbs = {}
    tbs = {[2] = 1}
    tbs["aaa"] = "bbb"
    local len = #tbs
    len = table.getn(tbs)
    print(len)
end

function testFuncEnv()
    require "TestEnv.TestEnv"
    local aaa = 411
end

main()