#-*- encoding=utf-8 -*-


class MDictionary(object):
    '''
    classdocs
    '''


    def __init__(self, params):
        '''
        Constructor
        '''
        self.m_dict = {}
        
    def __getitem__(self, key):
        if self.ContainsKey(key):
            return self.m_dict[key]
        
        return None
    
    def __setitem__(self, key, value):  
        self.m_dict[key] = value; 
        
    
    # 删除键是'Name'的条目
    def Remove(self, key):
        del self.m_dict[key]
        

    # 清空词典所有条目
    def Clear(self):
        self.m_dict.clear();


    # 删除词典
    def dispose(self):
        del self.m_dict

    # 计算字典元素个数，即键的总数
    def Count(self):
        len(self.m_dict)
        
    
    def Add(self, key, value):
        self.m_dict[key] = value


    # 如果键在字典dict里返回true，否则返回false
    def ContainsKey(self, key):
        return self.m_dict.has_key(key)

        
    def ContainsValue(self, value):
        return value in self.m_dict.values


    def Keys(self):
        return self.m_dict.keys()
    
    
    def Values(self):
        return self.m_dict.values()


    def TryGetValue(self, key, value):
        if self.ContainsKey(key):
            value = self.m_dict[key]
            return True
        else:
            value = None
            return False

    def items(self):
        return self.items()



