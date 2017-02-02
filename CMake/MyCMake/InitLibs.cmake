# CMAKE_CURRENT_SOURCE_DIR ��ָ��ǰִ�е� CMakeLists.txt �ļ����ڵ�Ŀ¼�����ǵ�ǰ include ���ڵ�Ŀ¼
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