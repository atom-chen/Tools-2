--[[  
      @brief 测试 require 实现，测试 select
]]--


module(...)


-- 打印参数
for i = 1, select('#', ...) do
     print(select(i, ...))
end


function new(r, i) return {r = r, i = i} end
 
-- 定义一个常量i
i = new(0, 1)
 
function add(c1, c2)
    return new(c1.r + c2.r, c1.i + c2.i)
end
 
function sub(c1, c2)
    return new(c1.r - c2.r, c1.i - c2.i)
end






