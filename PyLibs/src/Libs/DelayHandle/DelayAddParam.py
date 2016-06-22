# -*- coding: utf-8 -*-

from Libs.DelayHandle.DelayHandleParamBase import DelayHandleParamBase;

class DelayAddParam(DelayHandleParamBase):
    
    def __init__(self):
        super(DelayAddParam, self).__init__();
        
        self.mTypeId = "DelayAddParam";
        
        self.m_priority = 0;

