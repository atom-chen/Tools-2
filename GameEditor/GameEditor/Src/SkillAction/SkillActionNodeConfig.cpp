#include "SkillActionNodeConfig.h"

BEGIN_NAMESPACE_GAMEEDITOR

AttackActionNodeBase::AttackActionNodeBase()
{

}

AttackActionNodeBase::~AttackActionNodeBase()
{

}

AttackActionNodeListBase::AttackActionNodeListBase()
{
	
}

AttackActionNodeListBase::~AttackActionNodeListBase()
{
	for (auto item : m_nodeList)
	{
		delete item;
	}

	m_nodeList.clear();
}

void AttackActionNodeListBase::addNode(AttackActionNodeBase* node_)
{

}

void AttackActionNodeBase::parseXml(tinyxml2::XMLElement* attackActionNodeElem_)
{
	m_id = attackActionNodeElem_->Attribute("Id");
}

AttackActionNodeCommon::AttackActionNodeCommon()
{
	m_nodeType = eAttackActionNodeCommon;
}

AttackActionNodeCommon::~AttackActionNodeCommon()
{

}

void AttackActionNodeCommon::parseXml(tinyxml2::XMLElement* attackActionNodeElem_)
{
	AttackActionNodeBase::parseXml(attackActionNodeElem_);

	//attackActionNodeElem_->Attribute("size");
}

SkillActionNodeConfig::SkillActionNodeConfig()
{

}

SkillActionNodeConfig::~SkillActionNodeConfig()
{
	m_id2ListVec.clear();
}

bool SkillActionNodeConfig::loadXml()
{
	std::string path = "Config/SkillAction/SkillActionNode.xml";
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* config = NULL;
	tinyxml2::XMLElement* pAttackActionNodeElem = NULL;

	if (doc.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS)
	{
		return false;
	}

	config = doc.FirstChildElement("Config");
	AttackActionNodeListBase vec;
	// ÆÕÍ¨½Úµã
	AttackActionNodeCommon* pAttackActionNodeCommon;
	pAttackActionNodeElem = config->FirstChildElement("AttackActionNodeCommon");
	m_id2ListVec.push_back(AttackActionNodeListBase());
	vec = m_id2ListVec.back();
	while (pAttackActionNodeElem)
	{
		pAttackActionNodeCommon = new AttackActionNodeCommon();
		vec.addNode(pAttackActionNodeCommon);
		pAttackActionNodeCommon->parseXml(pAttackActionNodeElem);
		pAttackActionNodeElem = pAttackActionNodeElem->NextSiblingElement("AttackActionNodeCommon");
	}

	return true;
}

END_NAMESPACE_GAMEEDITOR