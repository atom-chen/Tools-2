#-*- encoding=utf-8 -*-

'''
@brief: 测试目录
'''

from Libs.Tools.UtilPath import UtilPath;
from Libs.Tools.UtilStr import UtilStr;
from Libs.Core.GObject import GObject;

class TestPath(GObject):
    
    def __init__(self):
        super(TestPath, self).__init__();
        
        self.mTypeId = "TestUtil";


    def run(self):
        #self.test();
        self.testMkdir();


    def test(self):
        UtilPath.traverseDirectory(
                                   "E:/Self/Self/unity/unitygame/Client_Start/Assets/uLua/Lua", 
                                   None, 
                                   None, 
                                   None, 
                                   None, 
                                   self, 
                                   self.traversePathHandle, 
                                   True
                                   );
        
    def traversePathHandle(self, srcPath, destPath):
        pathNoExt, ext = UtilPath.splitext(srcPath);
        if(ext == ".lua"):
            txtPath = UtilStr.format("{0}{1}", pathNoExt, ".txt");
            UtilPath.rename(srcPath, txtPath);

    
    def testMkdir(self):
        srcPath = "E:/Self/Self/unity/unitygame/Client_Start/Assets/Resources/lua";
        UtilPath.mkdir(srcPath);

        srcPath = "E:/Self/Self/unity/unitygame/Client_Start/Assets/Resources/lua/aaa/bbb";
        UtilPath.makedirs(srcPath);
        
        print("end");

