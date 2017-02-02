set(CurFilePath ${CMAKE_CURRENT_SOURCE_DIR})
set(CurModulePath ${CMAKE_MODULE_PATH})

SET(CMAKE_MODULE_PATH ${CurModulePath} ${CurFilePath} ${CurFilePath}/Libs ${CurFilePath}/Libs/Core ${CurFilePath}/Libs/Log ${CurFilePath}/Libs/Platform)

