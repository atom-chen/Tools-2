#-*- encoding=utf-8 -*-

from Libs.Core.GObject import GObject

'''
@brief: 数组
'''

class MList(GObject):

    def __init__(self):
        super(MList, self).__init__();
        
        self.mTypeId = "MList";
        
        self.m_list = [];


    def getList(self):
        return self.m_list;


    def getSize(self):
        return len(self.m_list);


    def add(self, item):
        self.m_list.append(item); 


    def Add(self, item):
        self.m_list.append(item);


    def push(self, item):
        self.m_list.append(item);
    

    def Remove(self, item):
        return self.m_list.remove(item);


    def Clear(self):
        self.m_list = [];


    def Count(self):
        return len(self.m_list);


    def length(self):
        return len(self.m_list);


    def RemoveAt(self, index):
        if(index < self.length()):
            #self.m_list.remove(self.m_list[index]);
            del self.m_list[index];


    # 该元素的位置,无则抛异常，因此需要先判断，然后再计算索引
    def IndexOf(self, item):
        idx = -1;
        # 先检查是否在列表中，如果不检查，直接使用 index ，如果没有找到会抛出异常
        if(item in self.m_list):
            idx = self.m_list.index(item);

        return idx;


    def Insert(self, index, item):
        if (index <= self.Count()):
            self.m_list.insert(index, item);
        else:
            # 日志
            pass;


    def Contains(self, item):
        return self.m_list.index(item) != -1;


    def Sort(self, comparer):
        self.m_list.sort(comparer);
        
    
    def merge(self, rhl):
        for item in rhl.getList():
            self.Add(item);

    
    def __getitem__(self, index):
        if(index < self.length()):
            return self.m_list[index];
        
        return None;
    
    
    @staticmethod
    def len(listData):
        return len(listData);
    
        
    