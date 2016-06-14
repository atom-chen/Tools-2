'''
@brief: TestUtil
'''

from Libs.Core.GObject import GObject
from Libs.Tools.UtilPath import UtilPath

class TestUtil(GObject):
    def __init__(self):
        super(TestUtil, self).__init__();
        
        self.mTypeId = "TestUtil";


    def run(self):
        self.testUtilPath();


    def testUtilPath(self):
        srcPath = "E:/denglu2";
        destPath = "E:/e";
        UtilPath.copyDirectory(srcPath, destPath, None, None, True);


