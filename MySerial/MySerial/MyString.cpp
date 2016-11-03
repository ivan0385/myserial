#include "stdafx.h"
#include "MyString.h"


CMyString::CMyString(void)
{
}


CMyString::~CMyString(void)
{
}


CString CMyString::GetAsciiFromString(CString rcv_total, CString str)
{
	CString mm;
	CString nn=L"";

	int iFirst = rcv_total.Find(str);
	BYTE *nu = new BYTE[256];
	String2Hex(str.Mid(3,2),nu);
	int length = nu[0]>>3;
	if (iFirst>=0)
	{
		mm = rcv_total.Right(rcv_total.GetLength()-(iFirst+str.GetLength()));
	}

	mm.Replace(L" ",L"");
	mm.Replace(L"\r\n",L"");
	String2Hex(mm,nu);

	CString tt;
	for (int i=0;i<length-1;i++)
	{
		tt.Format(L"%c",nu[i]);
		nn+=tt;
	}

	delete [] nu;

	return nn;
}


int CMyString::String2Hex(CString inputStr, BYTE * output)
{
	int bufPos = 0;
	int datasize,bufsize, i;
	BYTE byHigh, byLow;

	inputStr.Replace(L" ",L"");
	inputStr.Replace(L"\r\n",L"");

	datasize = inputStr.GetLength();

	if(datasize %2 == 0)
	{
		bufsize = datasize;
	}
	else
	{
		bufsize = datasize -1; 
	}

	for( i = 0; i < bufsize ; i+=2)
	{
		byHigh = ConvertHexChar((char)inputStr[i]);
		byLow  = ConvertHexChar((char)inputStr[i+1]);
		output[bufPos++] = (byHigh <<4) | byLow;
	}
	return bufPos;
}


int CMyString::ConvertHexChar(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else 
		return (-1);
}


CString CMyString::GetNowTime(void)
{
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	strTime.Format(L"%02d:%02d:%02d.%03d",st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	return strTime;
}


CString CMyString::GetNowDate(void)
{
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	strDate.Format(L"%4d-%2d-%2d",st.wYear,st.wMonth,st.wDay);
	return strDate;
}


CString CMyString::GetNowDateTime(void)
{
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	strTime.Format(L"%2d-%2d %02d:%02d:%02d",st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	return strTime;
}


void CMyString::split(std::string & src, std::string & separator, std::vector<std::string> & dest)
{
	std::string str = src;
	std::string substring;
	std::string::size_type start = 0, index;

	do
	{
		index = str.find_first_of(separator, start);
		if (index != std::string::npos)
		{
			substring = str.substr(start, index - start);
			dest.push_back(substring);
			start = str.find_first_not_of(separator, index);
			if (start == std::string::npos) return;
		}
	} while (index != std::string::npos);

	//the last token
	substring = str.substr(start);
	dest.push_back(substring);
}
