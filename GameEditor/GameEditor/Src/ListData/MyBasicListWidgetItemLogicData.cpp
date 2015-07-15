#include "MyBasicListWidgetItemLogicData.h"

MyBasicListWidgetItemLogicData::MyBasicListWidgetItemLogicData()
{
	m_bFile = true;
}

MyBasicListWidgetItemLogicData::~MyBasicListWidgetItemLogicData()
{

}

void MyBasicListWidgetItemLogicData::setFullPath(std::string path)
{
	m_fullPathAndName = path;
}

std::string MyBasicListWidgetItemLogicData::getFullPath()
{
	return m_fullPathAndName;
}

void MyBasicListWidgetItemLogicData::setBFile(bool bFile_)
{
	m_bFile = bFile_;
}

bool MyBasicListWidgetItemLogicData::getBFile()
{
	return m_bFile;
}