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
// ���¹�������ص�һЩ����, ��: �������б� ...

// ���ڶ���
class t_com_item
{
public:
	t_com_item(int i, CString s) { _s = s; _i = i; }

	// �����ַ�������: ����: ��У��λ
	CString get_s() const { return _s; }
	// ������������ : ����: NOPARITY(��)
	int get_i() const { return _i; }

protected:
	CString _s;
	int _i;
};

// ˢ�´��ڶ����б�ʱ��Ҫ�õ��Ļص���������
typedef void t_list_callback(void* ud, const t_com_item* t);

// ���ڶ���ˢ��ʱ�Ļص����ͽӿ�
class i_com_list
{
public:
	virtual void callback(t_list_callback* cb, void* ud) = 0;
};

// ���ڶ�������: ���� ����ϵͳ���еĴ����б�
template<class T>
class t_com_list : public i_com_list
{
public:
	void empty() { _list.clear(); }
	const T& add(T t) { _list.push_back(t); return _list[_list.size() - 1]; }
	int size() { return _list.size(); }
	const T& operator[](int i) { return _list[i]; }

	// ���¶����б�, �������ϵͳ�����б�
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

// ���ڶ˿��б�, �̳е�ԭ����: �˿���һ����ν�� "�Ѻ���"
// ���糣����: Prolific USB-to-Serial Comm Port
// ���µ������б�ؼ���ʱ��Ҫ��������һ��
class c_comport : public t_com_item
{
public:
	c_comport(int id, CString s)
		: t_com_item(id, s)
	{
	}

	CString get_id_and_name() const;
};

// ���ڶ˿�����: Ҫ��ϵͳȡ���б�, ������д
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


	// ���ڶ����б�
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
