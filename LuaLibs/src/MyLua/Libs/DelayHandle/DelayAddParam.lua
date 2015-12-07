local M = GlobalNS.Class(GlobalNS.DelayHandleParamBase)
GlobalNS["DelayAddParam"] = M

function M:ctor()
    self.m_priority = 0;
end

return M