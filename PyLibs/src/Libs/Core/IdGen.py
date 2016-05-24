#-*- encoding=utf-8 -*-

'''
@brief: IdGen
'''
from Libs.Core import GObject

class IdGen(GObject):
    # Constructor
    def __init__(self):
        self.mCurrentId = 0;


    def generateNewId(self):
        self.mCurrentId = self.mCurrentId + 1;
        return self.mCurrentId;

