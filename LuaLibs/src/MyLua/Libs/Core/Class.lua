-- 定义一个类表
local Class = function (super)
    local classType = {}        -- 返回的类表
    classType.ctor = false      -- 默认是没有构造函数的
    classType.super = super     -- 记录父类

    -- 这个函数都是没有传递 self ，如果要传递 self ，可以 classType:new 这么写，然后 cls 就是 self，classType:new 不能这么写，只能 classType:new = function(...)
    function classType:new(...)     -- 以这个表为元表，生成一个新的表
        local instance = {}         -- 实例化对象
        instance.clsCode = self     -- 记录自己的类表
        
        -- 生成表后，直接赋值元表为类的表，这样 ctor 中就可以使用类中的数据了
        setmetatable(instance, { __index = self })     -- 设置新表的元表为父类表，这里 classType 是通过函数闭包保存的
        
        do          -- 局部块
            local create              -- 调用类的创建函数
            create = function(cls, ...)
                if cls.super then         -- 如果有父类，就递归调用父类的创建函数
                    create(cls.super, ...)
                end
                if cls.ctor then          -- 调用自己的构造函数
                    cls.ctor(instance, ...)
                end
            end
     
            create(self, ...)
        end
        
        return instance
    end
   
   -- 如果父类表存在，设置 classType 表的元表为父类表
    if super then
        setmetatable(classType, super)
    end
   
    return classType
end

GlobalNS["Class"] = Class

return Class