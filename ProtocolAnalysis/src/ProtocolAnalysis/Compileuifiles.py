# -*- coding: utf-8 -*-

import os
from PyQt5.uic import compileUi

def compileUIFiles(uiDir):
    for name in os.listdir(uiDir):
        uiFilePath = os.path.join(uiDir, name)

        if os.path.isfile(uiFilePath):
            if name.endswith(".ui"):
                uiResultPath = ('ui_' + name[:-3] + ".py").lower()

                with open(os.path.join(uiDir, uiResultPath), "w") as f:
                    compileUi(uiFilePath, f)

def main():
    from ProtocolAnalysis import Paths

    compileUIFiles(Paths.UI_DIR)

if __name__ == "__main__":
    main()
