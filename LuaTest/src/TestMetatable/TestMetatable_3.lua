--[[  
      @brief 这个是错误的直接在 table 中添加  __index 表实现，导致获取不到值
]]--

Window = {}

Window.prototype = {x = 0, y = 0, width = 100, height = 100}
Window.mt = {}

function Window.new(o)
    -- setmetatable(o, Window.mt)
    o.__index = Window.prototype
    return o
end

--现在定义一个元方法
Window.mt.__index = function(table, key)
    return Window.prototype[key]
end


-- w = Window.new{x=10,y=20}   -- 调用的时候不用这么写吗 Window.new({x=10,y=20})
w = Window.new({x=10,y=20}) 
print(w.width)  -- 100 window实际上没有width这个字段




