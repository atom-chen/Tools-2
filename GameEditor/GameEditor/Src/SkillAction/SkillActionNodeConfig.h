#ifndef __SkillActionNodeConfig_H_
#define __SkillActionNodeConfig_H_

#include "GameEditor.h"
#include <string>

BEGIN_NAMESPACE_GAMEEDITOR

class GAMEEDITOR_EXPORT AttackActionNodeBase
{
protected:
#include "PushWarn.h"
	std::string m_id;		// Ψһ Id
#include "PopWarn.h"
	
};

class GAMEEDITOR_EXPORT SkillActionNodeConfig
{
public:
	SkillActionNodeConfig();
	~SkillActionNodeConfig();
};

END_NAMESPACE_GAMEEDITOR

#endif