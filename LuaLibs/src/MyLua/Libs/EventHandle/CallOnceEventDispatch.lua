--[[
    @brief 一次事件分发，分发一次就清理
]]

local M = GlobalNS.Class(GlobalNS.EventDispatch)
M.clsName = "CallOnceEventDispatch"
GlobalNS[M.clsName] = M

function M:ctor()

end

function M:dispatchEvent(dispatchObject)
    super.dispatchEvent(self, dispatchObject);
    selfclearEventHandle();
end

return M