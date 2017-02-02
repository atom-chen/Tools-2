# CMAKE_CURRENT_SOURCE_DIR 是指当前执行的 CMakeLists.txt 文件所在的目录，不是当前 include 所在的目录
set(CurCMakeFilePath ${CMAKE_CURRENT_SOURCE_DIR})
set(CurFilePath ${MY_LIBS_PATH})
set(CurModulePath ${CMAKE_MODULE_PATH})

SET(CMAKE_MODULE_PATH ${CurModulePath} ${CurFilePath} ${CurFilePath}/Libs ${CurFilePath}/Libs/Core ${CurFilePath}/Libs/Log ${CurFilePath}/Libs/Platform)

message(status, "#####################################")
message(status, "CurModulePath is ${CurModulePath}")
message(status, "CurCMakeFilePath is ${CurCMakeFilePath}")
message(status, "CurFilePath is ${CurFilePath}")
message(status, "CMAKE_MODULE_PATH is ${CMAKE_MODULE_PATH}")
message(status, "#####################################")

# 加载脚本加载模块
#include(ModuleLoad)
# 加载基本模块
include("System")
# 设置 CMakeModulePath 脚本加载目录
#SetCMakeModulePath(${CurModulePath} ${CurFilePath} ${CurFilePath}/Libs ${CurFilePath}/Libs/Core ${CurFilePath}/Libs/Log ${CurFilePath}/Libs/Platform)
#SetCMakeModulePath("${CurModulePath}" "${CurFilePath}" "${CurFilePath}/Libs" "${CurFilePath}/Libs/Core" "${CurFilePath}/Libs/Log" "${CurFilePath}/Libs/Platform")
# 加载库模块
LoadModule("LibsInc")
#include("LibsInc")