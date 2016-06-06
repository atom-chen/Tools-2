# -*- coding: utf-8 -*-

'''
@brief 文件日志
'''

from Libs.Log.LogDeviceBase import LogDeviceBase
from Libs.Log.LogColor import LogColor
from Libs.Tools.UtilPath import UtilPath
from Libs.FileSystem.MDataStream import MDataStream
from Libs.FileSystem.MFileMode import MFileMode
from Libs.FrameWork.Ctx import Ctx
from Libs.Tools.UtilStr import UtilStr

class FileLogDevice(LogDeviceBase):

    def __init__(self):
        super(FileLogDevice, self).__init__();
        
        self.mTypeId = "FileLogDevice";
        
        self.m_filePrefix = "log";


    def getFileSuffix(self):
        return self.m_fileSuffix;

    def setFileSuffix(self, value):
        self.m_fileSuffix = value;


    def getFilePrefix(self):
        return self.m_filePrefix; 


    def setFilePrefix(self, value):
        self.m_filePrefix = value;


    def initDevice(self):
        path = UtilPath.getcwd();
        self.checkDirSize(path); # 检查目录大小
        
        if (not UtilPath.exists(path)):
            UtilPath.mkdir(path);

        file = "";
        if (UtilPath.exists(file) and UtilPath.isfile(file)):
            UtilPath.deleteFile(file);
            self.m_fileStream = MDataStream(file, MFileMode.WriteTxt);
        else:
            self.m_fileStream = MDataStream(file, MFileMode.WriteAppend);


    def closeDevice(self):
        self.m_fileStream.close();


    # 写文件
    def logout(self, message, logType = LogColor.LOG):
        if (self.m_fileStream != None):
            self.m_fileStream.writeLine(message);
            self.m_fileStream.Flush();


    # 检测日志目录大小，如果太大，就删除
    def checkDirSize(self, path):
        if (UtilPath.exists(path)):
            size = 0;
            # 所有文件大小
            fileList = UtilPath.getAllFile();
            for file in fileList:
                size = size + file.mLength;

            # 如果超过限制就删除
            if (size > 10 * 1024 * 1024):
                for file in fileList:
                    try:
                        UtilPath.deleteFile(file.mFullPath);
                    except:
                        Ctx.instance().m_logSys.log(UtilStr.format("删除文件 {0} 出错", file.mFullPath));







