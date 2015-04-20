#include <QtWidgets>
#include <QTranslator>

#include <intrin.h>
#include <locale.h>

#include "MainWindow.h"

#if _MSC_VER >= 1600
	#pragma execution_character_set("utf-8")
#endif

int main(int argc, char *argv[])
{
	// 因为 boost 在调试环境中没有获取 exe 目录的接口，都是获取当前目录，而当前目录又是工程所在的目录，在工程中设置调试目录也不行，只能挂载进程调试
	// _asm INT 3; //调用断点中断
#if WIN32
	//__debugbreak();
#endif
	setlocale(LC_ALL, "chs");		// c 中文目录文件操作

	#if QT_VERSION < QT_VERSION_CHECK(5,0,0)  
		#if defined(_MSC_VER) && (_MSC_VER < 1600)  
			QTextCodec::setCodecForTr(QTextCodec::codecForName("GB18030-0"));
		#else  
			QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
		#endif  
	#endif  

	QApplication* pApp = new QApplication(argc, argv);
	QTranslator translator(0);
	translator.load("RunPath/languages/qt_zh.qm");
	pApp->installTranslator(&translator);
	MainWindow* pMainWindow = new MainWindow();
	pMainWindow->show();

	return pApp->exec();
}