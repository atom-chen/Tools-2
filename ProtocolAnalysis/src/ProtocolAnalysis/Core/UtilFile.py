#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.AppSysBase import AppSysBase
from ProtocolAnalysis.EventHandle.EventDispatch import EventDispatch
import os


class UtilFile(object):
    '''
    classdocs
    '''
    m_sEventDispatch = EventDispatch()
    m_dirName = ""
    m_fileName = ""
    m_fileFullPath = ""


    def __init__(self):
        '''
        Constructor
        '''

    # 访问一个目录下的文件
    @staticmethod
    def traversalOneDir(directoryName, filesInDirectory):
        AppSysBase.instance().m_logSys.info(directoryName)
        for fname in filesInDirectory:
            fpath = os.path.join(directoryName, fname)
            if not os.path.isdir(fpath):
                m_dirName = directoryName
                m_fileName = fname
                m_fileFullPath = fpath
                UtilFile.m_sEventDispatch.dispatchEvent(None)
    
    # 递归遍历整个目录
    @staticmethod
    def traversalAllDirs(startdir):
        for root, dirs, files in os.walk(startdir):
            AppSysBase.instance().m_logSys.info(''.join(dirs))
            UtilFile.traversalOneDir(root, files)


    @staticmethod
    def getEventDispatch():
        return UtilFile.m_sEventDispatch

    
    @staticmethod
    def dirName():
        return UtilFile.m_dirName

    
    @staticmethod
    def getFileName():
        return UtilFile.m_fileName
    
    
    @staticmethod
    def getFileFullPath():
        return UtilFile.m_fileFullPath

