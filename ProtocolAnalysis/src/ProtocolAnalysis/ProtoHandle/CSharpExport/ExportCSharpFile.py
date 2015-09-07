#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFileBase import eFileType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType


class ExportCSharpFile(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''
    
    
    def export(self):
        for file in AppSysBase.instance().getConfigPtr().getProtoFilesList():
            if file.getFileType() == eFileType.eFile:       # 如果是文件，直接解析
                fileNameNoExt = file.getFileNameNoExt()
                fileOutPath = AppSysBase.instance().getConfigPtr().getCSOutPath();
                fullPath = "{0}/{1}.cs".format(fileNameNoExt, fileOutPath)
                with open(fullPath, 'r', encoding = 'utf8') as fHandle:
                    for protoElem in file.getProtoElemList():   # 遍历整个文件列表
                        if protoElem.getType() == eProtoElemType.eMessage:  # 如果是消息
                            self.exportMessage(fHandle, protoElem)
                    
                    fHandle.Close()         # 关闭文件输入
                        
    
    # 导出一个 ProtoMessage 
    def exportMessage(self, fHandle, message):
        pass

