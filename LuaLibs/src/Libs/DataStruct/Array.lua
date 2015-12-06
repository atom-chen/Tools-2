--[[
    @brief 数组实现，类实现，数组的下标从 0 开始，但是 lua 中数组的下标从 1 开始
]]

local Array = GlobalNS.Class()
local M = Array

function M:ctor()
    self.m_data = {}
end

function M:dtor()

end

function M:getLen()
    if self.m_data ~= nil then
        return table.getn(self.m_data)
    end
    
    return 0
end

function M:add(value)
    self.m_data[self:getLen() + 1] = value
end

function M:remove(value)
    local idx = 1
    while( idx < self:getLen() + 1 )
    do
        if self.m_data[idx] == value then
            table.remove(self.m_data, idx)
            break;
        end
        idx = idx + 1
    end
end

return M