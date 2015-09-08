#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFileBase import eFileType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType



class ExportCSharpFile():
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
    
    
    def export(self):
        for file in AppSysBase.instance().getConfigPtr().getProtoFilesList().getFilesListPtr():
            if file.getFileType() == eFileType.eFile:       # 如果是文件，直接解析
                fileNameNoExt = file.getFileNameNoExt()
                fileOutPath = AppSysBase.instance().getConfigPtr().getCSOutPath();
                fullPath = "{0}/{1}.cs".format(fileOutPath, fileNameNoExt)

                with open(fullPath, 'w', encoding = 'utf8') as fHandle:
                    AppSysBase.instance().getClsCSharpExportUsing().exportUsing(fHandle)
                    AppSysBase.instance().getClsCSharpExportNS().exportNSStart(fHandle)
                    
                    for protoElem in file.getProtoElemList():   # 遍历整个文件列表
                        if protoElem.getElemType() == eProtoElemType.eMessage:  # 如果是消息
                            AppSysBase.instance().getClsCSharpExportMessage().exportMessage(fHandle, protoElem)
                        elif protoElem.getElemType() == eProtoElemType.eEnum:
                            AppSysBase.instance().getClsCSharpExportEnum().exportEnum(fHandle, protoElem)
                        elif protoElem.getElemType() == eProtoElemType.eComment:
                            AppSysBase.instance().getClsCSharpExportComment().exportComment(fHandle, protoElem)

                    AppSysBase.instance().getClsCSharpExportNS().exportNSEnd(fHandle)
                    
                    fHandle.close()         # 关闭文件输入

