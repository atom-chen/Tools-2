﻿using System.Collections;
using UnityEngine;

namespace SDK.Lib
{
    /**
     * @brief 支持从本地和 Web 服务器加载场景和场景 Bundle 资源 ，采用 WWW 下载
     */
    public class LevelLoadItem : LoadItem
    {
        protected string m_levelName;

        public string levelName
        {
            get
            {
                return m_levelName;
            }
            set
            {
                m_levelName = value;
            }
        }

        override public void load()
        {
            base.load();
            if(ResLoadType.eLoadResource == m_resLoadType)
            {
                Ctx.m_instance.m_logSys.log(string.Format("LevelLoadItem::load, ResLoadType is {0}, ResPackType is {1}, Load Not Need Coroutine, m_origPath is {2}", "LoadResource", "Level", m_origPath), LogTypeId.eLogResLoader);

                m_nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
                m_nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
            }
            else if (ResLoadType.eLoadStreamingAssets == m_resLoadType ||
                ResLoadType.eLoadLocalPersistentData == m_resLoadType)
            {
                // 需要加载 AssetBundles 加载
                if (m_loadNeedCoroutine)
                {
                    Ctx.m_instance.m_coroutineMgr.StartCoroutine(loadFromAssetBundleByCoroutine());
                }
                else
                {
                    loadFromAssetBundle();
                }
            }
            else if (ResLoadType.eLoadWeb == m_resLoadType)
            {
                Ctx.m_instance.m_logSys.log(string.Format("LevelLoadItem::load, ResLoadType is {0}, ResPackType is {1}, Load Not Need Coroutine, m_origPath is {2}", "LoadWeb", "Level", m_origPath), LogTypeId.eLogResLoader);

                Ctx.m_instance.m_coroutineMgr.StartCoroutine(downloadAsset());
            }
        }

        override public void unload()
        {
            base.unload();
        }

        protected IEnumerator loadFromAssetBundleByCoroutine()
        {
            string path = "";
            // UNITY_5_2 没有
            //AssetBundleCreateRequest req = null;

#if UNITY_5_0 || UNITY_5_1 || UNITY_5_2
            //byte[] bytes = Ctx.m_instance.m_fileSys.LoadFileByte(path);
            //req = AssetBundle.CreateFromMemory(bytes);
            //yield return req;

            // UNITY_5_2 没有异步从文件加载的 LoadFromFileAsync 接口，只有从内存异步加载的 CreateFromMemory 接口，因此直接使用 WWW 读取，就不先从文件系统将二进制读取进来，然后再调用 CreateFromMemory 了，不知道 WWW 和 从文件系统读取二进制再 CreateFromMemory 哪个更快。
            WWW www = null;
            path = ResPathResolve.msFileLoadRootPathList[(int)m_resLoadType] + "/" + m_loadPath;
            www = new WWW(path);
            yield return www;
            m_assetBundle = www.assetBundle;

            www.Dispose();
            www = null;
#else
            AssetBundleCreateRequest req = null;

            path = ResPathResolve.msABLoadRootPathList[(int)m_resLoadType] + "/" + m_loadPath;

            if (m_resLoadType == ResLoadType.eLoadStreamingAssets)
            {
                Ctx.m_instance.m_logSys.log(string.Format("LevelLoadItem::loadFromAssetBundleByCoroutine, ResLoadType is {0}, ResPackType is {1}, Load Need Coroutine, FullPath is {2}", "LoadStreamingAssets", "Level", path), LogTypeId.eLogResLoader);
            }
            else
            {
                Ctx.m_instance.m_logSys.log(string.Format("LevelLoadItem::loadFromAssetBundleByCoroutine, ResLoadType is {0}, ResPackType is {1}, Load Need Coroutine, FullPath is {2}", "LoadLocalPersistentData", "Level", path), LogTypeId.eLogResLoader);
            }

            req = AssetBundle.LoadFromFileAsync(path);
            yield return req;

            m_assetBundle = req.assetBundle;
#endif

            assetAssetBundlesLevelLoaded();
        }

        protected void loadFromAssetBundle()
        {
            string path = "";
            path = ResPathResolve.msABLoadRootPathList[(int)m_resLoadType] + "/" + m_loadPath;

            if (m_resLoadType == ResLoadType.eLoadStreamingAssets)
            {
                Ctx.m_instance.m_logSys.log(string.Format("LevelLoadItem::loadFromAssetBundle, ResLoadType is {0}, ResPackType is {1}, Load Not Need Coroutine, FullPath is {2}", "LoadStreamingAssets", "Level", path), LogTypeId.eLogResLoader);
            }
            else
            {
                Ctx.m_instance.m_logSys.log(string.Format("LevelLoadItem::loadFromAssetBundle, ResLoadType is {0}, ResPackType is {1}, Load Not Need Coroutine, FullPath is {2}", "LoadLocalPersistentData", "Level", path), LogTypeId.eLogResLoader);
            }

            // UNITY_5_2 没有
#if UNITY_5_0 || UNITY_5_1 || UNITY_5_2
            m_assetBundle = AssetBundle.CreateFromFile(path);
#else
            m_assetBundle = AssetBundle.LoadFromFile(path);
#endif
            assetAssetBundlesLevelLoaded();
        }

        protected void assetAssetBundlesLevelLoaded()
        {
            if (m_assetBundle != null)
            {
                Ctx.m_instance.m_logSys.log(string.Format("LevelLoadItem::assetAssetBundlesLevelLoaded, Level Load Success, Path is {0}", m_origPath), LogTypeId.eLogResLoader);

                m_nonRefCountResLoadResultNotify.resLoadState.setSuccessLoaded();
            }
            else
            {
                Ctx.m_instance.m_logSys.log(string.Format("LevelLoadItem::assetAssetBundlesLevelLoaded, Level Load Fail, Path is {0}", m_origPath), LogTypeId.eLogResLoader);

                m_nonRefCountResLoadResultNotify.resLoadState.setFailed();
            }

            m_nonRefCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
        }
    }
}