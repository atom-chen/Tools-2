# -*- coding: utf-8 -*-
'''
Created on 2013-4-7

@author: Administrator
@brief 启动
'''

import sys
#sys.path.append('E:/work/client-05/trunk/tools/python脚本/packeff/PackEff/src')
from PyQt5 import QtCore, QtGui, QtWidgets
from Pack.Frame.MainDialog import MainDialog
from Pack.Frame.Config import Config

# 初始化所有信息
def init():
    #pystart = sys.argv[0].find('.py')
    #if pystart != -1:
    #    Config.instance().initPath(Config.MainPy)
    #else:   # 应该是 exe 吧
    #    Config.instance().initPath(Config.MainExe)
    # 读取配置文件名字
    Config.instance().readInit(Config.instance().configFile)
    Config.instance().readCharNameFile(Config.instance().charNameFile)
    Config.instance().readEffNameFile(Config.instance().effNameFile)
    Config.instance().readTerNameFile(Config.instance().terNameFile)

def main():
    init()
    QtCore.QTextCodec.setCodecForLocale(QtCore.QTextCodec.codecForName("utf8"))
    QtCore.QTextCodec.setCodecForCStrings(QtCore.QTextCodec.codecForName("utf8"))
    QtCore.QTextCodec.setCodecForTr(QtCore.QTextCodec.codecForName("utf8"))
    app = QtWidgets.QApplication(sys.argv)
    dialog = MainDialog()
    dialog.show()
    sys.exit(app.exec_())
    
#if __name__ == "__main__":
main()

