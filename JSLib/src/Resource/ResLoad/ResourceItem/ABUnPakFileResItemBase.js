﻿using System.Collections;
using System.IO;
using UnityEngine;

namespace SDK.Lib
{
    /**
     * @brief 打包的资源系统 base
     */
    public class ABUnPakFileResItemBase : FileResItem
    {
        public byte[] m_bytes = null;
        protected AssetBundle m_bundle = null;

        public void initByBytes(byte[] bytes, string prefixPath)
        {
            m_bytes = bytes;
            m_bundlePath = Path.Combine(prefixPath, m_loadPath);

            // 检查是否资源打包成 unity3d 
            if (Ctx.m_instance.m_cfg.m_pakExtNameList.IndexOf(m_extName) != -1)
            {
                if (m_resNeedCoroutine)
                {
                    Ctx.m_instance.m_coroutineMgr.StartCoroutine(initAssetByCoroutine());
                }
                else
                {
                    initAsset();
                }
            }
            else
            {
                m_refCountResLoadResultNotify.resLoadState.setSuccessLoaded();
                m_refCountResLoadResultNotify.loadResEventDispatch.dispatchEvent(this);
            }
        }

        virtual protected void initAsset()
        {
#if UNITY_5_0 || UNITY_5_1 || UNITY_5_2
            m_bundle = AssetBundle.CreateFromMemoryImmediate(m_bytes);
#else
            m_bundle = AssetBundle.LoadFromMemory(m_bytes);
#endif
        }

        virtual protected IEnumerator initAssetByCoroutine()
        {
            return null;
        }

        override public void unload()
        {
            m_bytes = null;
            if (Ctx.m_instance.m_cfg.m_pakExtNameList.IndexOf(m_extName) != -1)         // 打包成 unity3d 加载的
            {
                if (m_bundle != null)
                {
                    m_bundle.Unload(false);
                    m_bundle = null;
                }
                else
                {
                    Ctx.m_instance.m_logSys.log("unity3d 资源卸载的时候 AssetBundle 加载失败");
                }
            }
        }
    }
}