#include "Config.h"
#include "boost/filesystem.hpp"

BEGIN_NAMESPACE_FILEARCHIVETOOL

Config::Config()
{
	m_pRootPath = new std::string("E:\\");
}

Config::~Config()
{
	delete m_pRootPath;
}

std::string& Config::getRootPath()
{
	return *m_pRootPath;
}

bool Config::bCompress()
{
	return true;
}

void Config::loadConfig()
{
	namespace bf = boost::filesystem;			//�򵥱���
	bf::path old_cpath = bf::current_path();	//ȡ�õ�ǰĿ¼ 
}

END_NAMESPACE_FILEARCHIVETOOL