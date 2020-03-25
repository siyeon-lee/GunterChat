#pragma once
#include "sySelectModel.h"
class syNetwork
{
public:
	syNetwork();
	virtual ~syNetwork();
public:
	std::shared_ptr<sySelectModel> m_pModel;
	C_STR               m_ipAddress;
	int					m_iPort;
	HWND				m_hWnd;
	SOCKET				m_Sock;
	static std::list<UPACKET>  m_RecvPool;
	static std::list<UPACKET>  m_SendPool;
	static bool			m_bConnect;
public:
	bool CreateSock();
	bool SendPacketPool();
	bool SendMsg(int type, char* data, int iSize);
	bool	Connect(const char* ip, int port, HWND hWnd);
	LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool	ShutDown();
	bool	SetModel(std::shared_ptr<sySelectModel> pModel);
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
	
};

