--[[
    @brief 精灵动画配置
]]
local M = GlobalNS.Class(GlobalNS.TableItemBodyBase)
M.clsName = "TableSpriteAniItemBody"
GlobalNS[M.clsName] = M

function M:ctor()
    self.m_frameRate = 0;     -- 帧率 FPS，每秒帧数
    self.m_frameCount = 0;    -- 帧数，总共多少帧
    self.m_aniResNameNoExt = ""; -- 动画资源的名字，没有扩展名
    
    self.m_invFrameRate = 0;    -- 一帧需要的时间
    self.m_aniResName = "";     -- 动画资源的名字，有扩展名
    self.m_aniPrefabName = "";  -- 动画预制资源
end

function M:parseBodyByteBuffer(bytes, offset)
    bytes.position = offset;
    bytes:readInt32(m_frameRate);
    bytesLreadInt32(m_frameCount);
    UtilTable.readString(bytes, m_aniResNameNoExt);

    m_invFrameRate = 1 / m_frameRate;
    m_aniResName = string.Format("{0}.asset", m_aniResNameNoExt);

    m_aniPrefabName = string.Format("{0}prefab.prefab", m_aniResNameNoExt);
end

return M