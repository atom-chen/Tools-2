#include "Task.h"
#include "tinyxml2.h"
#include "XmlConfig.h"

#include "MemLeakCheck.h"

BEGIN_NAMESPACE

Task::Task()
{

}

Task::~Task()
{

}

Solution* Task::getSolution()
{
	return m_pSolution;
}

void Task::destroy()
{

}

void Task::readXML()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* configXml = NULL;
	tinyxml2::XMLElement* solutionXml = NULL;
	
	if (doc.LoadFile("Config.xml") != tinyxml2::XML_SUCCESS)
	{
		throw "Config.xml 加载失败!";
	}

	configXml = doc.FirstChildElement("config");
	if(!configXml)
	{
		throw "xml文件没有config标签";
	}

	solutionXml = configXml->FirstChildElement("solution");
	if(!solutionXml)
	{
		throw "xml文件没有solution标签";
	}

	if(solutionXml)
	{
		m_pSolution = new Solution();
		//m_lstSolution.push_back(soluton);
		m_pSolution->initByXml(solutionXml);
		m_pSolution->loadTableXml();
		//solutionXml = solutionXml->NextSiblingElement("solution");
	}
}

std::vector<Table*>& Task::getTableList()
{
	return m_pSolution->getTablesList();
}

END_NAMESPACE