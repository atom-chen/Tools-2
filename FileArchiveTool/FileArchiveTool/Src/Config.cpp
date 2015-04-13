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
	namespace bf = boost::filesystem;			//简单别名
	bf::path old_cpath = bf::current_path();	//取得当前目录 
}

END_NAMESPACE_FILEARCHIVETOOL