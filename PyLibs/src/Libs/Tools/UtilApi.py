# -*- coding: utf-8 -*-

'''
@brief: UtilApi
'''

import time
from Libs.Core.GObject import GObject

class UtilApi(GObject):
    
    @staticmethod
    def isAddressEqual(a, b):
        return a == b;
        
    
    @staticmethod
    def getTotalSeconds():
        return time.time();
    
    
