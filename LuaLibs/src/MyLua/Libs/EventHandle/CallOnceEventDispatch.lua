--[[
    @brief 一次事件分发，分发一次就清理
]]

local M = GlobalNS.Class(GlobalNS.EventDispatch)
GlobalNS["CallOnceEventDispatch"] = M

function M:ctor()

end

function M:dispatchEvent(dispatchObject)
    super.dispatchEvent(dispatchObject);
    selfclearEventHandle();
end

return M