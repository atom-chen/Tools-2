#include "MyBasicListWidgetItemLogicData.h"

MyBasicListWidgetItemLogicData::MyBasicListWidgetItemLogicData()
{

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