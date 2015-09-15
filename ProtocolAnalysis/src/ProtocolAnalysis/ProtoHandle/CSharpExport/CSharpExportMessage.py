
#-*- encoding=utf-8 -*-

from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.CSharpExport.CSharpPropertyType2PropertyData import CSharpPropertyType2PropertyData


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
            if member.isBasicType():
                memberStr = "public {0} {1};".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_propertyTypeKeyWord, member.getVarName())
            elif member.isCharArrayType():     # char aaa[] 类型的特殊，直接转换成 string aaa
                memberStr = "public {0} {1};".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_propertyTypeKeyWord, member.getVarName())
            elif member.isUserType():
                memberStr = "public {0} {1};".format(member.getTypeName(), member.getVarName())
            elif member.isUserArrayType():
                memberStr = "public {0}[] {1};".format(member.getTypeName(), member.getVarName())
            else:       # 数组处理
                memberStr = "public {0}[] {1};".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_propertyTypeKeyWord, member.getVarName())
            
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
        # 写入基类成员赋值语句
        for baseMemberInit in message.getBaseMemberInitList():
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            
            # 写入变量名字
            if baseMemberInit.isDefaultValueCV():   # 如果是常量值
                memberStr = "{0} = (int){1};".format(baseMemberInit.getVarName(), baseMemberInit.getDefaultValue())
            else:    
                memberStr = "{0} = {1};".format(baseMemberInit.getVarName(), baseMemberInit.getDefaultValue())
            
            fHandle.write(memberStr)
            #写入注释
            if not AppSysBase.instance().getClsUtils().isNullOrEmpty(baseMemberInit.getCommentStr()):   # 如果字符串不为空
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
                fHandle.write(baseMemberInit.getCommentStr())
                
        # 写入自己的数据成员
        for selfMember in message.getMemberList():
            if not selfMember.hasDefaultValue():        # 如果没有默认值
                continue
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            if selfMember.isBasicType():
                # 写入变量名字
                memberStr = "{0} = {1};".format(selfMember.getVarName(), selfMember.getDefaultValue())
            elif selfMember.isCharArrayType():
                memberStr = "{0} = {1};".format(selfMember.getVarName(), "\"\"")
            elif selfMember.isUserType():
                memberStr = "{0} = {1};".format(selfMember.getVarName(), selfMember.getDefaultValue())
            #else:   # 其它的数组
            #    memberStr = "{0} = new {1}[{2}];".format(selfMember.getVarName(), CSharpPropertyType2PropertyData.m_sType2PropertyData[selfMember.getPropertyType()].m_propertyTypeKeyWord, selfMember.getArrLen())
                
            fHandle.write(memberStr)
            # 这个注释就不用写了，因为成员的注释已经在成员声明区域输出了
            #if not AppSysBase.instance().getClsUtils().isNullOrEmpty(selfMember.getCommentStr()):   # 如果字符串不为空
            #    AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            #    fHandle.write(selfMember.getCommentStr())
            
        
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
            
            if member.isBasicType():
                serializeStr = "bu.{0}({1});".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_serializeFuncKeyWord, member.getVarName())
            elif member.isCharArrayType():
                serializeStr = "bu.{0}({1}, GkEncode.UTF8, {2});".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_serializeFuncKeyWord, member.getVarName(), member.getArrLen())
            elif member.isUserType():
                serializeStr = "{0} = new {1}();".format(member.getVarName(), member.getTypeName())
                fHandle.write(serializeStr)
                AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
                
                serializeStr = "{0}.serialize(bu);".format(member.getVarName())
            elif member.isUserArrayType():
                CSharpExportMessage.exportArrSerialize(fHandle, message, member, "", "")
                serializeStr = ""
            else:       # 数组输出
                CSharpExportMessage.exportArrSerialize(fHandle, message, member, CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_propertyTypeKeyWord, CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_serializeFuncKeyWord)
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
        
        preMember = 0
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
            
            if member.isBasicType():
                serializeStr = "bu.{0}(ref {1});".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_derializeFuncKeyWord, member.getVarName())
            elif member.isCharArrayType():
                serializeStr = "bu.{0}(ref {1}, GkEncode.UTF8, {2});".format(CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_derializeFuncKeyWord, member.getVarName(), member.getArrLen())
            elif member.isUserType():
                serializeStr = "{0} = new {1}();".format(member.getVarName(), member.getTypeName())
                fHandle.write(serializeStr)
                AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            
                serializeStr = "{0}.derialize(bu);".format(member.getVarName())
            elif member.isUserArrayType():
                CSharpExportMessage.exportNewArr(fHandle, member, preMember)
                CSharpExportMessage.exportArrDerialize(fHandle, message, member, "", "")
                serializeStr = ""
            else:       # 数组输出
                CSharpExportMessage.exportNewArr(fHandle, member, preMember)
                CSharpExportMessage.exportArrDerialize(fHandle, message, member, CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_propertyTypeKeyWord, CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_derializeFuncKeyWord)
                serializeStr = ""

            
            fHandle.write(serializeStr)
            
            preMember = member
        
        
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
        if not member.isArrayLenCV():
            serializeStr = "for(int idx = 0; idx < {0}; ++idx)".format(member.getArrLen())
        else:
            serializeStr = "for(int idx = 0; idx < (int){0}; ++idx)".format(member.getArrLen())
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
        #if member.isBasicArrayType():
        #    serializeStr = "bu.{0}({1}[idx]);".format(typeWrite, member.getVarName())
        #else:
        #    serializeStr = "{0}[idx] = new {1}();".format(member.getVarName(), member.getTypeName())
        #    fHandle.write(serializeStr)
        #    AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        #    AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        #    AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        #    AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        #    AppSysBase.instance().getClsUtils().writeTab2File(fHandle)                        
        serializeStr = "{0}[idx].serialize(bu);".format(member.getVarName())
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
        if not member.isArrayLenCV():
            serializeStr = "for(int idx = 0; idx < {0}; ++idx)".format(member.getArrLen())
        else:
            serializeStr = "for(int idx = 0; idx < (int){0}; ++idx)".format(member.getArrLen())
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
        if member.isBasicArrayType():
            serializeStr = "bu.{0}(ref {1}[idx]);".format(typeRead, member.getVarName())
        else:   # 用户数据数组类型
            serializeStr = "{0}[idx] = new {1}();".format(member.getVarName(), member.getTypeName())
            fHandle.write(serializeStr)            
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            
            serializeStr = "{0}[idx].derialize(bu);".format(member.getVarName())
            
        
        fHandle.write(serializeStr)
        
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        serializeStr = "}"
        fHandle.write(serializeStr)
        
        
    @staticmethod
    def exportNewArr(fHandle, member, preMember):
        typeName = ""
        if member.isUserArrayType():            # 用户数组
            typeName = member.getTypeName()
        else:       # 基本类型数组
            typeName = CSharpPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_propertyTypeKeyWord
                
        if member.isArrayLenEqualZero():        # 如果数组长度是 0
            serializeStr = "{0} = new {1}[{2}];".format(member.getVarName(), typeName, preMember.getVarName())
        elif member.isArrayLenCV():        # 如果数组长度是 0
            serializeStr = "{0} = new {1}[(int){2}];".format(member.getVarName(), typeName, member.getArrLen())
        else:
            serializeStr = "{0} = new {1}[{2}];".format(member.getVarName(), typeName, member.getArrLen())
            
        fHandle.write(serializeStr)


