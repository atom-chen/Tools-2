# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'E:\Self\Self\Tools\Tools\ProtocolAnalysis\src\ProtocolAnalysis\UI\LeftFnWin.ui'
#
# Created: Wed Sep 16 12:21:31 2015
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
        self.m_pushButtonExportCpp = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.m_pushButtonExportCpp.setObjectName("m_pushButtonExportCpp")
        self.verticalLayout.addWidget(self.m_pushButtonExportCpp)
        self.m_pushButtonExportCS = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.m_pushButtonExportCS.setObjectName("m_pushButtonExportCS")
        self.verticalLayout.addWidget(self.m_pushButtonExportCS)
        self.m_btnCopyFile = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.m_btnCopyFile.setObjectName("m_btnCopyFile")
        self.verticalLayout.addWidget(self.m_btnCopyFile)
        self.m_btnConvFile = QtWidgets.QPushButton(self.verticalLayoutWidget)
        self.m_btnConvFile.setObjectName("m_btnConvFile")
        self.verticalLayout.addWidget(self.m_btnConvFile)
        LeftFnWin.setWidget(self.verticalLayoutWidget)

        self.retranslateUi(LeftFnWin)
        QtCore.QMetaObject.connectSlotsByName(LeftFnWin)

    def retranslateUi(self, LeftFnWin):
        _translate = QtCore.QCoreApplication.translate
        LeftFnWin.setWindowTitle(_translate("LeftFnWin", "function"))
        self.m_pushButtonExportCpp.setText(_translate("LeftFnWin", "ExportCpp"))
        self.m_pushButtonExportCS.setText(_translate("LeftFnWin", "ExportCS"))
        self.m_btnCopyFile.setText(_translate("LeftFnWin", "Copy File"))
        self.m_btnConvFile.setText(_translate("LeftFnWin", "Conv File"))

