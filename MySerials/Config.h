#pragma once
#include <map>

#define FILE_NAME L"common.ini"
class CCommonConfig
{
public:
	CCommonConfig();
	~CCommonConfig();
private:
	std::map<CString, CString> m_cfg_map;
public:
	bool addKey(CString key, CString value);
	CString getKey(CString key);
	bool saveConfig();
	bool loadConfig();
};

