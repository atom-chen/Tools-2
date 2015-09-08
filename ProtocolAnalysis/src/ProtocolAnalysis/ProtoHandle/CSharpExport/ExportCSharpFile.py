#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoParse.ProtoFileBase import eFileType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpKeyWord import CSharpKeyWord


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
                
                fileMsgCount = 0
                
                with open(fullPath, 'w', encoding = 'utf8') as fHandle:
                    self.exportUsing(fHandle)
                    self.exportNSStart(fHandle)
                    
                    for protoElem in file.getProtoElemList():   # 遍历整个文件列表
                        if protoElem.getType() == eProtoElemType.eMessage:  # 如果是消息
                            if fileMsgCount > 0:            # 如果之前已经有输出，需要输出一个新行
                                AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                                AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                            self.exportMessage(fHandle, protoElem)
                            fileMsgCount += 1


                    self.exportNSEnd(fHandle)
                    
                    fHandle.close()         # 关闭文件输入
     
       
    # 导出导入的命名空间
    def exportUsing(self, fHandle):
        # 输出导入的命名空间
        importNS = "using SDK.Lib;"
        fHandle.write(importNS)
        
    
    # 导出命名空间开始
    def exportNSStart(self, fHandle):
        # 输出命名空间
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        
        nsStr = "namespace Game.Msg"
        fHandle.write(nsStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeLBrace2File(fHandle)
        
        
    # 导出命名空间结束
    def exportNSEnd(self, fHandle):
        # 写入命名空间的右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)
        
    
    # 导出一个 ProtoMessage 
    def exportMessage(self, fHandle, message):
        # 写入类的名字
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        clsName = "public class {0}".format(message.getTypeName())
        fHandle.write(clsName)
        
        # 输入左括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeLBrace2File(fHandle)
        
        # 写入类的成员
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        for member in message.getMemberList():
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            
            memberStr = "public {0} {1};".format(CSharpKeyWord.sProtoKey2CSharpKey[member.getTypeName()], member.getVarName())
            fHandle.write(memberStr)
            
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        
        # 写入构造函数
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        constructFuncStr = "public {0}()".format(message.getTypeName())
        fHandle.write(constructFuncStr)
        
        # 写入构造函数左括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeLBrace2File(fHandle)
        
        # 写入构造函数内容
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        
        # 写入构造函数右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)

        # 写入序列化函数名字
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "override public void serialize(ByteBuffer bu)"
        fHandle.write(serializeStr)
        
        # 写入序列函数的左括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeLBrace2File(fHandle)
        
        # 写入序列函数基本函数
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        fHandle.write("base.serialize(bu)")
        
        # 写入序列函数的右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)
        
        # 写入类的右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)
        
    # 导入反序列化函数
    
    
    
    
    
