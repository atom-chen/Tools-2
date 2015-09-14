#include "CodeExport.h"
#include "XmlConfig.h"

BEGIN_NAMESPACE

CodeExport::CodeExport()
{

}

CodeExport::~CodeExport()
{
	
}

void CodeExport::setXmlPath(std::string file)
{
	m_mutex.lock();
	m_xmlPath = file;
	m_mutex.unlock();
}

void CodeExport::setOutputPath(std::string path)
{
	m_mutex.lock();
	m_tblPath = path;
	m_mutex.unlock();
}

bool CodeExport::exportCppCode()
{
	Package* packItem = new Package();

	packItem->setXml(m_xmlPath);
	packItem->setOutput(m_tblPath);

	packItem->loadTableXml();
	packItem->setAllExportClientTable();
	packItem->exportCppCode();

	delete packItem;

	return true;
}

bool CodeExport::exportCsCode()
{
	Package* packItem = new Package();

	packItem->setXml(m_xmlPath);
	packItem->setOutput(m_tblPath);

	packItem->loadTableXml();
	packItem->setAllExportClientTable();
	packItem->exportCsCode();

	delete packItem;

	return true;
}

END_NAMESPACE