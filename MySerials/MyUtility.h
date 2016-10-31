#pragma once
#include <vector>
class CMyUtility
{
public:
	CMyUtility(void);
	~CMyUtility(void);
	static CString GetModuleFolder(HMODULE hModule=NULL);
	static CString GetModuleName(HMODULE hModule=NULL);
	static CString CMyUtility::GetExcutableFullPath(HMODULE hModule=NULL);
	static CString GetFileFolder(LPCTSTR strFilename);
	static INT64 GetFileSize(LPCTSTR strFilename);
	static CString GetFileExtName(LPCTSTR strFilename);
	static CString QueryTempFilePath(void);
	static BOOL FileRead(LPCTSTR strFilename, std::vector<BYTE>& file_data);
	static BOOL FileWrite(LPCTSTR strFilename, const void* p, int nLength);
};

