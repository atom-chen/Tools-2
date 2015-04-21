#include "ManiFestData.h"
#include "FileInfo.h"
#include "PakItemBase.h"
#include "PakItemDir.h"
#include "FileArchiveToolSys.h"
#include "Config.h"
#include "LogSys.h"
#include "TaskQueue.h"
#include "ArchiveData.h"
#include  "CharsetConv.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

ManiFestItem::ManiFestItem()
{
	m_inPakPath = new std::string;
}

ManiFestItem::~ManiFestItem()
{
	delete m_inPakPath;
}

std::string& ManiFestItem::getInPakPath()
{
	return *m_inPakPath;
}

void ManiFestItem::setInPakPath(std::string& name_)
{
	*m_inPakPath = name_;
}

void ManiFestItem::setPakName(std::string& name_)
{

}

void ManiFestItem::serialManiFestInfo(std::stringstream& ss)
{

}


/*********************************************************/

ManiFestFileItem::ManiFestFileItem()
{

}

ManiFestFileItem::~ManiFestFileItem()
{

}

void ManiFestFileItem::serialManiFestInfo(std::stringstream& ss)
{
	char* pUtf8Path = FileArchiveToolSysDef->getCharsetConvPtr()->LocalToUtf8Str((char*)(m_inPakPath->c_str()));
	ss << pUtf8Path << "=" << pUtf8Path;
}

/*********************************************************/

ManiFestDirItem::ManiFestDirItem()
{
	m_pakName = new std::string;
}

ManiFestDirItem::~ManiFestDirItem()
{
	delete m_pakName;
}

std::string& ManiFestDirItem::getPakName()
{
	return *m_pakName;
}

void ManiFestDirItem::setPakName(std::string& name_)
{
	*m_pakName = name_;
}

void ManiFestDirItem::serialManiFestInfo(std::stringstream& ss)
{
	char* pUtf8Path = FileArchiveToolSysDef->getCharsetConvPtr()->LocalToUtf8Str((char*)(m_inPakPath->c_str()));
	ss << pUtf8Path << "=";
	pUtf8Path = FileArchiveToolSysDef->getCharsetConvPtr()->LocalToUtf8Str((char*)(m_pakName->c_str()));
	ss << pUtf8Path;
}

/*********************************************************/

ManiFestData::ManiFestData()
{
	m_pLockList = new LockList<ManiFestItem*>;
}

ManiFestData::~ManiFestData()
{
	delete m_pLockList;
}

LockList<ManiFestItem*>* ManiFestData::getLockList()
{
	return m_pLockList;
}

void ManiFestData::clearAll()
{
	m_pLockList->clear();
}

void ManiFestData::addItem(ManiFestItem* item)
{
	m_pLockList->push_back(item);
}

void ManiFestData::exportManiFest()
{
	std::stringstream ss;
	size_t writeLen;
	FILE* localFile = fopen(FileArchiveToolSysDef->getConfigPtr()->getManiFestFullPath().c_str(), "wb");
	if (localFile != nullptr)
	{
		FileArchiveToolSysDef->getLogSysPtr()->log("���嵥�ļ��ɹ�\n");
		size_t curIdx = 0;
		for (auto item : *(m_pLockList->getVec()))
		{
			ss.clear();
			ss.str("");
			item->serialManiFestInfo(ss);
			if (curIdx != m_pLockList->size() - 1)		// �������һ��������Ҫ��ӻ���
			{
				ss << "\n";
			}

			writeLen = fwrite(ss.str().c_str(), 1, ss.str().length(), localFile);
			if (writeLen != ss.str().length())
			{
				FileArchiveToolSysDef->getLogSysPtr()->log("���һ���嵥ʧ��\n");
			}

			++curIdx;
		}
	}
	else
	{
		FileArchiveToolSysDef->getLogSysPtr()->log("���嵥�ļ�ʧ��\n");
	}

	clearAll();
	fclose(localFile);
}

void ManiFestData::buildManiFestItem(FileHeader* pFileHeader, PakItemBase* pPakItemBase)
{
	ManiFestItem* pManiFestItem;

	std::string fullPath = pFileHeader->getPakFileName();
	if (pPakItemBase->getPakItemType() == ePI_FILE)
	{
		pManiFestItem = new ManiFestFileItem;
		pManiFestItem->setInPakPath(fullPath);
	}
	else if (pPakItemBase->getPakItemType() == ePI_DIR)
	{
		pManiFestItem = new ManiFestDirItem;
		PakItemDir* pPakItemDir = static_cast<PakItemDir*>(pPakItemBase);
		pManiFestItem->setPakName(pPakItemDir->getPakFullName());
		pManiFestItem->setInPakPath(fullPath);
	}

	addItem(pManiFestItem);
}

void ManiFestData::addSelf2TaskQueue()
{
	FileArchiveToolSysDef->getLogSysPtr()->log("��ʼ����嵥����");
	ManiFestDataTask* pManiFestDataTask = new ManiFestDataTask(this);
	FileArchiveToolSysDef->getTaskQueuePtr()->addTask(pManiFestDataTask);
}

/*********************************************/

ManiFestDataTask::ManiFestDataTask(ManiFestData* pManiFestData)
{
	m_pManiFestData = pManiFestData;
}

ManiFestDataTask::~ManiFestDataTask()
{

}

bool ManiFestDataTask::exeTask()
{
	FileArchiveToolSysDef->getLogSysPtr()->log("��ʼִ���嵥����");
	m_pManiFestData->exportManiFest();
	return true;
}

bool ManiFestDataTask::exeResult()
{
	FileArchiveToolSysDef->getLogSysPtr()->log("����嵥�ļ��������");
	FileArchiveToolSysDef->getArchiveDataPtr()->onManiFestEnd();
	return true;
}

END_NAMESPACE_FILEARCHIVETOOL