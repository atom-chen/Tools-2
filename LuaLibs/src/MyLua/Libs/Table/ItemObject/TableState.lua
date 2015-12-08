local M = GlobalNS.Class(GlobalNS.TableItemBodyBase)
M.clsName = "TableStateItemBody"
GlobalNS[M.clsName] = M

function M:ctor()
    self.m_name = "";           -- 名称
    self.m_res = "";            -- 资源
    self.m_effectId = 0;        -- 特效 Id
end

function M:parseBodyByteBuffer(bytes, offset)
    local UtilTable = nil 
    bytes.position = offset;
    UtilTable.readString(bytes, m_name);
    UtilTable.readString(bytes, m_res);
    bytes.readInt32(m_effectId);

    self.initDefaultValue();
end

function M:initDefaultValue()
    if(m_effectId == 0) then
        m_effectId = 0;
    end
end

return M