#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType


class CppExportNS(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''
    
    
    @staticmethod
    # 导出命名空间开始
    def exportNSStart(fHandle, file):
        # 输出命名空间
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        
        #nsStr = "namespace Game.Msg"
        #fHandle.write(nsStr)
        
        for protoElem in file.getProtoElemList():   # 遍历整个文件列表
            if protoElem.getElemType() == eProtoElemType.ePackage:
                nsStr = "namespace {0}".format(protoElem.getTypeName())
                fHandle.write(nsStr)
                break
        
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeLBrace2File(fHandle)
        
        
    # 导出命名空间结束
    @staticmethod
    def exportNSEnd(fHandle):
        # 写入命名空间的右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)

