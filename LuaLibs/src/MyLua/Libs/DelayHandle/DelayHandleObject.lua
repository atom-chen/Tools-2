local M = GlobalNS.Class()
GlobalNS["DelayHandleObject"] = M

function M:ctor()
    self.m_delayObject = nil;
    self.m_delayParam = nil;
end

return M