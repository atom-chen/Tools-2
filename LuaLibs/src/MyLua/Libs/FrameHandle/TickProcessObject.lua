local M = GlobalNS.Class()
M.clsName = "TickProcessObject"
GlobalNS[M.clsName] = M

function M:ctor()
    self.m_tickObject = nil;
    self.m_priority = 0;
end

return M