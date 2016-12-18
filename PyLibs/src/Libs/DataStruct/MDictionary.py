#-*- encoding=utf-8 -*-

'''
@brief: MDictionary
'''

from Libs.Core.GObject import GObject;

class MDictionary(GObject):
    
    def __init__(self):
        super(MDictionary, self).__init__();
        
        self.mTypeId = "MDictionary";
         
        self.mData = {};


    def getData(self):
        return self.mData;


    def getCount(self):
        return len(self.mData.keys())
    

    def value(self, key):
        # Python3以后删除了has_key()方法
        #if(self.mData.has_key(key)):
        if(key in self.mData):
            return self.mData[key];
        
        return None;


    def key(self, value):
        for (key_, value_) in dict.items():
            if(value_ == value):
                return key_;
        
        return None;


    def Add(self, key, value):
        self.mData[key] = value;


    def Remove(self, key):
        if(self.mData.has_key(key)):
            del self.mData[key];

    def Clear(self):
        #self.mData = {};
        #del self.mData;
        self.mData.clear();


    def ContainsKey(self, key):
        return self.mData.has_key(key);


    def ContainsValue(self, value):
        for (key_, value_) in self.mData.items():
            if(value_ == value):
                return True;
        
        return False;
        
        
    def keys(self):
        return self.mData.keys();
    
    
    def values(self):
        return self.mData.values();
    
    def items(self):
        return self.mData.items();
    
    def copy(self):
        return self.mData.copy();



