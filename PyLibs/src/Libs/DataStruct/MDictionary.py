#-*- encoding=utf-8 -*-

'''
@brief: MDictionary
'''

from Libs.Core.GObject import GObject;

class MDictionary(GObject):
    
    def __init__(self):
        super(MDictionary, self).__init__();
        
        self.mTypeId = "MDictionary";
         
        self.m_data = {};


    def getData(self):
        return self.m_data;


    def getCount(self):
        return len(self.m_data.keys())
    

    def value(self, key):
        # Python3以后删除了has_key()方法
        #if(self.m_data.has_key(key)):
        if(key in self.m_data):
            return self.m_data[key];
        
        return None;


    def key(self, value):
        for (key_, value_) in dict.items():
            if(value_ == value):
                return key_;
        
        return None;


    def Add(self, key, value):
        self.m_data[key] = value;


    def Remove(self, key):
        if(self.m_data.has_key(key)):
            del self.m_data[key];

    def Clear(self):
        #self.m_data = {};
        #del self.m_data;
        self.m_data.clear();


    def ContainsKey(self, key):
        return self.m_data.has_key(key);


    def ContainsValue(self, value):
        for (key_, value_) in self.m_data.items():
            if(value_ == value):
                return True;
        
        return False;
        
        
    def keys(self):
        return self.m_data.keys();
    
    
    def values(self):
        return self.m_data.values();
    
    def items(self):
        return self.m_data.items();
    
    def copy(self):
        return self.m_data.copy();



