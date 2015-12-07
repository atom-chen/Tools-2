local EventDispatchGroup = GlobalNS.Class()
local M = EventDispatchGroup

function M:ctor()
    self.m_groupID2DispatchDic = GlobalNS.Dictionary:new()
    self.m_bInLoop = false;
end

-- 添加分发器
function M:addEventDispatch(groupID, disp)
    if not self.m_groupID2DispatchDic.ContainsKey(groupID) then
        self.m_groupID2DispatchDic.Add(groupID, disp);
    end
end

function addEventHandle(groupID, handle)
    self.m_groupID2DispatchDic.value(groupID).addEventHandle(handle)
end

function removeEventHandle(groupID, handle)
    if self.m_groupID2DispatchDic.ContainsKey(groupID) then
        self.m_groupID2DispatchDic.value(groupID).removeEventHandle(handle)
    else
        -- 日志
    end
end

function dispatchEvent(groupID,  dispatchObject)
    self.m_bInLoop = true;
    if self.m_groupID2DispatchDic.ContainsKey(groupID) then
        self.m_groupID2DispatchDic.value(groupID).dispatchEvent(dispatchObject)
    else
        -- 日志
    end
    self.m_bInLoop = false;
end

function M:clearAllEventHandle()
    if not m_bInLoop then
        for _, dispatch in pairs(m_groupID2DispatchDic) do
            dispatch.clearEventHandle()
        end

        m_groupID2DispatchDic.Clear()
    else
        -- 日志
    end
end

function clearGroupEventHandle(groupID)
    if not self.m_bInLoop then
        if self.m_groupID2DispatchDic.ContainsKey(groupID) then
            self.m_groupID2DispatchDic.value(groupID).clearEventHandle();
            self.m_groupID2DispatchDic.Remove(groupID);
        else
            -- 日志
        end
    else
        -- 日志
    end
end

return M