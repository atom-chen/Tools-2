local DelayHandleObject = GlobalNS.Class()
local M = DelayHandleObject

function M:ctor()
    self.m_delayObject = nil;
    self.m_delayParam = nil;
end

return M