#include "MyBasicFileSystemModel.h"  

MyBasicFileSystemModel::MyBasicFileSystemModel()
{
	this->setReadOnly(false);
	this->setFilter(QDir::Dirs);
}