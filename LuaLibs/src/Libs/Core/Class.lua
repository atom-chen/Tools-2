-- 定义一个类表
-- 直接采用表的形式
function class(super)
    local class_type = {}       -- 返回的类表
    class_type.ctor = false     -- 构造构造函数默认是没有的
    class_type.super = super    -- 设置父类表，可以通过 super 这个字段访问父类
    
    class_type.new = function(...)    -- 以这个表为元表，生成一个新的表
        local obj={}
        
        -- 生成表后，直接赋值元表为类的表，这样 ctor 中就可以使用类中的数据了
        setmetatable(obj, { __index = class_type })     -- 设置新表的元表为父类表
        
        do
            local create              -- 调用类的创建函数
            create = function(c, ...)
                if c.super then         -- 如果有父类，就递归调用父类的创建函数
                    create(c.super, ...)
                end
                if c.ctor then          -- 调用自己的构造函数
                    c.ctor(obj, ...)
                end
            end
     
            create(class_type, ...)
        end
        
        return obj
    end
   
   -- 如果父类表存在，设置 vtbl 表的元表为父类表
    if super then
        setmetatable(vtbl, {__index =
            function(t, k)
                local ret = super[k] -- 获取 super 类的表
                class_type[k] = ret       -- 读取的时候从父类查找，保存到自己类表中，以后不用再次查找了
                return ret
            end
        })
    end
   
    return class_type
end