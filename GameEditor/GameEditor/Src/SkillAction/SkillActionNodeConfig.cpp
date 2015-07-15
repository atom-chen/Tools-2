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

}

void AttackActionNodeBase::parseXml(tinyxml2::XMLElement* attackActionNodeElem_)
{

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
	// ÆÕÍ¨½Úµã
	AttackActionNodeCommon* pAttackActionNodeCommon;
	pAttackActionNodeElem = config->FirstChildElement("AttackActionNodeCommon");
	while (pAttackActionNodeElem)
	{
		pAttackActionNodeCommon = new AttackActionNodeCommon();
		m_id2ListMap["AttackActionNodeCommon"].push_back(pAttackActionNodeCommon);
		pAttackActionNodeCommon->parseXml(pAttackActionNodeElem);
		pAttackActionNodeElem = pAttackActionNodeElem->NextSiblingElement("AttackActionNodeCommon");
	}

	return true;
}

END_NAMESPACE_GAMEEDITOR