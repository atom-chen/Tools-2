﻿using System.Collections;
using System.Collections.Generic;

namespace SDK.Lib
{
    public class ResLoadData
    {
        // 因为资源有些需要协同程序，因此重复利用资源
        public Dictionary<string, LoadItem> m_path2LDItem;       // 正在加载的内容 loaditem
        public ArrayList m_willLDItem;                           // 将要加载的 loaditem
        public ArrayList m_noUsedLDItem;                         // 没有被使用的 loaditem
        public Dictionary<string, ResItem> m_path2Res;
        public ArrayList m_noUsedResItem;                         // 没有被使用的 Res

        public ResLoadData()
        {
            m_path2LDItem = new Dictionary<string, LoadItem>();
            m_path2Res = new Dictionary<string, ResItem>();
            m_willLDItem = new ArrayList();
            m_noUsedLDItem = new ArrayList();
            m_noUsedResItem = new ArrayList();
        }
    }
}