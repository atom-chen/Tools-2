--[[
    @brief 一次事件分发，分发一次就清理
]]

local CallOnceEventDispatch = GlobalNS.Class(GlobalNS.EventDispatch)
local M = CallOnceEventDispatch

function M:ctor()

end

function dispatchEvent(dispatchObject)
    super.dispatchEvent(dispatchObject);
    selfclearEventHandle();
end

return M