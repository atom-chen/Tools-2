# -*- coding: utf-8 -*-

'''
@brief App Data
'''

from threading import Lock

class AppSys(object):
    pInstance = None
    
    @classmethod
    def instance(cls):
        if cls.pInstance is None:
            cls.pInstance = cls()
            
        return cls.pInstance
    
    def __init__(self):
        self.m_effLock = Lock()    # lock
        self.m_bOverEff = True     # Over ?
        self.m_effThread = None    # eff thread
        
        self.m_bOverChar = True
        self.m_charThread = None   # char thread
        
        self.m_bOverTer = True
        self.m_terThread = None    # char thread
        
        self.m_charCopyThread = None     # char copy
        self.m_bOverCCopy = True
        
        self.m_effCopyThread = None      # eff copy
        self.m_bOverECopy = True
        
        self.m_terCopyThread = None      # ter copy
        self.m_bOverTCopy = True
        
        self.m_bCharPicPackOver = False    # 模型图片打包是否完成
        self.m_bEffPicPackOver = False     # 特效图片打包是否完成
        self.m_bTerPicPackOver = False     # 地形图片打包是否完成
        
