﻿#-*- encoding=utf-8 -*-

'''
@brief 文件日志
'''

from Libs.Log.LogDeviceBase import LogDeviceBase
from Libs.Tools.UtilApi import UtilApi
from Libs.Log.LogColor import LogColor

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
        path = UtilApi.getcwd();
        self.checkDirSize(path); # 检查目录大小
        
        if (not UtilApi.exists(path)):
            UtilApi.mkdir(path);

        file = "";
        if (UtilApi.exists(file) and UtilApi.isfile(file)):
            File.Delete(file);
            m_fileStream = new FileStream(file, FileMode.Create);
        else:
            m_fileStream = new FileStream(file, FileMode.Create);

        m_streamWriter = new StreamWriter(m_fileStream);


    def closeDevice(self):
        m_streamWriter.Flush();
        m_streamWriter.Close();
        m_fileStream.Close();


    # 写文件
    def logout(self, message, type = LogColor.LOG):
        if (m_streamWriter != None):
            m_streamWriter.Write(message);
            m_streamWriter.Write("\n");
            m_streamWriter.Flush();


    # 检测日志目录大小，如果太大，就删除
    def checkDirSize(self, path):
        if (UtilApi.exists(path)):
            DirectoryInfo dirInfo = new DirectoryInfo(path);
            size = 0;
            # 所有文件大小
            FileInfo[] fis = dirInfo.GetFiles();
            foreach (FileInfo fi in fis)
                Size += fi.Length;

            # 如果超过限制就删除
            if (size > 10 * 1024 * 1024):
                for fi in fis:
                    try:
                        fi.Delete();
                    catch Exception err:

                        Ctx.m_instance.m_logSys.log(string.Format("删除文件 {0} 出错", fi.FullName));







