# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'D:\file\opensource\unity-game-git\unitygame\Tools\FileDirDiff\FileDirDiff\src\FileDirDiff\UI\LeftFnWin.ui'
#
# Created: Fri Apr 24 22:39:35 2015
#      by: PyQt5 UI code generator 5.4
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_LeftFnWin(object):
    def setupUi(self, LeftFnWin):
        LeftFnWin.setObjectName("LeftFnWin")
        LeftFnWin.resize(235, 300)
        self.verticalLayoutWidget = QtWidgets.QWidget()
        self.verticalLayoutWidget.setObjectName("verticalLayoutWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setObjectName("verticalLayout")
        self.m_btnCheck = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.m_btnCheck.setObjectName("m_btnCheck")
        self.verticalLayout.addWidget(self.m_btnCheck)
        self.m_btnCopy = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.m_btnCopy.setObjectName("m_btnCopy")
        self.verticalLayout.addWidget(self.m_btnCopy)
        self.m_btnDiff = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.m_btnDiff.setObjectName("m_btnDiff")
        self.verticalLayout.addWidget(self.m_btnDiff)
        LeftFnWin.setWidget(self.verticalLayoutWidget)

        self.retranslateUi(LeftFnWin)
        QtCore.QMetaObject.connectSlotsByName(LeftFnWin)

    def retranslateUi(self, LeftFnWin):
        _translate = QtCore.QCoreApplication.translate
        LeftFnWin.setWindowTitle(_translate("LeftFnWin", "function"))
        self.m_btnCheck.setText(_translate("LeftFnWin", "Test Btn"))
        self.m_btnCopy.setText(_translate("LeftFnWin", "Copy File"))
        self.m_btnDiff.setText(_translate("LeftFnWin", "Build Diff"))

