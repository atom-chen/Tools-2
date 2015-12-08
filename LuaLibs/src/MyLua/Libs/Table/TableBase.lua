require "MyLua.Libs.Core.GlobalNS"

local M = GlobalNS.Class()
M.clsName = "TableBase"
GlobalNS[M.clsName] = M

function M:ctor(resName, tablename)
    m_resName = resName;
    m_tableName = tablename;                -- 表的名字

    m_List = GlobalNS.TableItemBase:new();
    m_byteBuffer = nil;      -- 整个表格所有的原始数据
end

return M