#include "TabSubWidgetLogicData.h"

TabSubWidgetLogicData::TabSubWidgetLogicData()
{

}

TabSubWidgetLogicData::~TabSubWidgetLogicData()
{

}

void TabSubWidgetLogicData::setFullPath(std::string path)
{
	m_fullPathAndName = path;
}

std::string TabSubWidgetLogicData::getFullPath()
{
	return m_fullPathAndName;
}