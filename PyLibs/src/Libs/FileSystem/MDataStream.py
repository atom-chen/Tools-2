# -*- coding: utf-8 -*-

'''
@brief 本地文件系统
'''

from Libs.Core.GObject import GObject
from Libs.Tools.UtilPath import UtilPath
from Libs.Tools.UtilStr import UtilStr

class MDataStream(GObject):
    
    # In text mode, if encoding is not specified the encoding used is platform
    # dependent: locale.getpreferredencoding(False) is called to get the current locale encoding.
    def __init__(self, fileName, mode = None, encoding = None):
        super(MDataStream, self).__init__();
        
        self.mTypeId = "MDataStream";
        
        self.mFileName = fileName;
        self.mMode = mode;
        self.mEncoding = encoding;
        self.mFileHandle = None;
        
        if(self.mMode == None):
            self.mMode = "rb";
        if(self.mEncoding == None):
            self.mEncoding = "utf-8";
            
        self.open();
        
    #注：不能把open语句放在try块里，因为当打开文件出现异常时，文件对象file_object无法执行close()方法。
    def open(self):
        # 第二个参数默认为r
        #self.mFileHandle = open(self.mFileName, self.mMode, self.mEncoding);
        try:
            self.mFileHandle = open(self.mFileName, self.mMode);
        except Exception as e:
            print(UtilStr.format("MDataStream::open, error, Path is {0}", self.mFileName));
        
        
    def close(self):
        if(self.isValid()):
            self.mFileHandle.flush();
            self.mFileHandle.close();
        
        
    def isValid(self):
        return self.mFileHandle != None;
    
    
    #返回一个长整型的”文件标签
    def fileno(self):
        if(self.isValid()):
            return self.mFileHandle.fileno();
        return 0;


    #文件是否是一个终端设备文件（unix系统中的） 
    def isatty(self):
        if(self.isValid()):
            return self.mFileHandle.isatty();
        return False;
    
    
    #返回文件操作标记的当前位置，以文件的开头为原点 
    def tell(self):
        if(self.isValid()):
            return self.mFileHandle.tell();
        return 0;
    
    
    #将文件打操作标记移到offset的位置。这个offset一般是相对于文件的开头来计算的，一般为正数。
    #但如果提供了whence参数就不一定了，whence可以为0表示从头开始计算，1表示以当前位置为原点计算。
    #2表示以文件末尾为原点进行计算。需要注意，如果文件以a或a+的模式打开，每次进行写操作时，文件操作标记会自动返回到文件末尾。 
    def seek(self, offset, whence):
        if(self.isValid()):
            self.mFileHandle.seek(offset, whence);
            
            
    #把文件裁成规定的大小，默认的是裁到当前文件操作标记的位置。如果size比文件的大小还要大，依据系统的不同可能是不改变文件，
    # 也可能是用0把文件补到相应的大小，也可能是以一些随机的内容加上去。 
    def truncate(self, size):
        if(self.isValid()):
            self.mFileHandle.truncate(size);
    
    
    def getLength(self):
        if(self.isValid()):
            self.mFileHandle.seek(0, 2);
            return self.tell();
            
        return 0;
         
            
    #size为读取的长度，以byte为单位 
    def readOffset(self, start = None, size = None):
        if(self.isValid()):
            if(start != None):
                self.seek(start, 0);
            if(size == None):
                size = self.getLength();
            return self.mFileHandle.read(size);
        
        return "";
    
    
    #size为读取的长度，以byte为单位 
    def read(self, size = None):
        if(self.isValid()):
            #if(size == None):
            #    size = self.getLength();
            return self.mFileHandle.read(size);
        
        return "";
            
    #读一行，如果定义了size，有可能返回的只是一行的一部分  
    def readline(self, size):
        if(self.isValid()):
            return self.mFileHandle.readline(size)
            
        return "";
            
    #把文件每一行作为一个list的一个成员，并返回这个list。其实它的内部是通过循环调用readline()来实现的。
    #如果提供size参数，size是表示读取内容的总长，也就是说可能只读到文件的一部分。 
    def readlines(self, size):
        if(self.isValid()):
            return self.mFileHandle.readlines(size)
            
        return [];    
            
    #把str写到文件中，write()并不会在str后加上一个换行符  
    def write(self, strCon):
        if(self.isValid()):
            self.mFileHandle.write(strCon);
            
    
    def writeLine(self, strCon):
        if(self.isValid()):
            self.mFileHandle.write(strCon);
            self.mFileHandle.write(UtilPath.CRLF);    
            
    #把seq的内容全部写到文件中。这个函数也只是忠实地写入，不会在每行后面加上任何东西。 
    def writelines(self, seq):
        if(self.isValid()):
            self.mFileHandle.writelines(seq);
    
