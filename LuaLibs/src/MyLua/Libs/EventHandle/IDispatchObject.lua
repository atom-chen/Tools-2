--[[
    @brief 可分发的对象
]]

require "MyLua.Libs.Core.GlobalNS"
require "MyLua.Libs.EventHandle.EventDispatch"

local M = GlobalNS.Class(GlobalNS.EventDispatch)
M.clsName = "IDispatchObject"
GlobalNS[M.clsName] = M

function M:ctor()

end

return M