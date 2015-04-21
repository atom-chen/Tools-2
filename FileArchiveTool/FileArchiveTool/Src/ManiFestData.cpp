#include "ManiFestData.h"
#include "FileInfo.h"
#include "PakItemBase.h"
#include "PakItemDir.h"
#include "FileArchiveToolSys.h"
#include "Config.h"
#include "LogSys.h"
#include "TaskQueue.h"
#include "ArchiveData.h"

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
	ss << *m_inPakPath << "=" << *m_inPakPath << "\n";
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
	ss << *m_inPakPath << "=" << *m_pakName << "\n";
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
		FileArchiveToolSysDef->getLogSysPtr()->log("打开清单文件成功\n");

		for (auto item : *(m_pLockList->getVec()))
		{
			ss.clear();
			ss.str("");
			item->serialManiFestInfo(ss);

			writeLen = fwrite(ss.str().c_str(), 1, ss.str().length(), localFile);
			if (writeLen != ss.str().length())
			{
				FileArchiveToolSysDef->getLogSysPtr()->log("输出一项清单失败\n");
			}
		}
	}
	else
	{
		FileArchiveToolSysDef->getLogSysPtr()->log("打开清单文件失败\n");
	}

	clearAll();
	fclose(localFile);
}

void ManiFestData::buildManiFestItem(FileHeader* pFileHeader, PakItemBase* pPakItemBase)
{
	ManiFestItem* pManiFestItem;

	std::string fullPath = pFileHeader->getFullPath();
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

bool ManiFestData::exeTask()
{
	FileArchiveToolSysDef->getLogSysPtr()->log("开始执行清单任务");
	exportManiFest();
	return true;
}

bool ManiFestData::exeResult()
{
	FileArchiveToolSysDef->getLogSysPtr()->log("输出清单文件任务完成");
	FileArchiveToolSysDef->getArchiveDataPtr()->onManiFestEnd();
	return true;
}

void ManiFestData::addSelf2TaskQueue()
{
	FileArchiveToolSysDef->getLogSysPtr()->log("开始添加清单任务");
	FileArchiveToolSysDef->getTaskQueuePtr()->addTask(this);
}

END_NAMESPACE_FILEARCHIVETOOL