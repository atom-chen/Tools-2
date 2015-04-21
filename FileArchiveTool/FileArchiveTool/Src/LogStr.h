#ifndef __LogStr_H
#define __LogStr_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

#define LS_PAK_END "当前打包完成\n"
#define LS_PAK_ADD_TASK "添加打包任务\n"
#define LS_PAK_START_PAK_THREAD "启动打包线程\n"

#define LS_UNPAK_END "当前解包完成\n"
#define LS_UNPAK_ADD_TASK "添加解包任务\n"
#define LS_UNPAK_START_PAK_THREAD "启动解包线程\n"

#define LS_START_SPLITPAK "开始划分包\n"
#define LS_CODE_ERROR "编码转换错误\n"
#define LS_CODE_BUFFER_OVERFLOW "编码转换 Dest 缓冲区小于 Src 缓冲区\n"
#define LS_SPLIT_LINE "======================\n"

END_NAMESPACE_FILEARCHIVETOOL

#endif