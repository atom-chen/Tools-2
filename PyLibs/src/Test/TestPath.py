#-*- encoding=utf-8 -*-

'''
@brief: 测试目录
'''

from Libs.Tools.UtilPath import UtilPath
from Libs.Tools.UtilStr import UtilStr

class TestPath(object):
    def test(self):
        UtilPath.recurseTraverseDirectory("E:/Self/Self/unity/unitygame/Client_Start/Assets/uLua/Lua", None, self, self.traversePathHandle);
        
    def traversePathHandle(self, srcPath, destPath):
        pathNoExt, ext = UtilPath.splitext(srcPath);
        if(ext == ".lua"):
            txtPath = UtilStr.format("{0}{1}", pathNoExt, ".txt");
            UtilPath.rename(srcPath, txtPath);


testPath = TestPath();
testPath.test();

