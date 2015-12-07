local AddOnceAndCallOnceEventDispatch = GlobalNS.Class(GlobalNS.EventDispatch)
local M = AddOnceAndCallOnceEventDispatch

function M:ctor()
    
end

function M:addEventHandle(handle)
    if not self.existEventHandle(handle) then
        super.addEventHandle(handle)
    end
end

function M:dispatchEvent(dispatchObject)
    super.dispatchEvent(dispatchObject)
    self.clearEventHandle()
end

return M