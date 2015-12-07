local M = GlobalNS.Class()
GlobalNS["SystemTimeData"] = M

function M:ctor()
    self.m_preTime = 0              -- 上一次更新时的秒数
    self.m_curTime = 0              -- 正在获取的时间
    self.m_deltaSec = 0             -- 两帧之间的间隔
end

function getDeltaSec()
    return m_deltaSec
end

function setDeltaSec(value)
    m_deltaSec = value
end

function getCurTime()
    return m_curTime
end

function setCurTime(value)
    m_curTime = value;
end

function nextFrame()
    m_preTime = m_curTime;
end

return M