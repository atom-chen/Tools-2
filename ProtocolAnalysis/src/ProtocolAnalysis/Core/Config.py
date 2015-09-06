#-*- encoding=utf-8 -*-

#import os
#import datetime
#import time

from ProtocolAnalysis.ProtoParse.ProtoFilesList import ProtoFilesList

# base config info
class Config(object):
    
    #pInstance = None
    
    #@staticmethod
    #def instance():
    #    if Config.pInstance is None:
    #        Config.pInstance = Config()
    #    return Config.pInstance
    
    def __init__(self):
    #    assert(Config.pInstance is None)
    #    Config.pInstance = self
        
        # 注意全部需要初始化，否则如果配置文件不用，并且没有判断是否有这个属性，就会出问题
        self.m_protoFilesList = None        # Prote 文件所在目录，使用逗号分隔，如果有 '.' 就是一个 Proto 文件，如果没有，就说明是一个目录
        self.m_outPath = ""         # 输出文件目录
        
        # 配置文件和自己变量之间的映射
        self.m_cfg2Var = {}
        self.m_cfg2Var["ProtoDir"] = "m_protoDir"
        self.m_cfg2Var["OutPath"] = "m_outPath"

        #读取初始化数据
    def readInit(self, filename):
        # gbk , gk2312
        with open(filename, 'r', encoding = 'utf8') as fHandle:
            cont = fHandle.read()
            strlist = cont.split('\n')
            idx = 0
            substrList = []
            listlen = len(strlist)
            while idx < listlen:
                substrList = strlist[idx].split('=')
                if len(substrList[0]):
                    if substrList[0] == 'ProtoDir':
                        self.__dict__[self.m_cfg2Var[substrList[0]]] = ProtoFilesList(substrList[1])
                    else:    
                        self.__dict__[self.m_cfg2Var[substrList[0]]] = substrList[1]
                idx += 1
                
                
    def getProtoFilesList(self):
        return self.m_protoFilesList

