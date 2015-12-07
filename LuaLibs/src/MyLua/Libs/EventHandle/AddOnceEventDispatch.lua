--[[
    @brief 事件回调函数只能添加一次
]]

local M = GlobalNS.Class(GlobalNS.EventDispatch)
GlobalNS["AddOnceEventDispatch"] = M

function M:ctor(eventId_)
    
end

function M:addEventHandle(handle)
    -- 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
    if not self.existEventHandle(handle) then
        super.addEventHandle(handle);
    end
end

return M