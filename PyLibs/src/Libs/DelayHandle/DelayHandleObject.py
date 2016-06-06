# -*- coding: utf-8 -*-

from Libs.Core.GObject import GObject;

class DelayHandleObject(GObject):
    def __init__(self):
        self.mTypeId = "DelayHandleObject";
        self.m_delayObject = None;
        self.m_delayParam = None;

