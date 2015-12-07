-- 类加载器，加载类使用
local M = {}
GlobalNS["ClassLoader"] = M

function M:loadClass(path)
    -- require path -- 竟然会报错
    require(path) -- 需要这么写才行
    -- require "aaa" -- 直接跟字符串就可以这么写
end

function M:unloadClass(path)
    package.loaded[path] = nil
end

return M