#ifndef __ManiFestData_H
#define __ManiFestData_H

#include "Prerequisites.h"
#include "LockList.h"
#include "ITask.h"

#include <sstream>

BEGIN_NAMESPACE_FILEARCHIVETOOL

/**
 *@brief �嵥��
 */
class FILEARCHIVETOOL_EXPORT ManiFestItem
{
protected:
	std::string* m_inPakPath;			// ������Դ�����֣������ʱ����Ҫд��ͷ������Ϣ

public:
	ManiFestItem();
	virtual ~ManiFestItem();

	std::string& getInPakPath();
	void setInPakPath(std::string& name_);

	virtual void setPakName(std::string& name_);
	virtual void serialManiFestInfo(std::stringstream& ss);				// ���л��嵥����Ϣ
};

/**
 *@brief �ļ��嵥��
 */
class FILEARCHIVETOOL_EXPORT ManiFestFileItem : public ManiFestItem
{
public:
	ManiFestFileItem();
	virtual ~ManiFestFileItem();

	virtual void serialManiFestInfo(std::stringstream& ss);				// ���л��嵥����Ϣ
};

/**
*@brief Ŀ¼�嵥��
*/
class FILEARCHIVETOOL_EXPORT ManiFestDirItem : public ManiFestItem
{
protected:
	std::string* m_pakName;				// ���ڰ�������

public:
	ManiFestDirItem();
	virtual ~ManiFestDirItem();

	std::string& getPakName();
	virtual void setPakName(std::string& name_);

	virtual void serialManiFestInfo(std::stringstream& ss);				// ���л��嵥����Ϣ
};


/**************************************************/
//template<class T>
//class LockQueue<MainFestItem*>;

class FileHeader;
class PakItemBase;

/**
 *@brief �嵥����
 */
class FILEARCHIVETOOL_EXPORT ManiFestData
{
protected:
	LockList<ManiFestItem*>* m_pLockList;

public:
	ManiFestData();
	virtual ~ManiFestData();
	LockList<ManiFestItem*>* getLockList();
	void clearAll();
	void addItem(ManiFestItem* item);
	void exportManiFest();				// �����嵥
	void buildManiFestItem(FileHeader* pFileHeader, PakItemBase* pPakItemBase);

	void addSelf2TaskQueue();
};

/*********************************************/

class FILEARCHIVETOOL_EXPORT ManiFestDataTask : public ITask
{
protected:
	ManiFestData* m_pManiFestData;

public:
	ManiFestDataTask(ManiFestData* pManiFestData);
	~ManiFestDataTask();
	virtual bool exeTask();
	virtual bool exeResult();
};

END_NAMESPACE_FILEARCHIVETOOL

#endif