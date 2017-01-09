# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;

class DelayHandleObject(GObject):
    def __init__(self):
        self.mTypeId = "DelayHandleObject";
        self.mDelayObject = None;
        self.mDelayParam = None;

