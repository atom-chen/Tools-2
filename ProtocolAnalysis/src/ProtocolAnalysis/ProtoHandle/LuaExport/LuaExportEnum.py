#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class LuaExportEnum(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''

    @staticmethod
    # 导出 enum
    def exportEnum(fHandle, message):
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        clsName = "public enum {0}".format(message.getTypeName())
        fHandle.write(clsName)
        
        # 输入左括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeLBrace2File(fHandle)
        
        # 写入类的成员
        for member in message.getMemberList():
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
            
            # 写入变量名字
            memberStr = "{0} = {1},".format(member.getVarName(), member.getDefaultValue())
            fHandle.write(memberStr)
            #写入注释
            if not AppSysBase.instance().getClsUtils().isNullOrEmpty(member.getCommentStr()):   # 如果字符串不为空
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
                fHandle.write(member.getCommentStr())

        
        # 写入枚举的右括号
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
        AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
        AppSysBase.instance().getClsUtils().writeRBrace2File(fHandle)
        
        # 输入一个空行，以便隔开
        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
    
    