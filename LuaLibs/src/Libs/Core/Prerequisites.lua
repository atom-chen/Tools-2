-- 所有全局类都在这里加载
require "Libs.Core.GlobalNS"      -- 加载自己的全局表

GlobalNS.Class = require "Libs.Core.Class"
GlobalNS.GObject = require "Libs.Core.GObject"
GlobalNS.Array = require "Libs.DataStruct.Array"
GlobalNS.MList = GlobalNS.Array
GlobalNS.EventDispatchFunctionObject = require "Libs.EventHandle.EventDispatchFunctionObject"