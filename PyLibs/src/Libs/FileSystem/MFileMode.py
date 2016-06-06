#-*- encoding=utf-8 -*-

'''
@brief: MFileMode
'''
from Libs.Core.GObject import GObject;

class MFileMode(GObject):

    ReadTxt = "r";      # 读文本文件
    ReadBin = "rb";     # 读二进制文件
    WriteTxt = "w";     # 写文本文件
    WriteBin = "wb";    # 写二进制文件
    WriteAppend = "r";      # 追加写文件

