local M = GlobalNS.Class()
GlobalNS["TickProcessObject"] = M

function M:ctor()
    self.m_tickObject = nil;
    self.m_priority = 0;
end

return M