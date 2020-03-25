#pragma once
#include "syServerStd.h"
#include "Protocol.h"
class sySelectModel
{
public:
	sySelectModel();
	virtual ~sySelectModel();
public:
	HWND    m_hWnd;
	SOCKET	m_Sock;
	int		m_iRecvByte;
	char	m_szRecvBuffer[PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE];
public:
	virtual bool	Init() { return true; };
	virtual bool	Frame() { return true; };
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return 1;
	}
	bool RecvData();
	bool RecvMsg(SOCKET sock, char* pBuffer, int iNumDataByte);
	bool SendMsg(SOCKET sock, int type, char* data, int iSize);
	bool SendMsg(UPACKET& packet);
};

