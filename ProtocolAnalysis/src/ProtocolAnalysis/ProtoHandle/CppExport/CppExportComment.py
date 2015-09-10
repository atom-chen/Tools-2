#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase


class CppExportComment(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''
    
    
    @staticmethod
    # 导出注释
    def exportComment(fHandle, message):
        if len(message.getCommentList()) > 0:
            for commentStr in message.getCommentList():
                AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                AppSysBase.instance().getClsUtils().writeTab2File(fHandle)
                fHandle.write(commentStr)
    
    
    
        