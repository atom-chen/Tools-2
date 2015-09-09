#-*- encoding=utf-8 -*-


from ProtocolAnalysis.Core.Utils import Utils


# List 包装
class MList(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''
        self.m_list = []
        self.list = self.m_list         # 建立一个连接
        
    
    def __getattr__(self, name):
        attrName = Utils.addMemberPrefix(name)
        return self.__dict__[attrName]
    
    
    def __setattr__(self, name, value):
        attrName = Utils.addMemberPrefix(name)
        self.__dict__[attrName] = value
        
    
    # 添加一个元素
    def append(self, elem):
        self.m_list.append(elem)
        
    
    def Add(self, elem):
        self.append(elem)

    
    # 移除一个元素
    def remove(self, elem):
        if self.elemInList(elem):
            self.m_list.remove(elem)
            return True
            
        return False
    
    
    # 根据索引移除一个元素
    def removeAt(self, idx):
        if idx < len(self.m_list):
            del self.m_list[idx]
            
    # 从列表中找出某个值第一个匹配项的索引位置
    def index(self, elem):
        return self.m_list.index(elem)
    
    
    # 将对象插入列表
    def insert(self, index, elem):
        if index < self.len():
            self.m_list.insert(index, elem)
        else:
            self.append(elem)
        
    
    # 获取列表的长度
    def len(self):
        return len(self.m_list)
    
    
    # 获取列表的长度
    def Count(self):
        self.len()
        
        
    def Clear(self):
        del self.m_list[:]
    
    
    # 元素是否存在于列表中，如果存在就返回 True
    def elemInList(self, elem):
        return elem in self.m_list
    
    
    # 统计某个元素在列表中出现的次数
    def elemCount(self, elem):
        self.m_list.count(elem)
        
        
    # 移除列表中的一个元素（默认最后一个元素），并且返回该元素的值
    def pop(self):
        self.m_list.pop()
        
        
    # 反向列表中元素
    def reverse(self):
        self.m_list.reverse()
        
        
    # 对原列表进行排序
    def sort(self, func):
        self.m_list.sort(func)

