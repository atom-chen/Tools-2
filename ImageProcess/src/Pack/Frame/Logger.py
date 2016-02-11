# -*- coding: utf-8 -*-

'''
@brief 日志类
'''

from threading import Lock
import sys

class Logger(object):
    pInstance = None
     
    @classmethod
    def instance(cls):
        if cls.pInstance is None:
            cls.pInstance = cls()
            
        return cls.pInstance
    
    def __init__(self):
        self.m_effLock = Lock()
        self.m_charLock = Lock()
        self.m_terLock = Lock()
        
        self.m_effLog = []
        self.m_charLog = []
        self.m_terLog = []
        
        self.m_charLogFile = None
        self.m_effLogFile = None
        self.m_terLogFile = None
    
    def loggerEff(self, desc):
        if not desc is None:
            self.m_effLock.acquire()
            if isinstance(desc, list):
                desc = ''.join(desc)
            if isinstance(desc, bytes):
                try:
                    desc = desc.decode("utf-8")
                except:
                    desc = desc.decode("gbk")
            if len(desc):
                self.m_effLog.append(desc)
            self.m_effLock.release()
        
    def loggerChar(self, desc):
        if not desc is None:
            self.m_charLock.acquire()
            if isinstance(desc, list):
                desc = ''.join(desc)
            if isinstance(desc, bytes):
                try:
                    desc = desc.decode("utf-8")
                except:
                    desc = desc.decode("gbk")
            if len(desc):
                self.m_charLog.append(desc)
            self.m_charLock.release()
        
    def loggerTer(self, desc):
        if not desc is None:
            self.m_terLock.acquire()
            if isinstance(desc, list):
                desc = ''.join(desc)
            if isinstance(desc, bytes):
                try:
                    desc = desc.decode("utf-8")
                except:
                    desc = desc.decode("gbk")
            if len(desc):
                self.m_terLog.append(desc)
            self.m_terLock.release()
 
    def getloggerEff(self, loglist):
        self.m_effLock.acquire()
        for log in self.m_effLog:
            loglist.append(log)
        del self.m_effLog[:]
        self.m_effLock.release()
        
    def getloggerChar(self, loglist):
        self.m_charLock.acquire()
        for log in self.m_charLog:
            loglist.append(log)
        del self.m_charLog[:]
        self.m_charLock.release()
    
    def getloggerTer(self, loglist):
        self.m_terLock.acquire()
        for log in self.m_terLog:
            loglist.append(log)
        del self.m_terLog[:]
        self.m_terLock.release()
        
    #向子进程中输出日志
    def loggerCSubPro(self, desc):
        filename = 'charlog.txt'
        if self.m_charLogFile is None:
            self.m_charLogFile = open(filename, 'wt', encoding='utf8')
        
        # 写日志文件
        self.m_charLogFile.write(desc)
        self.m_charLogFile.write('\n')
        self.m_charLogFile.flush()
        # 写标准输出
        sys.stdout.write(desc)
        sys.stdout.write('\n')
        sys.stdout.flush()

    #关闭子进程文件日志写
    def loggerCCloseSubPro(self):
        if not self.m_charLogFile is None:
            self.m_charLogFile.close()
            
    #向子进程中输出日志
    def loggerESubPro(self, desc):
        filename = 'efflog.txt'
        if self.m_effLogFile is None:
            self.m_effLogFile = open(filename, 'wt', encoding='utf8')
        
        # 写日志文件
        self.m_effLogFile.write(desc)
        self.m_effLogFile.write('\n')
        self.m_effLogFile.flush()
        # 写标准输出
        desc = desc.encode('gbk')
        sys.stdout.write(desc.decode('gbk'))
        sys.stdout.write('\n')
        sys.stdout.flush()

    #关闭子进程文件日志写
    def loggerECloseSubPro(self):
        if not self.m_effLogFile is None:
            self.m_effLogFile.close()

    #向子进程中输出日志
    def loggerTSubPro(self, desc):
        filename = 'terlog.txt'
        if self.m_terLogFile is None:
            self.m_terLogFile = open(filename, 'wt', encoding='utf8')
        
        # 写日志文件
        self.m_terLogFile.write(desc)
        self.m_terLogFile.write('\n')
        self.m_terLogFile.flush()
        # 写标准输出
        sys.stdout.write(desc)
        sys.stdout.write('\n')
        sys.stdout.flush()

    #关闭子进程文件日志写
    def loggerTCloseSubPro(self):
        if not self.m_terLogFile is None:
            self.m_terLogFile.close()
