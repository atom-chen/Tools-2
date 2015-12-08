-- 静态类

require "MyLua.Libs.Core.GlobalNS"

local M = {}
M.clsName = "StaticClass"
GlobalNS[M.clsName] = M

-- 
function M:ctor()
    
end

return M