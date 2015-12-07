--[[
    @brief 心跳管理器
]]

﻿local M = GlobalNS.Class(GlobalNS.DelayHandleMgrBase)
GlobalNS["TickMgr"] = M

function M:ctor()
{
    self:m_tickLst = GlobalNS.MList:new();
}

function M:addTick(tickObj, priority)
    self.addObject(tickObj, priority);
end

function M:addObject(delayObject, priority)
    if self.bInDepth() then
        super.addObject(delayObject, priority);
    else
        local position = -1;
        local i = 0
        for (i = 0, i < m_tickLst.Count, 1) do
            if m_tickLst[i] == nil then
                continue;
            end

            if m_tickLst[i].m_tickObject == delayObject then
                return;
            end

            if m_tickLst[i].m_priority < priority then
                position = i;
                break;
            end
        end

        processObject = GlobalNS.TickProcessObject:new();
        processObject.m_tickObject = delayObject;
        processObject.m_priority = priority;

        if position < 0 or position >= m_tickLst.Count then
            self.m_tickLst.Add(processObject);
        else
            self.m_tickLst.Insert(position, processObject);
        end
    end
end

function delObject(delayObject)
    if self.bInDepth() then
        super.delObject(delayObject);
    else
        for key, item in ipairs(m_tickLst.list()) do
            if item.m_tickObject == delayObject then
                self.m_tickLst.Remove(item);
                break;
            end
        end
    end
end

function Advance(delta)
    self.incDepth();

    for key, tk in ipairs(m_tickLst.list()) do
        if not tk.m_tickObject.getClientDispose() then
            tk.m_tickObject.onTick(delta);
        end
    end

    self.decDepth();
}

return M