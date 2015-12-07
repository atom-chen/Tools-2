--[[
    @brief 定时器，这个是不断增长的
]]

﻿local M = GlobalNS.Class(GlobalNS.IDelayHandleItem)
GlobalNS["TimerItemBase"] = M

function M:TimerItemBase()
{
    self.m_internal = 1;            -- 定时器间隔
    self.m_totalTime = 1;           -- 总共定时器时间
    self.m_curTime = 0;             -- 当前已经调用的定时器的时间
    self.m_bInfineLoop = false;     -- 是否是无限循环
    self.m_curLeftTimer = 0;        -- 当前定时器剩余的次数
    self.m_timerDisp = nil;         -- 定时器分发
    self.m_disposed = false;        -- 是否已经被释放
}

function OnTimer(delta)
    if self.m_disposed then
        return;
    end

    self.m_curTime += delta;
    self.m_curLeftTimer += delta;

    if self.m_bInfineLoop then
        self.checkAndDisp();
    else
        if m_curTime >= m_totalTime then
            self.disposeAndDisp();
        else
            self.checkAndDisp();
        end
    end
end

function disposeAndDisp()
    self.m_disposed = true;
    if self.m_timerDisp != nil then
        self.m_timerDisp(this);
    end
end

function checkAndDisp()
    if m_curLeftTimer >= m_internal then
    {
        m_curLeftTimer = m_curLeftTimer - m_internal;

        if (m_timerDisp != null)
        {
            m_timerDisp(this);
        }
    }
}

public virtual void reset()
{
    m_curTime = 0;
    m_curLeftTimer = 0;
    m_disposed = false;
}

public void setClientDispose()
{

}

public bool getClientDispose()
{
    return false;
}