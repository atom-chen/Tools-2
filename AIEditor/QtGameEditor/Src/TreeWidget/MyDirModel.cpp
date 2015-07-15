#include "MyDirModel.h"  

MyDirModel::MyDirModel()
{
	this->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);
}