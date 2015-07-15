#ifndef __SkillActionNodeConfig_H_
#define __SkillActionNodeConfig_H_

#include "GameEditor.h"
#include "tinyxml2.h"
#include <string>
#include <vector>
#include <map>

BEGIN_NAMESPACE_GAMEEDITOR

enum GAMEEDITOR_EXPORT eAttackActionNodeType
{
	eAttackActionNodeCommon,
	eTotal
};

class GAMEEDITOR_EXPORT AttackActionNodeBase
{
protected:
#include "PushWarn.h"
	std::string m_id;
#include "PopWarn.h"
	eAttackActionNodeType m_nodeType;

public:
	AttackActionNodeBase();
	virtual ~AttackActionNodeBase();

	virtual void parseXml(tinyxml2::XMLElement* attackActionNodeElem_);
};

class GAMEEDITOR_EXPORT AttackActionNodeListBase
{
protected:
#include "PushWarn.h"
	std::vector<AttackActionNodeBase*> m_nodeList;
#include "PopWarn.h"

public:
	AttackActionNodeListBase();
	virtual ~AttackActionNodeListBase();
};

class GAMEEDITOR_EXPORT AttackActionNodeCommon : public AttackActionNodeBase
{
public:
	AttackActionNodeCommon();
	virtual ~AttackActionNodeCommon();

	virtual void parseXml(tinyxml2::XMLElement* attackActionNodeElem_);
};

class GAMEEDITOR_EXPORT SkillActionNodeConfig
{
protected:
#include "PushWarn.h"
	std::map<std::string, std::vector<AttackActionNodeBase*>> m_id2ListMap;
#include "PopWarn.h"

public:
	SkillActionNodeConfig();
	~SkillActionNodeConfig();

	bool loadXml();			// 加载配置文件
};

END_NAMESPACE_GAMEEDITOR

#endif