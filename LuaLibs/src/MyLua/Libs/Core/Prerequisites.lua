-- 所有全局类都在这里加载
require "MyLua.Libs.Core.GlobalNS"      -- 加载自己的全局表

require "MyLua.Libs.Core.Class"
require "MyLua.Libs.Core.GObject"
require "MyLua.Libs.DataStruct.Array"
GlobalNS.MList = GlobalNS.Array

require "MyLua.Libs.EventHandle.EventDispatchFunctionObject"