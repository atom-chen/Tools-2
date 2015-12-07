--[[
    @brief 事件分发器
]]

local M = GlobalNS.Class()
GlobalNS["EventDispatch"] = M

function M:ctor(eventId_)
    self.m_eventId = eventId_
    self.m_handleList = GlobalNS.MList:new()
    self.m_uniqueId = 0       -- 唯一 Id ，调试使用
end

function M:dtor()

end

function M:getHandleList()
    return self.m_handleList;
end

function M:getUniqueId()
    return self.m_uniqueId;
end

function M:setUniqueId(value)
    self.m_uniqueId = value;
    --self.m_handleList.uniqueId = m_uniqueId;
end

function M:addEventHandle(handle)
    local funcObject = GlobalNS.EventDispatchFunctionObject:new()
    funcObject.m_handle = handle;
    if (nil ~= handle) then
        self.addObject(funcObject);
    else
        -- 日志
    end
end

function M:addObject(delayObject, priority)
    if self.bInDepth() then
        super.addObject(delayObject, priority);
    else
        -- 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
        self.m_handleList.Add(delayObject);
    end
end

function M:removeEventHandle(handle)
    local idx = 0;
    for idx = 0, idx < self.m_handleList.Count(), 1 do
        if self.m_handleList.at(idx).m_handle == handle then
            break;
        end
    end
    if idx < self.m_handleList.Count() then
        self.delObject(self.m_handleList[idx]);
    else
        -- 日志
    end
end

function M:delObject(delayObject)
    if self.bInDepth() then
        super.delObject(delayObject);
    else
        if self.m_handleList.Remove(delayObject) == false then
            -- 日志
        end
    end
end

function M:dispatchEvent(dispatchObject)
    self.incDepth();

    for _, handle in ipairs(self.m_handleList.list()) do
        if handle.m_bClientDispose == false then
            handle.m_handle(dispatchObject);
        end
    end

    self.decDepth();
end

function M:clearEventHandle()
    if (self.bInDepth()) then
        for _, item in ipairs(self.m_handleList.list()) do
            self.delObject(item);
        end
    else
        m_handleList.Clear();
    end
end

-- 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
function M:existEventHandle(handle)
    local bFinded = false;
    for _, item in ipairs(self.m_handleList.list()) do
        if (UtilApi.isAddressEqual(item.m_handle, handle)) then
            bFinded = true;
            break;
        end
    end

    return bFinded;
end

function M:copyFrom(rhv)
    for _, handle in ipairs(rhv.handleList.list()) do
        self.m_handleList.Add(handle);
    end
end

return M