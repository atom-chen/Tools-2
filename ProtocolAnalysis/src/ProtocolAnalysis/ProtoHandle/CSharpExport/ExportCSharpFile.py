#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFileBase import eFileType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpKeyWord import CSharpKeyWord


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
        # 写入类的名字
        clsName = "public class {0}\n{\n".format(message.getTypeName())
        fHandle.write(clsName)
        
        # 写入类的成员
        for member in message.getMemberList():
            memberStr = "public {0} {1};\n".format(CSharpKeyWord.sProtoKey2CSharpKey[member.getTypeName()], member.getVarName())
            fHandle.write(memberStr)
            
        # 写入构造函数
        constructFuncStr = "public {0}()\n{\n}\n".format(member.getVarName())
        fHandle.write(constructFuncStr)
        
        # 写入序列化函数    
        serializeStr = "override public void serialize(ByteBuffer ba)\n{\n}\n"
        fHandle.write(serializeStr)
        # 吸入反序列化函数

