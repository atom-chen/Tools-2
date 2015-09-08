#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class CSharpExportNS(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''
    
    
    @staticmethod
    # 导出命名空间开始
    def exportNSStart(fHandle):
        # 输出命名空间
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        
        nsStr = "namespace Game.Msg"
        fHandle.write(nsStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeLBrace2File(fHandle)
        
        
    # 导出命名空间结束
    @staticmethod
    def exportNSEnd(fHandle):
        # 写入命名空间的右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)

