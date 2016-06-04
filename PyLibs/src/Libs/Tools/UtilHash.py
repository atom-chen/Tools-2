#-*- encoding=utf-8 -*-

'''
@brief: 哈希算法
'''

import hashlib
from Libs.Core import GObject

class UtilHash(GObject):
    
    @staticmethod
    #一个文件的 md5 码，appendContect 是需要在文件最后追加的内容
    def buildFileMd5(filepath, appendContect):
        md5hash = hashlib.md5()
        blocksize = 0x10000
        f = open(filepath, "rb")
        while True:
            data = f.read(blocksize)
            if not data:
                break
            md5hash.update(data)
            
        if(appendContect != None):
            md5hash.update(appendContect)
        
        f.close()
        return md5hash.hexdigest()

