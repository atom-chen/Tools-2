﻿
using System.Collections;
using System.IO;
using UnityEngine;

namespace SDK.Lib
{
    /**
     * @brief 用户数据加载 Item
     */
    public class DataLoadItem : LoadItem
    {
        public byte[] mBytes;
        protected TextAsset mTextAsset;
        protected MDataStream mDataStream;

        public override void reset()
        {
            mBytes = null;
            base.reset();
        }

        override public void load()
        {
            base.load();

            string fullLoadPath = "";

            if (ResLoadType.eLoadResource == m_resLoadType)  // 如果从 Resources 加载
            {
                if (m_loadNeedCoroutine)
                {
                    Ctx.m_instance.m_coroutineMgr.StartCoroutine(loadFromDefaultAssetBundleByCoroutine());
                }
                else
                {
                    loadFromDefaultAssetBundle();
                }
            }
            else if(ResLoadType.eLoadStreamingAssets == m_resLoadType ||
                    ResLoadType.eLoadLocalPersistentData == m_resLoadType)
            {
                fullLoadPath = ResPathResolve.msDataStreamLoadRootPathList[(int)m_resLoadType] + "/" + m_loadPath;

                if (ResLoadType.eLoadStreamingAssets == m_resLoadType)
                {
                    Ctx.m_instance.m_logSys.log(string.Format("DataLoadItem::load, ResLoadType is {0}, ResPackType is {1}, Load Not Need Coroutine, fullLoadPath is {2}", "LoadStreamingAssets", "Data", fullLoadPath), LogTypeId.eLogResLoader);
                }
                else
                {
                    Ctx.m_instance.m_logSys.log(string.Format("DataLoadItem::load, ResLoadType is {0}, ResPackType is {1}, Load Not Need Coroutine, fullLoadPath is {2}", "LoadLocalPersistentData", "Data", fullLoadPath), LogTypeId.eLogResLoader);
                }

                // 暂时只支持同步加载
                mDataStream = new MDataStream(fullLoadPath, onFileOpened);
            }
            else if (ResLoadType.eLoadWeb == m_resLoadType)
            {
                Ctx.m_instance.m_logSys.log(string.Format("DataLoadItem::load, ResLoadType is {0}, ResPackType is {1}, Load Not Need Coroutine, m_origPath is {2}", "LoadWeb", "Data", m_origPath), LogTypeId.eLogResLoader);

                // Web 服务器加载
            }
        }

        // 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
        override public void unload()
        {
            if(mTextAsset != null)
            {
                UtilApi.UnloadAsset(mTextAsset);
                mTextAsset = null;
            }
            mBytes = null;
            base.unload();
        }

        // Resources.Load就是从一个缺省打进程序包里的AssetBundle里加载资源，而一般AssetBundle文件需要你自己创建，运行时动态加载，可以指定路径和来源的。
        protected void loadFromDefaultAssetBundle()
        {
            Ctx.m_instance.m_logSys.log(string.Format("DataLoadItem::loadFromDefaultAssetBundle, ResLoadType is {0}, ResPackType is {1}, Load Not Need Coroutine, m_origPath is {2}", "LoadResource", "Data", m_origPath), LogTypeId.eLogResLoader);

            bool isSuccess = false;
            mTextAsset = Resources.Load<TextAsset>(m_loadPath);
            if (mTextAsset != null)
            {
                mBytes = mTextAsset.bytes;
                isSuccess = true;
            }

            if (isSuccess)
            {
                m_nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
            }
            else
            {
                m_nonRefCountResLoadResultNotify.resLoadState.setFailed();
            }
            m_nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
        }

        protected IEnumerator loadFromDefaultAssetBundleByCoroutine()
        {
            Ctx.m_instance.m_logSys.log(string.Format("DataLoadItem::loadFromDefaultAssetBundleByCoroutine, ResLoadType is {0}, ResPackType is {1}, Load Need Coroutine, m_loadPath is {2}", "LoadResource", "Data", m_loadPath), LogTypeId.eLogResLoader);

            ResourceRequest req = Resources.LoadAsync<TextAsset>(m_loadPath);
            yield return req;

            if (req.asset != null && req.isDone)
            {
                mTextAsset = req.asset as TextAsset;
                mBytes = mTextAsset.bytes;
                m_nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
            }
            else
            {
                m_nonRefCountResLoadResultNotify.resLoadState.setFailed();
            }
          
            m_nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
        }

        protected void onFileOpened(IDispatchObject dispObj)
        {
            mDataStream = dispObj as MDataStream;   // 因为返回之前就回调了，因此这里需要赋值一下，然后才能使用 mDataStream
            if (mDataStream.isValid())
            {
                mBytes = mDataStream.readByte();
            }
            mDataStream.dispose();
            mDataStream = null;

            if(mBytes != null)
            {
                Ctx.m_instance.m_logSys.log(string.Format("DataLoadItem::onFileOpened, m_origPath is {0}, Open Success", m_origPath), LogTypeId.eLogResLoader);

                m_nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
            }
            else
            {
                Ctx.m_instance.m_logSys.log(string.Format("DataLoadItem::onFileOpened, m_origPath is {0}, Open Failed", m_origPath), LogTypeId.eLogResLoader);

                m_nonRefCountResLoadResultNotify.resLoadState.setFailed();
            }

            m_nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
        }
    }
}