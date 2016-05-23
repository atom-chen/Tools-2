'''
@brief: 类型之间相互转换
'''

class MConvert(object):

    @staticmethod
    def str2Float(srcStr):
        return float(srcStr);
    
    
    @staticmethod
    def str2Int(srcStr, base = 10):
        return int(srcStr, base);
    
    
    @staticmethod
    def str2Long(srcStr, base = 10):
        #return long(srcStr, base);
        pass;
    

    @staticmethod
    def list2Tuple(lst):
        return tuple(lst);

    @staticmethod
    def tuple2List(tple):
        return list(tple);
