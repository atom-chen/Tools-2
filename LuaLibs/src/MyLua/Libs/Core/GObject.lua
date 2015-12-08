-- 所有的类的基类

require "MyLua.Libs.Core.GlobalNS"

local M = {}
M.clsName = "GObject"
GlobalNS[M.clsName] = M

-- 
function M.__newindex(tbl, key, value)
    
end

return M