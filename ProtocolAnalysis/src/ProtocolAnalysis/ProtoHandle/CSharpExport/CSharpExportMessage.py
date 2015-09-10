
#-*- encoding=utf-8 -*-

from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpPropertyType2PropertyData import CSharpPropertyType2PropertyData
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
        # 写入反序列化函数
        CSharpExportMessage.exportDerialize(fHandle, message)
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
            if member.getPropType() == PropertyType.eInt8Array:     # char aaa[] 类型的特殊，直接转换成 string aaa
                memberStr = "public {0} {1};".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_propertyTypeKeyWord, member.getVarName())
            elif member.getPropType() == PropertyType.eUint8 or member.getPropType() == PropertyType.eInt16 or member.getPropType() == PropertyType.eUint16 or member.getPropType() == PropertyType.eInt32 or member.getPropType() == PropertyType.eUint32:
                memberStr = "public {0} {1};".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_propertyTypeKeyWord, member.getVarName())
            else:       # 数组处理
                memberStr = "public {0} {1};".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_propertyTypeKeyWord, member.getVarNameAndArray())
            
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
                
        # 写入自己的数据成员
        for selfMember in message.getMemberList():
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            if selfMember.getPropertyType() == PropertyType.eInt8 or \
                selfMember.getPropertyType() == PropertyType.eUint8 or \
                selfMember.getPropertyType() == PropertyType.eInt16 or \
                selfMember.getPropertyType() == PropertyType.eUint16 or \
                selfMember.getPropertyType() == PropertyType.eInt32 or \
                selfMember.getPropertyType() == PropertyType.eUint32:
                # 写入变量名字
                memberStr = "{0} = {1};".format(baseMemberInit.getVarName(), baseMemberInit.getDefaultValue())
            elif selfMember.getPropertyType() == PropertyType.eInt8Array:
                memberStr = "{0} = {1};".format(baseMemberInit.getVarName(), "")
            else:   # 其它的数组
                memberStr = "{0} = new {1}[{2}];".format(selfMember.getVarName(), CSharpPropertyType2PropertyData.m_sType2PropertyData[selfMember.getTypeName()].m_propertyTypeKeyWord, selfMember.getArrLen())
                
            fHandle.write(memberStr)
            #写入注释
            if not AppSysBase.instance().getClsUtils().isNullOrEmpty(selfMember.getCommentStr()):   # 如果字符串不为空
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
            #if member.getPropertyType() == PropertyType.eInt8:
            #    serializeStr = "bu.writeUnsignedInt8({0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eUint8:
            #    serializeStr = "bu.writeUnsignedInt8({0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eInt16:
            #    serializeStr = "bu.writeInt16({0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eUint16:
            #    serializeStr = "bu.writeUnsignedInt16({0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eInt32:
            #    serializeStr = "bu.writeInt32({0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eUint32:
            #    serializeStr = "bu.writeUnsignedInt32({0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eInt8Array:
            #    serializeStr = "bu.writeMultiByte({0}, GkEncode.UTF8, {1});".format(member.getVarName(), member.getArrLen())
            #else:       # 各种数组处理
            #    if member.getPropertyType() == PropertyType.eUint8Array:
            #        CSharpExportMessage.exportArrSerialize(fHandle, message, member, "byte", "8")
            #    if member.getPropertyType() == PropertyType.eInt16Array:
            #        CSharpExportMessage.exportArrSerialize(fHandle, message, member, "short", "16")
            #    if member.getPropertyType() == PropertyType.eUint16Array:
            #        CSharpExportMessage.exportArrSerialize(fHandle, message, member, "ushort", "16")
            #    if member.getPropertyType() == PropertyType.eInt32Array:
            #        CSharpExportMessage.exportArrSerialize(fHandle, message, member, "int", "32")
            #    if member.getPropertyType() == PropertyType.eUint32Array:
            #        CSharpExportMessage.exportArrSerialize(fHandle, message, member, "uint", "32")
            #       
            #    serializeStr = ""   # 防止最后输出
            
            if member.getPropertyType() == PropertyType.eInt8 or \
                member.getPropertyType() == PropertyType.eUint8 or \
                member.getPropertyType() == PropertyType.eInt16 or \
                member.getPropertyType() == PropertyType.eUint16 or \
                member.getPropertyType() == PropertyType.eInt32 or \
                member.getPropertyType() == PropertyType.eUint32:
                serializeStr = "bu.{0}({1});".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_serializeFuncKeyWord, member.getVarName())
            elif member.getPropertyType() == PropertyType.eInt8Array:
                serializeStr = "bu.{0}({1}, GkEncode.UTF8, {2});".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_serializeFuncKeyWord, member.getVarName(), member.getArrLen())
            else:       # 数组输出
                CSharpExportMessage.exportArrSerialize(fHandle, message, member, CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_propertyTypeKeyWord, CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_serializeFuncKeyWord)
                serializeStr = ""
                
            fHandle.write(serializeStr)
        
        
        # 写入序列函数的右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)
    
    # 导入反序列化函数
    @staticmethod
    def exportDerialize(fHandle, message):
        # 写入反序列化函数名字
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "override public void derialize(ByteBuffer bu)"
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
        fHandle.write("base.derialize(bu)")
        
        # 写入序列化的内容
        for member in message.getMemberList():
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            
            # 写入变量名字
            #if member.getPropertyType() == PropertyType.eInt8:
            #    serializeStr = "bu.readUnsignedInt8(ref {0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eUint8: 
            #    serializeStr = "bu.readUnsignedInt8(ref {0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eInt16: 
            #    serializeStr = "bu.readInt16(ref {0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eUint16: 
            #    serializeStr = "bu.readUnsignedInt16(ref {0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eInt32: 
            #    serializeStr = "bu.readInt32(ref {0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eUint32:   # 如果是 uint32 
            #    serializeStr = "bu.readUnsignedInt32(ref {0});".format(member.getVarName())
            #elif member.getPropertyType() == PropertyType.eInt8Array:
            #    serializeStr = "bu.readMultiByte(ref {0}, {1}, GkEncode.UTF8);".format(member.getVarName(), member.getArrLen())
            #else:
            #    if member.getPropertyType() == PropertyType.eUint8Array:
            #        CSharpExportMessage.exportArrDerialize(fHandle, message, member, "byte", "8")
            #    if member.getPropertyType() == PropertyType.eInt16Array:
            #        CSharpExportMessage.exportArrDerialize(fHandle, message, member, "short", "16")
            #    if member.getPropertyType() == PropertyType.eUint16Array:
            #        CSharpExportMessage.exportArrDerialize(fHandle, message, member, "ushort", "16")
            #    if member.getPropertyType() == PropertyType.eInt32Array:
            #        CSharpExportMessage.exportArrDerialize(fHandle, message, member, "int", "32")
            #    if member.getPropertyType() == PropertyType.eUint32Array:
            #        CSharpExportMessage.exportArrDerialize(fHandle, message, member, "uint", "32")
            
            if member.getPropertyType() == PropertyType.eInt8 or \
                member.getPropertyType() == PropertyType.eUint8 or \
                member.getPropertyType() == PropertyType.eInt16 or \
                member.getPropertyType() == PropertyType.eUint16 or \
                member.getPropertyType() == PropertyType.eInt32 or \
                member.getPropertyType() == PropertyType.eUint32:
                serializeStr = "bu.{0}({1});".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_derializeFuncKeyWord, member.getVarName())
            elif member.getPropertyType() == PropertyType.eInt8Array:
                serializeStr = "bu.{0}({1}, GkEncode.UTF8, {2});".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_derializeFuncKeyWord, member.getVarName(), member.getArrLen())
            else:       # 数组输出
                CSharpExportMessage.exportArrDerialize(fHandle, message, member, CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_propertyTypeKeyWord, CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getTypeName()].m_derializeFuncKeyWord)
                serializeStr = ""

            
            fHandle.write(serializeStr)
        
        
        # 写入序列函数的右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)
    
    
    # 输出数组输入
    @staticmethod
    def exportArrSerialize(fHandle, message, member, typeStr, typeWrite):
        #serializeStr = "{0} = new {1}[{2}];".format(member.getVarName(), typeStr, member.getArrLen())
        #fHandle.write(serializeStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "for(int idx = 0; idx < member.getArrLen(); ++idx)"
        fHandle.write(serializeStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "{"
        fHandle.write(serializeStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "bu.{0}({1}[idx]);".format(typeWrite, member.getVarName())
        fHandle.write(serializeStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "}"
        fHandle.write(serializeStr)


    # 输出数组输入
    @staticmethod
    def exportArrDerialize(fHandle, message, member, typeStr, typeRead):
        #serializeStr = "{0} = new {1}[{2}];".format(member.getVarName(), typeStr, member.getArrLen())
        #fHandle.write(serializeStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "for(int idx = 0; idx < member.getArrLen(); ++idx)"
        fHandle.write(serializeStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "{"
        fHandle.write(serializeStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "bu.{0}(ref {1}[idx]);".format(typeRead, member.getVarName())
        fHandle.write(serializeStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "}"
        fHandle.write(serializeStr)
        
        
    