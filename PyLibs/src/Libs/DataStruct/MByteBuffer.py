# -*- coding: utf-8 -*-

'''
@brief: 字节缓冲区 
'''

import struct;

from Libs.Core.GObject import GObject;
from Libs.DataStruct.MByteOrder import MByteOrder;

class MByteBuffer(GObject):
    
    def __init__(self):
        super(MByteBuffer, self).__init__();
        
        self.mTypeId = "MByteBuffer";
        
        self.mEndian = MByteOrder.eLittleEndian;
        #self.mBuffer = bytearray('asfsd', 'utf-8');
        self.mBuffer = bytearray(2 * 1024, 'utf-8');
        
        
    def readInt8(self):
        if(self.mEndian == MByteOrder.eLittleEndian):
            bytes = struct.unpack("<b", self.mBuffer);

