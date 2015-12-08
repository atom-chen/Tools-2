require "MyLua.Libs.Core.GlobalNS"

local M = GlobalNS.Class()
M.clsName = "ITickedObject"
GlobalNS[M.clsName] = M

function M:onTick(delta)

end

return M