#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType


class CppExportInclude(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''

    @staticmethod
    # 导出导入的命名空间
    def exportInclude(fHandle, file):
        # 输出导入的命名空间
        #importUsing = "using SDK.Lib;"
        #fHandle.write(importUsing)
        
        # 输出导入的命名空间
        bFirst = True
        for protoElem in file.getProtoElemList():   # 遍历整个文件列表
            if protoElem.getElemType() == eProtoElemType.eHeader:
                for headerInclude in protoElem.getHeaderList():
                    if bFirst:          # 添加一个间隔空行
                        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                    
                    # 下一行写入
                    AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                    includeStr = "#include {0}".format(headerInclude)
                    fHandle.write(includeStr)
                    
                    bFirst = False
                    

