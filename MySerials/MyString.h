#pragma once

#include<string>
#include<vector>
class CMyString
{
public:
	CMyString(void);
	~CMyString(void);
	static CString CMyString::GetAsciiFromString(CString rcv_total, CString str);
	static int String2Hex(CString inputStr, BYTE * output);
	static int ConvertHexChar(char ch);
	static CString GetNowTime(void);
	static CString GetNowDate(void);
	static CString GetNowDateTime(void);
	static void split(std::string & src, std::string & separator, std::vector<std::string> & dest);
};

