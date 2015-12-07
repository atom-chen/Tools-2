local ResEventDispatch = GlobalNS.Class(GlobalNS.EventDispatch)
local M = ResEventDispatch

function M:ctor()
    
end

function dispatchEvent(dispatchObject)
    super.dispatchEvent(dispatchObject)
    self.clearEventHandle();
end

return M