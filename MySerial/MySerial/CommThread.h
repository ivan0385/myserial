#pragma once
#include "common.h"

#define BUFF_SIZE			(1024*1024)

class CQueue
{
public:
	BYTE buff[BUFF_SIZE];
	int m_iHead, m_iTail;
	CQueue();
	void Clear();
	int GetSize();
	BOOL PutByte(BYTE b);
	BOOL GetByte(BYTE *pb);
};


//////////////////////////////////////////////////////////////////////////
// 以下管理串口相关的一些对象, 如: 波特率列表 ...

// 串口对象
class t_com_item
{
public:
	t_com_item(int i, CString s) { _s = s; _i = i; }

	// 返回字符串部分: 比如: 无校验位
	CString get_s() const { return _s; }
	// 返回整数部分 : 比如: NOPARITY(宏)
	int get_i() const { return _i; }

protected:
	CString _s;
	int _i;
};

// 刷新串口对象列表时需要用到的回调函数类型
typedef void t_list_callback(void* ud, const t_com_item* t);

// 串口对象刷新时的回调类型接口
class i_com_list
{
public:
	virtual void callback(t_list_callback* cb, void* ud) = 0;
};

// 串口对象容器: 比如 保存系统所有的串口列表
template<class T>
class t_com_list : public i_com_list
{
public:
	void empty() { _list.clear(); }
	const T& add(T t) { _list.push_back(t); return _list[_list.size() - 1]; }
	int size() { return _list.size(); }
	const T& operator[](int i) { return _list[i]; }

	// 更新对象列表, 比如更新系统串口列表
	virtual i_com_list* update_list() { return this; }

	virtual operator i_com_list*() { return static_cast<i_com_list*>(this); }
	virtual void callback(t_list_callback* cb, void* ud)
	{
		for (int i = 0, c = _list.size(); i < c; i++)
		{
			cb(ud, &_list[i]);
		}
	}

protected:
	std::vector<T> _list;
};

// 串口端口列表, 继承的原因是: 端口有一个所谓的 "友好名"
// 比如常见的: Prolific USB-to-Serial Comm Port
// 更新到串口列表控件中时需要她们两者一起
class c_comport : public t_com_item
{
public:
	c_comport(int id, CString s)
		: t_com_item(id, s)
	{
	}

	CString get_id_and_name() const;
};

// 串口端口容器: 要向系统取得列表, 所以重写
class c_comport_list : public t_com_list<c_comport>
{
public:
	virtual i_com_list* update_list();
};

class CCommThread
{
public:
	CCommThread(void);
	~CCommThread(void);

public:
	BOOL        check;
	HANDLE		m_hComm;
	CString		m_sPortName;
	BOOL		m_bConnected;
	OVERLAPPED	m_osRead, m_osWrite;
	HANDLE		m_hThreadWatchComm;
	WORD		m_wPortID;
	CQueue      m_QueueRead;
	//---------
	void	init();
	BOOL	OpenPort(CString strPortName,
	DWORD	dwBaud, BYTE byData, BYTE byStop, BYTE byParity );
	void	ClosePort();
	DWORD	WriteComm(BYTE *pBuff, DWORD nToWrite);

	//----------
	DWORD	ReadComm(BYTE *pBuff, DWORD nToRead);

	// Operations
public:
	void Init();
	void SetRectangle();


	// 串口对象列表
public:
	c_comport_list*			comports() { return &_comport_list; }
	t_com_list<t_com_item>*	baudrates() { return &_baudrate_list; }
	t_com_list<t_com_item>*	parities() { return &_parity_list; }
	t_com_list<t_com_item>*	stopbits() { return &_stopbit_list; }
	t_com_list<t_com_item>*	databits() { return &_databit_list; }
private:
	c_comport_list			_comport_list;
	t_com_list<t_com_item>	_baudrate_list;
	t_com_list<t_com_item>	_parity_list;
	t_com_list<t_com_item>	_stopbit_list;
	t_com_list<t_com_item>	_databit_list;

};


DWORD	ThreadWatchComm(CCommThread* pComm);
