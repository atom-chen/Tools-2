#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType


class CSharpExportUsing(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''

    @staticmethod
    # 导出导入的命名空间
    def exportUsing(fHandle, file):
        # 输出导入的命名空间
        #importUsing = "using SDK.Lib;"
        #fHandle.write(importUsing)
        
        # 输出导入的命名空间
        bFirst = True
        for protoElem in file.getProtoElemList():   # 遍历整个文件列表
            if protoElem.getElemType() == eProtoElemType.eImport:
                for importNS in protoElem.getHeaderList():
                    if not bFirst:
                        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                    
                    nsStr = "using {0};".format(importNS)
                    fHandle.write(nsStr)
                    
                    bFirst = False
                    

