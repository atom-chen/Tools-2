#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpKeyWord import CSharpKeyWord
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoTypeMemberBase import PropertyType


class CSharpExportMessage(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''

    @staticmethod
    # 导出一个 ProtoMessage 
    def exportMessage(fHandle, message):
        # 写入类的名字
        CSharpExportMessage.exportClsDeclStart(fHandle, message)
        # 写入类的成员
        CSharpExportMessage.exportMemDecl(fHandle, message)
        # 与后面分割一个空格
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        # 写入构造函数
        CSharpExportMessage.exportConstruct(fHandle, message)
        # 写入序列化函数
        CSharpExportMessage.exportSerialize(fHandle, message)
        # 写入类的右括号
        CSharpExportMessage.exportClsDeclEnd(fHandle, message)
        # 输入一个空行，以便隔开
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)


    # 导出类声明
    @staticmethod
    def exportClsDeclStart(fHandle, message):
        # 写入类的名字
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        if AppSysBase.instance().getClsUtils().isNullOrEmpty(message.getParentCls()):
            clsName = "public class {0}".format(message.getTypeName())
        else:
            clsName = "public class {0} : {1}".format(message.getTypeName(), message.getParentCls())
        fHandle.write(clsName)
        
        # 输入左括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeLBrace2File(fHandle)
        
        
    # 写入类声明结束
    @staticmethod
    def exportClsDeclEnd(fHandle, message):
        # 写入类的右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)


    # 写入成员声明
    @staticmethod
    def exportMemDecl(fHandle, message):
        # 写入类的成员
        for member in message.getMemberList():
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            
            # 写入变量名字
            memberStr = "public {0} {1};".format(CSharpKeyWord.sProtoKey2CSharpKey[member.getTypeName()], member.getVarName())
            fHandle.write(memberStr)
            #写入注释
            if not AppSysBase.instance().getClsUtils().isNullOrEmpty(member.getCommentStr()):   # 如果字符串不为空
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
                fHandle.write(member.getCommentStr())


    # 写入构造函数
    @staticmethod
    def exportConstruct(fHandle, message):
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
        for baseMemberInit in message.getBaseMemberInitList():
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            
            # 写入变量名字
            memberStr = "{0} = {1};".format(baseMemberInit.getVarName(), baseMemberInit.getDefaultValue())
            fHandle.write(memberStr)
            #写入注释
            if not AppSysBase.instance().getClsUtils().isNullOrEmpty(baseMemberInit.getCommentStr()):   # 如果字符串不为空
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
                fHandle.write(baseMemberInit.getCommentStr())
            
        
        # 写入构造函数右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)

    # 导出序列化函数
    @staticmethod
    def exportSerialize(fHandle, message):
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
        
        # 写入序列化的内容
        for member in message.getMemberList():
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            
            # 写入变量名字
            if member.getPropertyType() == PropertyType.eUint32:   # 如果是 uint32 
                serializeStr = "bu.writeUnsignedInt32({0});".format(member.getVarName())
            if member.getPropertyType() == PropertyType.eCharArray:
                serializeStr = "bu.writeMultiByte({0}, GkEncode.UTF8, {1});".format(member.getVarName(), member.getArrLen())
            fHandle.write(serializeStr)
        
        
        # 写入序列函数的右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)
    
    # 导入反序列化函数
    
    