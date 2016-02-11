# -*- coding: utf-8 -*-

'''
@brief 矩形区域，主要进行图像拼接的时候计算包围大小
'''

class stRect(object):
    def __init__(self):
        self.m_x = 0
        self.m_y = 0
        self.m_width = 0
        self.m_height = 0
        self.m_curHeight = 0

    # 扩展高度
    def extHeight(self, height, nextline):
        if nextline:
            self.m_curHeight = height
            self.m_height += height
        elif self.m_curHeight < height:
            self.m_curHeight = height
            self.m_height += (height - self.m_curHeight)
        
    def extWidth(self, width):
        self.m_width += width
        
    def reset(self):
        self.m_x = 0
        self.m_y = 0
        self.m_width = 0
        self.m_height = 0
        self.m_curHeight = 0
