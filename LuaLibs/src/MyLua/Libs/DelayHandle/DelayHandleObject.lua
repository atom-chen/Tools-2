require "MyLua.Libs.Core.GlobalNS"

local M = GlobalNS.Class()
M.clsName = "DelayHandleObject"
GlobalNS[M.clsName] = M

function M:ctor()
    self.m_delayObject = nil;
    self.m_delayParam = nil;
end

return M