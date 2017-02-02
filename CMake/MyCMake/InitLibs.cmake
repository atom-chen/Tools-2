# CMAKE_CURRENT_SOURCE_DIR 是指当前执行的 CMakeLists.txt 文件所在的目录，不是当前 include 所在的目录
set(CurCMakeFilePath ${CMAKE_CURRENT_SOURCE_DIR})
set(CurFilePath ${MY_LIBS_PATH})
set(CurModulePath ${CMAKE_MODULE_PATH})

SET(CMAKE_MODULE_PATH ${CurModulePath} ${CurFilePath} ${CurFilePath}/Libs ${CurFilePath}/Libs/Core ${CurFilePath}/Libs/Log ${CurFilePath}/Libs/Platform)

message(status, "#####################################")
message(status, ${CurModulePath})
message(status, ${CurCMakeFilePath})
message(status, ${CurFilePath})
message(status, "#####################################")

include(ModuleLoad)

LoadModule("PlatformSys")