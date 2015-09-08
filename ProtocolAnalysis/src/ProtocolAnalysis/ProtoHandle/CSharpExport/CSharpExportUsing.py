#-*- encoding=utf-8 -*-


class CSharpExportUsing(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''

    @staticmethod
    # 导出导入的命名空间
    def exportUsing(fHandle):
        # 输出导入的命名空间
        importUsing = "using SDK.Lib;"
        fHandle.write(importUsing)

