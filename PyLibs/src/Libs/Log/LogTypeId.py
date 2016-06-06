# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;

class LogTypeId(GObject):
    eLogCommon = 0;         # 通用日志
    eLogSceneCull = 1;      # 场景裁剪日志
    eLogMSceneManager = 2;  # 场景管理器
    eLogTest = 3;           # 测试日志

