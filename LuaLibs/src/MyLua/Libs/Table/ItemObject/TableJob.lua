--[[
    @brief 职业表
]]

require "MyLua.Libs.Core.GlobalNS"

local M = GlobalNS.Class(GlobalNS.TableItemBodyBase)
M.clsName = "TableJobItemBody"
GlobalNS[M.clsName] = M

function M:ctor()
    self.m_jobName = "";                -- 职业名称
    self.m_jobDesc = "";                -- 职业描述
    self.m_frameImage = "";             -- 门派底图资源(这个是场景卡牌需要的资源)
    self.m_yaoDaiImage = "";            -- 卡牌名字腰带资源(这个是场景卡牌需要的资源)
    self.m_jobRes = "";                 -- 门派选择资源(门派名字资源是这个资源名字加上 __name 组成，例如这个名字是 aaa ，那么名字的资源名字就是 aaa_name)
    self.m_cardSetRes = "";             -- 门派卡组资源
    self.m_skillName = "";              -- 技能名称
    self.m_skillDesc = "";              -- 技能描述
    self.m_skillRes = "";               -- 技能图标资源
    
    self.m_jobNameRes = "";             -- 这个字段表中没有配置
    self.m_jobBtnRes = "";              -- 职业按钮资源
end

function M:parseBodyByteBuffer(bytes, offset)
    local UtilTable = nil
    bytes.position = offset;
    UtilTable.readString(bytes, m_jobName);
    UtilTable.readString(bytes, m_jobDesc);
    UtilTable.readString(bytes, m_frameImage);
    UtilTable.readString(bytes, m_yaoDaiImage);

    UtilTable.readString(bytes, m_jobRes);
    UtilTable.readString(bytes, m_cardSetRes);
    UtilTable.readString(bytes, m_skillName);
    UtilTable.readString(bytes, m_skillDesc);
    UtilTable.readString(bytes, m_skillRes);

    self.initDefaultValue();
end

function M:initDefaultValue()
    if (string.IsNullOrEmpty(m_frameImage)) then
        m_frameImage = "paidi_kapai";
    end
    if (string.IsNullOrEmpty(m_yaoDaiImage)) then
        m_yaoDaiImage = "mingzidi_kapai";
    end
    if (string.IsNullOrEmpty(m_cardSetRes)) then
        m_cardSetRes = "emei_taopai";
    end
    if (string.IsNullOrEmpty(m_skillRes)) then
        m_skillRes = "emeibiao_zhiye";
    end
    if (string.IsNullOrEmpty(m_jobRes)) then
        m_jobNameRes = "emei_zhiye";
        m_jobBtnRes = "gaibang_paizu";
    else
        m_jobNameRes = string.Format("{0}_name", m_jobRes);
        m_jobBtnRes = string.Format("{0}_btn", m_jobRes);
    end
    if (string.IsNullOrEmpty(m_jobRes)) then
        m_jobRes = "emei_zhiyepai";
    end
end

return M