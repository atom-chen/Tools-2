--[[
    @brief 定时器，这个是不断增长的
]]

local M = GlobalNS.Class(GlobalNS.IDelayHandleItem)
GlobalNS["FrameTimerItem"] = M

function M:ctor()
    self.m_internal = 1;
    self.m_totalFrameCount = 1;
    self.m_curFrame = 0;
    self.m_bInfineLoop = false;
    self.m_curLeftFrame = 0;
    self.m_timerDisp = nil;
    self.m_disposed = false;
end

function M:OnFrameTimer()
    if self.m_disposed then
        return;
    end

    ++self.m_curFrame;
    ++self.m_curLeftFrame;

    if self.m_bInfineLoop then
        if self.m_curLeftFrame == m_internal then
            self.m_curLeftFrame = 0;

            if self.m_timerDisp ~= nil then
                self.m_timerDisp(self);
            end
        end
    else
        if self.m_curFrame == self.m_totalFrameCount then
            self.m_disposed = true;
            if self.m_timerDisp ~= nil then
                self.m_timerDisp(this);
            end
        else
            if self.m_curLeftFrame == m_internal then
                self.m_curLeftFrame = 0;
                if self.m_timerDisp ~= nil then
                    self.m_timerDisp(this);
                end
            end
        end
    end
end

function M:reset()
    self.m_curFrame = 0;
    self.m_curLeftFrame = 0;
    self.m_disposed = false;
end

function M:setClientDispose()

end

function M:getClientDispose()
    return false;
end

return M