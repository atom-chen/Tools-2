#ifndef _TASK_H
#define _TASK_H

#include <string>		// include string
#include <vector>		// include vector
#include "tinyxml2.h"	// include xml
#include "EnValue.h"
#include "TabelAttr.h"
#include "Platform.h"
#include "XmlConfig.h"

BEGIN_NAMESPACE

/**
 * @brief task
 */
class Task
{
protected:
	Solution* m_pSolution;

public:
	Task();
	~Task();

	Solution* getSolution();
	void readXML();		// read Config.xml
	void destroy();

	std::vector<Table*>& getTableList();
};

END_NAMESPACE

#endif