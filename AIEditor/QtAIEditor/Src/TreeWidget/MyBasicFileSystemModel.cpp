#include "MyBasicFileSystemModel.h"  

MyBasicFileSystemModel::MyBasicFileSystemModel()
{
	this->setReadOnly(false);	// ����ֻ������
	//this->setFilter(QDir::Dirs);		// ֻ��ʾ��ǰĿ¼
	//this->setFilter(QDir::AllEntries);
	this->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);        //ֻ��ʾ�ļ���  

	// ���ù�����,������ֻ��ʾĿ¼��ʱ����������ͻ������⣬������ʾ��ȫ
	//QStringList filter;
	//filter << "*.png" << "*.jpg" << "*.bmp" << "*.gif" << "*.*";
	//this->setNameFilters(filter);

	// û��ͨ�����������ļ�disable��������,trueΪdisable falseΪ����  
	this->setNameFilterDisables(false);
	this->setRootPath(QStringLiteral("E:/Self"));		// ������ʾĿ¼�� QFileSystemModel ģ�ͣ�����ͨ�� setRootPath ���ø�Ŀ¼
}