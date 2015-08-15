#include "TabSubWidgetLogicData.h"

BEGIN_NAMESPACE_GAMEEDITOR

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

END_NAMESPACE_GAMEEDITOR