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
	// ��Ϊ boost �ڵ��Ի�����û�л�ȡ exe Ŀ¼�Ľӿڣ����ǻ�ȡ��ǰĿ¼������ǰĿ¼���ǹ������ڵ�Ŀ¼���ڹ��������õ���Ŀ¼Ҳ���У�ֻ�ܹ��ؽ��̵���
	// _asm INT 3; //���öϵ��ж�
#if WIN32
	//__debugbreak();
#endif
	setlocale(LC_ALL, "chs");		// c ����Ŀ¼�ļ�����

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