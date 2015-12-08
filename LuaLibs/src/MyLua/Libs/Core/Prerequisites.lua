-- 所有全局类都在这里加载
require "MyLua.Libs.Core.GlobalNS"      -- 加载自己的全局表

-- 基础
require "MyLua.Libs.Core.Class"
require "MyLua.Libs.Core.GObject"
require "MyLua.Libs.DataStruct.Array"
GlobalNS.MList = GlobalNS.Array

-- 事件分发器
require "MyLua.Libs.EventHandle.EventDispatchFunctionObject"
require "MyLua.Libs.EventHandle.IDispatchObject"
require "MyLua.Libs.EventHandle.EventDispatch"
require "MyLua.Libs.EventHandle.EventDispatchGroup"
require "MyLua.Libs.EventHandle.AddOnceAndCallOnceEventDispatch"
require "MyLua.Libs.EventHandle.AddOnceEventDispatch"
require "MyLua.Libs.EventHandle.CallOnceEventDispatch"
require "MyLua.Libs.EventHandle.ResEventDispatch"