--[[
    @brief 倒计时定时器
]]
local M = GlobalNS.Class(GlobalNS.TimerItemBase)
GlobalNS["DaoJiShiTimer"] = M

function M:ctor()

end

function OnTimer(delta)
    if self.m_disposed then
        return;
    end

    self.m_curTime = self.m_curTime - delta;
    self.m_curLeftTimer = self.m_curLeftTimer + delta;

    if self.m_bInfineLoop then
        self.checkAndDisp();
    else
        if self.m_curTime <= 0 then
            self.disposeAndDisp();
        else
            self.checkAndDisp();
        end
    end
end

function reset()
    self.m_curTime = m_totalTime;
    self.m_curLeftTimer = 0;
    self.m_disposed = false;
end

return M