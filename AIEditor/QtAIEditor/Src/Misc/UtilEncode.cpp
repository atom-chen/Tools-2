#include "UtilEncode.h"

QString UtilEncode::local2Unicode(QString inStr)
{
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *unicodeCodec = QTextCodec::codecForName("UTF-8");
	return gbk->toUnicode(inStr.toStdString().c_str());
}

QString UtilEncode::unicode2Local(QString inStr)
{
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QByteArray gbkby = gbk->fromUnicode(inStr);
	return gbkby;
}