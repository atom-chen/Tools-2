#include "UtilEncode.h"

QString UtilEncode::qLocal2QUnicode(QString inStr)
{
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QTextCodec *unicodeCodec = QTextCodec::codecForName("UTF-8");
	return gbk->toUnicode(inStr.toStdString().c_str());
}

QString UtilEncode::qUnicode2QLocal(QString inStr)
{
	QTextCodec *gbk = QTextCodec::codecForName("GB18030");
	QByteArray gbkby = gbk->fromUnicode(inStr);
	return gbkby;
}

QString UtilEncode::sLocal2QUnicode(std::string src)
{
	return qLocal2QUnicode(src.c_str());
}

std::string UtilEncode::qUnicode2SLocal(QString src)
{
	QString localQStr = qUnicode2QLocal(src);
	return localQStr.toStdString().c_str();
}