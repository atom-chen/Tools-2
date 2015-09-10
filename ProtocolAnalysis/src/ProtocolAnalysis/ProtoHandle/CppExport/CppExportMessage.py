
#-*- encoding=utf-8 -*-

from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.CppExport.CppPropertyType2PropertyData import CppPropertyType2PropertyData
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoTypeMemberBase import PropertyType
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoPropertyTypeKeyWord2Property import ProtoPropertyTypeKeyWord2Property


class CppExportMessage(object):
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
        CppExportMessage.exportClsDeclStart(fHandle, message)
        # 写入类的成员
        CppExportMessage.exportMemDecl(fHandle, message)
        # 与后面分割一个空格
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        # 写入构造函数
        CppExportMessage.exportConstruct(fHandle, message)
        # 写入类的右括号
        CppExportMessage.exportClsDeclEnd(fHandle, message)
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
        fHandle.write(";")      # Cpp 需要再类型定义最后写入分号 ";"


    # 写入成员声明
    @staticmethod
    def exportMemDecl(fHandle, message):
        # 写入类的成员
        for member in message.getMemberList():
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            
            # 写入变量名字
            if member.getPropertyType() == PropertyType.eInt8Array:     # char aaa[] 类型的特殊，直接转换成 string aaa
                memberStr = "public {0} {1};".format(CppPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_propertyTypeKeyWord, member.getVarName())
            elif member.getPropertyType() == PropertyType.eUint8 or \
                member.getPropertyType() == PropertyType.eInt16 or \
                member.getPropertyType() == PropertyType.eUint16 or \
                member.getPropertyType() == PropertyType.eInt32 or \
                member.getPropertyType() == PropertyType.eUint32:
                memberStr = "public {0} {1};".format(CppPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_propertyTypeKeyWord, member.getVarName())
            else:       # 数组处理
                memberStr = "public {0} {1};".format(CppPropertyType2PropertyData.m_sType2PropertyData[member.getPropertyType()].m_propertyTypeKeyWord, member.getVarNameAndArray())
            
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
                memberStr = "{0} = {1};".format(selfMember.getVarName(), selfMember.getDefaultValue())
            elif selfMember.getPropertyType() == PropertyType.eInt8Array:
                memberStr = "{0} = {1};".format(selfMember.getVarName(), "\"\"")
            else:   # 其它的数组
                memberStr = "{0} = new {1}[{2}];".format(selfMember.getVarName(), CppPropertyType2PropertyData.m_sType2PropertyData[selfMember.getPropertyType()].m_propertyTypeKeyWord, selfMember.getArrLen())
                
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

