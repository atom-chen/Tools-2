local M = GlobalNS.Class(GlobalNS.EventDispatch)
M.clsName = "AddOnceAndCallOnceEventDispatch"
GlobalNS[M.clsName] = M

function M:ctor()
    
end

function M:addEventHandle(handle)
    if not self.existEventHandle(handle) then
        super.addEventHandle(self, handle)
    end
end

function M:dispatchEvent(dispatchObject)
    super.dispatchEvent(self, dispatchObject)
    self.clearEventHandle()
end

return M