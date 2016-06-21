﻿using System.IO;

namespace SDK.Lib
{
    /**
     * @brief 自定义打包文件加载
     */
    public class ABPakLoadItem : LoadItem
    {
        public MDataStream mDataStream = null;      // 文件流

        override public void reset()
        {
            base.reset();
        }

        override public void load()
        {
            base.load();

            string curPath = "";
            if (ResLoadType.eLoadStreamingAssets == m_resLoadType)
            {
                curPath = Path.Combine(MFileSys.getLocalReadDir(), m_loadPath);
            }
            else if (ResLoadType.eLoadLocalPersistentData == m_resLoadType)
            {
                curPath = Path.Combine(MFileSys.getLocalWriteDir(), m_loadPath);
            }
            mDataStream = new MDataStream(curPath);

            if (mDataStream != null)
            {
                m_nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
            }
            else
            {
                m_nonRefCountResLoadResultNotify.resLoadState.setFailed();
            }

            m_nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
        }
    }
}