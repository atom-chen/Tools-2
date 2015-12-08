-- 所有全局类都在这里加载
require "MyLua.Libs.Core.GlobalNS"      -- 加载自己的全局表

-- 基础
require "MyLua.Libs.Core.Class"
require "MyLua.Libs.Core.GObject"
require "MyLua.Libs.Core.StaticClass"
require "MyLua.Libs.Core.ClassLoader"

-- 数据结构
require "MyLua.Libs.DataStruct.Array"
GlobalNS.MList = GlobalNS.Array
require "MyLua.Libs.DataStruct.Dictionary"


-- 延迟处理器
require "MyLua.Libs.DelayHandle.IDelayHandleItem"
require "MyLua.Libs.DelayHandle.DelayHandleObject"
require "MyLua.Libs.DelayHandle.DelayHandleParamBase"
require "MyLua.Libs.DelayHandle.DelayAddParam"
require "MyLua.Libs.DelayHandle.DelayDelParam"
require "MyLua.Libs.DelayHandle.DelayHandleMgrBase"


-- 事件分发器
require "MyLua.Libs.EventHandle.EventDispatchFunctionObject"
require "MyLua.Libs.EventHandle.IDispatchObject"
require "MyLua.Libs.EventHandle.EventDispatch"
require "MyLua.Libs.EventHandle.EventDispatchGroup"
require "MyLua.Libs.EventHandle.AddOnceAndCallOnceEventDispatch"
require "MyLua.Libs.EventHandle.AddOnceEventDispatch"
require "MyLua.Libs.EventHandle.CallOnceEventDispatch"
require "MyLua.Libs.EventHandle.ResEventDispatch"


-- 帧处理事件
require "MyLua.Libs.EventHandle.ITickedObject"
require "MyLua.Libs.EventHandle.TimerItemBase"
require "MyLua.Libs.EventHandle.FrameTimerItem"
require "MyLua.Libs.EventHandle.DaoJiShiTimer"
require "MyLua.Libs.EventHandle.SystemTimeData"
require "MyLua.Libs.EventHandle.SystemFrameData"
require "MyLua.Libs.EventHandle.TickProcessObject"
require "MyLua.Libs.EventHandle.TimerMgr"
require "MyLua.Libs.EventHandle.FrameTimerMgr"
require "MyLua.Libs.EventHandle.TickMgr"