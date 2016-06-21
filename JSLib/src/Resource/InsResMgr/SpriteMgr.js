﻿using LuaInterface;
using System;

namespace SDK.Lib
{
    public class SpriteMgr : InsResMgrBase
    {
        public SpriteAtlasRes getAndSyncLoadRes(string path)
        {
            //path = path + UtilApi.DOTPNG;
            return getAndSyncLoad<SpriteAtlasRes>(path, true);
        }

        public SpriteAtlasRes getAndAsyncLoadRes(string path, MAction<IDispatchObject> handle)
        {
            //path = path + UtilApi.DOTPNG;
            return getAndAsyncLoad<SpriteAtlasRes>(path, handle, true);
        }

        public SpriteAtlasRes getAndAsyncLoadRes(string path, LuaTable luaTable = null, LuaFunction luaFunction = null)
        {
            //path = path + UtilApi.DOTPNG;
            return getAndAsyncLoad<SpriteAtlasRes>(path, luaTable, luaFunction, true);
        }
    }
}