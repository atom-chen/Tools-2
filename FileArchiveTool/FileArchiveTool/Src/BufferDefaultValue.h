#ifndef __BUFFERDEFAULTVALUE_H
#define __BUFFERDEFAULTVALUE_H

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

#define MAX_CAPACITY 8 * 1024 * 1024      // 最大允许分配 8 M
#define INIT_CAPACITY 1 * 1024            // 默认分配 1 K
#define MSG_HEADER_SIZE 4   // 包长度占据几个字节

END_NAMESPACE_FILEARCHIVETOOL

#endif		// __BUFFERDEFAULTVALUE_H