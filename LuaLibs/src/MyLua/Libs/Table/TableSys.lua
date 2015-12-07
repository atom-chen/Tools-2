--[[
 * @brief 添加一个表的步骤总共分 4 步
 * // 添加一个表的步骤一
 * // 添加一个表的步骤二
 * // 添加一个表的步骤三
 * // 添加一个表的步骤四
]]

local M = GlobalNS.Class()
GlobalNS["TableSys"] = M

function M:ctor()
	self.m_dicTable = GlobalNS.Dictionary:new();
    self.m_dicTable.Add(GlobalNS.TableID.TABLE_OBJECT, GlobalNS.TableBase:new("ObjectBase_client.bytes", "ObjectBase_client"));
    self.m_dicTable.Add(GlobalNS.TableID.TABLE_CARD, GlobalNS.TableBase:new("CardBase_client.bytes", "CardBase_client"));
    self.m_dicTable.Add(GlobalNS.TableID.TABLE_SKILL, GlobalNS.TableBase:new("SkillBase_client.bytes", "SkillBase_client"));    -- 添加一个表的步骤三
    self.m_dicTable.Add(GlobalNS.TableID.TABLE_JOB, GlobalNS.TableBase:new("proBase_client.bytes", "proBase_client"));
    self.m_dicTable.Add(GlobalNS.TableID.TABLE_SPRITEANI, GlobalNS.TableBase:new("FrameAni_client.bytes", "FrameAni_client"));
    self.m_dicTable.Add(GlobalNS.TableID.TABLE_RACE, GlobalNS.TableBase:new("RaceBase_client.bytes", "RaceBase_client"));
    self.m_dicTable.Add(GlobalNS.TableID.TABLE_STATE, GlobalNS.TableBase:new("StateBase_client.bytes", "StateBase_client"));
end

-- 返回一个表
function getTable(tableID)
	table = m_dicTable.value(tableID);
	if (nil == table) then
		self.loadOneTable(tableID);
		table = m_dicTable[tableID];
	end
	return table.m_List;
end

-- 返回一个表中一项，返回的时候表中数据全部加载到 Item 中
function M:getItem(tableID, itemID)
    table = m_dicTable.value(tableID);
    if (nil == table.m_byteBuffer) then
		self.loadOneTable(tableID);
		table = m_dicTable[tableID];
	end
    ret = M.findDataItem(table, itemID);

    if (nil ~= ret and nil == ret.m_itemBody) then
        self.loadOneTableOneItemAll(tableID, table, ret);
    end

    if (nil == ret) then
        -- 日志
    end

	return ret;
end

-- 加载一个表
function loadOneTable(tableID)
	table = m_dicTable.value(tableID);

    LoadParam param = Ctx.m_instance.m_poolSys.newObject<LoadParam>();
    LocalFileSys.modifyLoadParam(Path.Combine(Ctx.m_instance.m_cfg.m_pathLst[(int)ResPathType.ePathTablePath], table.m_resName), param);
    param.m_loadEventHandle = onLoadEventHandle;
    param.m_loadNeedCoroutine = false;
    param.m_resNeedCoroutine = false;
    Ctx.m_instance.m_resLoadMgr.loadResources(param);
    Ctx.m_instance.m_poolSys.deleteObj(param);
end

-- 加载一个表完成
public void onLoadEventHandle(IDispatchObject dispObj)
{
    m_res = dispObj as ResItem;
    if (m_res.refCountResLoadResultNotify.resLoadState.hasSuccessLoaded())
    {
        Ctx.m_instance.m_logSys.debugLog_1(LangItemID.eItem0, m_res.GetPath());

        byte[] bytes = m_res.getBytes("");
        if (bytes != null)
        {
            m_byteArray = Ctx.m_instance.m_factoryBuild.buildByteBuffer();
            m_byteArray.clear();
            m_byteArray.writeBytes(bytes, 0, (uint)bytes.Length);
            m_byteArray.setPos(0);
            readTable(getTableIDByPath(m_res.GetPath()), m_byteArray);
        }
    }
    else if (m_res.refCountResLoadResultNotify.resLoadState.hasFailed())
    {
        Ctx.m_instance.m_logSys.debugLog_1(LangItemID.eItem1, m_res.GetPath());
    }

    // 卸载资源
    Ctx.m_instance.m_resLoadMgr.unload(m_res.GetPath(), onLoadEventHandle);
}

-- 根据路径查找表的 ID
function getTableIDByPath path)
    for key, value in pairs(m_dicTable) do
        if (Ctx.m_instance.m_cfg.m_pathLst[(int)ResPathType.ePathTablePath] + kv.Value.m_resName == path) then
            return kv.Key;
        end
    end

    return 0;
end

-- 加载一个表中一项的所有内容
function void loadOneTableOneItemAll(TableID tableID, TableBase table, TableItemBase itemBase)
{
    if (TableID.TABLE_OBJECT == tableID)
    {
        itemBase.parseBodyByteBuffer<TableObjectItemBody>(table.m_byteBuffer, itemBase.m_itemHeader.m_offset);
    }
    else if (TableID.TABLE_CARD == tableID)
    {
        itemBase.parseBodyByteBuffer<TableCardItemBody>(table.m_byteBuffer, itemBase.m_itemHeader.m_offset);
    }
    else if (TableID.TABLE_SKILL == tableID)  // 添加一个表的步骤四
    {
        itemBase.parseBodyByteBuffer<TableSkillItemBody>(table.m_byteBuffer, itemBase.m_itemHeader.m_offset);
    }
    else if (TableID.TABLE_JOB == tableID)
    {
        itemBase.parseBodyByteBuffer<TableJobItemBody>(table.m_byteBuffer, itemBase.m_itemHeader.m_offset);
    }
    else if (TableID.TABLE_SPRITEANI == tableID)
    {
        itemBase.parseBodyByteBuffer<TableSpriteAniItemBody>(table.m_byteBuffer, itemBase.m_itemHeader.m_offset);
    }
    else if (TableID.TABLE_RACE == tableID)
    {
        itemBase.parseBodyByteBuffer<TableRaceItemBody>(table.m_byteBuffer, itemBase.m_itemHeader.m_offset);
    }
    else if (TableID.TABLE_STATE == tableID)
    {
        itemBase.parseBodyByteBuffer<TableStateItemBody>(table.m_byteBuffer, itemBase.m_itemHeader.m_offset);
    }
}

// 获取一个表的名字
function string getTableName(TableID tableID)
{
	TableBase table = m_dicTable[tableID];
	if (null != table)
	{
		return table.m_tableName;
	}			
	return "";
}

// 读取一个表，仅仅读取表头
function void readTable(TableID tableID, ByteBuffer bytes)
{
    TableBase table = m_dicTable[tableID];
    table.m_byteBuffer = bytes;

    bytes.setEndian(EEndian.eLITTLE_ENDIAN);
    uint len = 0;
    bytes.readUnsignedInt32(ref len);
    uint i = 0;
    TableItemBase item = null;
    for (i = 0; i < len; i++)
    {
        //if (TableID.TABLE_OBJECT == tableID)
        //{
        //    item = new TableItemObject();
        //}
        item = new TableItemBase();
        item.parseHeaderByteBuffer(bytes);
        // 加载完整数据
        //loadOneTableOneItemAll(tableID, table, item);
        //if (TableID.TABLE_OBJECT == tableID)
        //{
            //item.parseAllByteBuffer<TableObjectItemBody>(bytes);
        //}
        table.m_List.Add(item);
    }
}

// 查找表中的一项
function public TableItemBase findDataItem(TableBase table, uint id)
{
	int size = table.m_List.Count;
	int low = 0;
	int high = size - 1;
	int middle = 0;
	uint idCur = 0;
	
	while (low <= high)
	{
		middle = (low + high) / 2;
        idCur = table.m_List[middle].m_itemHeader.m_uID;
		if (idCur == id)
		{
			break;
		}
		if (id < idCur)
		{
			high = middle - 1;
		}
		else
		{
			low = middle + 1;
		}
	}
	
	if (low <= high)
	{
        return table.m_List[middle];
	}
	return null;
}