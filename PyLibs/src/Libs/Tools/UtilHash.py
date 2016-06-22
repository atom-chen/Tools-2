#-*- encoding=utf-8 -*-

'''
@brief: 哈希算法
'''

import hashlib;
from Libs.Core.GObject import GObject;
from Libs.FileSystem.MDataStream import MDataStream;
from Libs.FileSystem.MFileMode import MFileMode;

class UtilHash(GObject):
    
    @staticmethod
    #一个文件的 md5 码，appendContect 是需要在文件最后追加的内容
    def buildFileMd5(filepath, appendContect = None):
        md5hash = hashlib.md5();
        blocksize = 0x10000;
        dataStream = MDataStream(filepath, MFileMode.ReadBin);
        while True:
            data = dataStream.read(blocksize);
            if not data:
                break;
            md5hash.update(data);
            
        if(appendContect != None):
            md5hash.update(appendContect);
        
        dataStream.close();
        return md5hash.hexdigest();

