# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'E:\01_lgh\Pro_File\PackEff\PackEff\src\pack\ui\EffDialog.ui'
#
# Created: Sat Apr 13 18:29:02 2013
#      by: pyside-uic 0.2.14 running on PySide 1.1.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(590, 428)
        self.m_btnEPack = QtGui.QPushButton(Dialog)
        self.m_btnEPack.setGeometry(QtCore.QRect(40, 30, 121, 51))
        self.m_btnEPack.setObjectName("m_btnEPack")
        self.m_btnCPack = QtGui.QPushButton(Dialog)
        self.m_btnCPack.setGeometry(QtCore.QRect(190, 30, 121, 51))
        self.m_btnCPack.setObjectName("m_btnCPack")
        self.verticalLayoutWidget = QtGui.QWidget(Dialog)
        self.verticalLayoutWidget.setGeometry(QtCore.QRect(10, 10, 571, 411))
        self.verticalLayoutWidget.setObjectName("verticalLayoutWidget")
        self.m_verticalLayout = QtGui.QVBoxLayout(self.verticalLayoutWidget)
        self.m_verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.m_verticalLayout.setObjectName("m_verticalLayout")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QtGui.QApplication.translate("Dialog", "Dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.m_btnEPack.setText(QtGui.QApplication.translate("Dialog", "effect pack", None, QtGui.QApplication.UnicodeUTF8))
        self.m_btnCPack.setText(QtGui.QApplication.translate("Dialog", "char pack", None, QtGui.QApplication.UnicodeUTF8))

