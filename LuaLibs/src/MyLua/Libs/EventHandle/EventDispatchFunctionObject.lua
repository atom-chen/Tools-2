--[[
    @brief 
]]
local M = GlobalNS.Class()
M.clsName = "EventDispatchFunctionObject"
GlobalNS[M.clsName] = M

function M:ctor()
    self.m_bClientDispose = false       -- 是否释放了资源
    self.m_handle = nil
    self.m_pThis = nil
end

function M:dtor()

end

function M:call(dispObj)
    if(nil ~= m_pThis and nil ~=  m_handle) then
        m_pThis:m_handle(dispObj);
    else
        m_handle(dispObj);
    end
end

function M:setClientDispose()
    self.m_bClientDispose = true;
end

function M:getClientDispose()
    return m_bClientDispose;
end

return M