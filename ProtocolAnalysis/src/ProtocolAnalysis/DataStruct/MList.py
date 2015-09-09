#-*- encoding=utf-8 -*-


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
        
    
    # 添加一个元素
    def append(self, elem):
        self.m_list.append(elem)

    
    # 移除一个元素
    def remove(self, elem):
        self.m_list.remove(elem)
    
    
    # 根据索引移除一个元素
    def removeAt(self, idx):
        if idx < len(self.m_list):
            del self.m_list[idx]
    
    