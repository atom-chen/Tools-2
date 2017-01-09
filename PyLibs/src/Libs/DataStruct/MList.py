#-*- encoding=utf-8 -*-

from Libs.Core.GObject import GObject;

'''
@brief: 数组
'''

class MList(GObject):

    def __init__(self):
        super(MList, self).__init__();
        
        self.mTypeId = "MList";
        
        self.mList = [];


    def getList(self):
        return self.mList;


    def getSize(self):
        return len(self.mList);


    def add(self, item):
        self.mList.append(item); 


    def Add(self, item):
        self.mList.append(item);


    def push(self, item):
        self.mList.append(item);
    

    def Remove(self, item):
        return self.mList.remove(item);


    def Clear(self):
        self.mList = [];


    def Count(self):
        return len(self.mList);


    def length(self):
        return len(self.mList);


    def RemoveAt(self, index):
        if(index < self.length()):
            #self.mList.remove(self.mList[index]);
            del self.mList[index];


    # 该元素的位置,无则抛异常，因此需要先判断，然后再计算索引
    def IndexOf(self, item):
        idx = -1;
        # 先检查是否在列表中，如果不检查，直接使用 index ，如果没有找到会抛出异常
        if(item in self.mList):
            idx = self.mList.index(item);

        return idx;


    def Insert(self, index, item):
        if (index <= self.Count()):
            self.mList.insert(index, item);
        else:
            # 日志
            pass;


    def Contains(self, item):
        return self.mList.index(item) != -1;


    def Sort(self, comparer):
        self.mList.sort(comparer);
        
    
    def merge(self, rhl):
        for item in rhl.getList():
            self.Add(item);

    
    def __getitem__(self, index):
        if(index < self.length()):
            return self.mList[index];
        
        return None;
    
    
    @staticmethod
    def len(listData):
        return len(listData);
    
        
    