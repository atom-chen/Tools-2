#-*- encoding=utf-8 -*-

'''
@brief: 测试目录
'''

from Libs.Tools.UtilPath import UtilPath

class TestPath(object):
    def test(self):
        UtilPath.recurseTraverseDirectory("E:/Self/Self/unity/unitygame/Client_Start/Assets/uLua/Lua", None, self, self.traversePath);
        
    def traversePath(self, srcPath, destPath):
        pass;


testPath = TestPath();
testPath.test();

