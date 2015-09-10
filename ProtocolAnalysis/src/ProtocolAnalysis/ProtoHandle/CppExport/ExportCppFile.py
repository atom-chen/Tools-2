#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFileBase import eFileType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType



class ExportCppFile():
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
                self.exportOneFile(file)
            elif file.getFileType() == eFileType.eDir:       # 如果是文件，直接解析
                for dirFile in file.getFilesList():
                    self.exportOneFile(dirFile)
                    

    def exportOneFile(self, file):
        fileNameNoExt = file.getFileNameNoExt()
        fileOutPath = AppSysBase.instance().getConfigPtr().getCppOutPath();
        fullPath = "{0}/{1}.h".format(fileOutPath, fileNameNoExt)

        with open(fullPath, 'w', encoding = 'utf8') as fHandle:
            AppSysBase.instance().getClsCppExportDefine().exportHeaderDefineStart(fHandle, fileNameNoExt)
            AppSysBase.instance().getClsCppExportInclude().exportInclude(fHandle, file)
            AppSysBase.instance().getClsCppExportPragma().exportPragmaBeforeNS(fHandle, file)
            AppSysBase.instance().getClsCppExportNS().exportNSStart(fHandle, file)
            
            for protoElem in file.getProtoElemList():   # 遍历整个文件列表
                if protoElem.getElemType() == eProtoElemType.eMessage:  # 如果是消息
                    AppSysBase.instance().getClsCppExportMessage().exportMessage(fHandle, protoElem)
                elif protoElem.getElemType() == eProtoElemType.eEnum:
                    AppSysBase.instance().getClsCppExportEnum().exportEnum(fHandle, protoElem)
                elif protoElem.getElemType() == eProtoElemType.eComment:
                    AppSysBase.instance().getClsCppExportComment().exportComment(fHandle, protoElem)
                    

            AppSysBase.instance().getClsCSharpExportNS().exportNSEnd(fHandle)
            AppSysBase.instance().getClsCppExportPragma().exportPragmaAfterNS(fHandle, file)
            AppSysBase.instance().getClsCppExportDefine().exportHeaderDefineEnd(fHandle)
            
            fHandle.close()         # 关闭文件输入

