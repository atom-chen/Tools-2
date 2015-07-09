#include "MyBasicFileSystemModel.h"  

MyBasicFileSystemModel::MyBasicFileSystemModel()
{
	this->setReadOnly(false);	// 设置只读属性
	//this->setFilter(QDir::Dirs);		// 只显示当前目录
	//this->setFilter(QDir::AllEntries);
	this->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);        //只显示文件夹  

	// 设置过滤器,这个如果只显示目录的时候设置这个就会有问题，树中显示不全
	//QStringList filter;
	//filter << "*.png" << "*.jpg" << "*.bmp" << "*.gif" << "*.*";
	//this->setNameFilters(filter);

	// 没有通过过滤器的文件disable还是隐藏,true为disable false为隐藏  
	this->setNameFilterDisables(false);
	this->setRootPath(QStringLiteral("E:/Self"));		// 设置显示目录， QFileSystemModel 模型，必须通过 setRootPath 设置根目录
}