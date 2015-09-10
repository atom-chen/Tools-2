#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.ProtoHandle.ProtoBase.ProtoElemBase import eProtoElemType

class CppExportPragma(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''


    @staticmethod
    def exportPragmaBeforeNS(fHandle, file):
        bFirst = True
        for message in file.getProtoElemList():
            if message.getElemType() == eProtoElemType.ePackage:
                break
            elif message.getElemType() == eProtoElemType.ePragma:
                for pragma in message.getPragmaList():
                    if bFirst:          # 添加一个间隔空行
                        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                        
                    # 下一行写入
                    AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                    pragmaFull = "#pragma {0}".format(pragma)
                    fHandle.write(pragmaFull)
                    
                    bFirst = False

              
              
    @staticmethod
    def exportPragmaMidNS(fHandle, message):
        bFirst = False
        for pragma in message.getPragmaList():
            if bFirst:          # 添加一个间隔空行
                AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                
            # 下一行写入
            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
            pragmaFull = "#pragma {0}".format(pragma)
            fHandle.write(pragmaFull)
            
            bFirst = False
                    
                    
                    
    @staticmethod
    def exportPragmaAfterNS(fHandle, file):
        bFirst = True
        bFindNS = False
        for message in file.getProtoElemList():
            if message.getElemType() == eProtoElemType.ePackage:
                bFindNS = True
            elif message.getElemType() == eProtoElemType.ePragma:
                if bFindNS:
                    for pragma in message.getPragmaList():
                        if bFirst:          # 添加一个间隔空行
                            AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                        
                        AppSysBase.instance().getClsUtils().writeNewLine2File(fHandle)
                        pragmaFull = "#pragma {0}".format(pragma)
                        fHandle.write(pragmaFull)

