local M = GlobalNS.Class()
GlobalNS["UtilTable"] = M

function M:ctor()
    self.m_prePos = 0;        -- 记录之前的位置
    self.m_sCnt = 0
end

function M:readString(bytes, tmpStr)
    bytes.readUnsignedInt16(m_sCnt);
    bytes.readMultiByte(tmpStr, m_sCnt, GkEncode.UTF8);
end

return M