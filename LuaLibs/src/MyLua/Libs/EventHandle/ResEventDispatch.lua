local M = GlobalNS.Class(GlobalNS.EventDispatch)
GlobalNS["ResEventDispatch"] = M

function M:ctor()
    
end

function M:dtor()

end

function M:dispatchEvent(dispatchObject)
    super.dispatchEvent(dispatchObject)
    self.clearEventHandle();
end

return M