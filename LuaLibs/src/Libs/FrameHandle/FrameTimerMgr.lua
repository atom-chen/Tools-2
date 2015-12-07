--[[
    @brief 定时器管理器
]]

local M = GlobalNS.Class(GlobalNS.DelayHandleMgrBase)
GlobalNS["FrameTimerMgr"] = M

function M:ctor()
    self.m_timerLists = GlobalNS.MList:new();
    self.m_delLists = GlobalNS.MList:new();
end

function addObject(delayObject, priority)
    -- 检查当前是否已经在队列中
    if self.m_timerLists.IndexOf(delayObject) == -1 then
        if self.bInDepth() then
            super.addObject(delayObject, priority);
        else
            m_timerLists.Add(delayObject as FrameTimerItem);
        end
    end
end

function delObject(delayObject)
    -- 检查当前是否在队列中
    if self.m_timerLists.IndexOf(delayObject) != -1 then
        delayObject.m_disposed = true;
        if self.bInDepth() then
            super.addObject(delayObject);
        else
            for key, item in ipairs(m_timerLists.list()) do
                if item == delayObject then
                    self.m_timerLists.Remove(item);
                    break;
                end
            end
        end
    end
end

function Advance(delta)
    self.incDepth();

    for key, timerItem in ipairs(m_timerLists.list()) do
        if not timerItem.getClientDispose() then
            timerItem.OnFrameTimer();
        end
        if timerItem.m_disposed then
            self.delObject(timerItem);
        end
    end

    self.decDepth();
end

return M