--[[
    @brief 
]]
local EventDispatchFunctionObject = GlobalNS.Class()
local M = EventDispatchFunctionObject

function M:ctor()
    self.m_bClientDispose = false       -- 是否释放了资源
    self.m_handle = nil
end

function M:dtor()

end

function M:setClientDispose()
    self.m_bClientDispose = true;
end

function M:getClientDispose()
    return m_bClientDispose;
end

return M