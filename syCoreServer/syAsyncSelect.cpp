#include "syAsyncSelect.h"
#include "syNetwork.h"
#define WM_ASYNC_SOCKET   (WM_USER+1)
const char username[] = "ȫ�浿";

syAsyncSelect::syAsyncSelect(SOCKET sock)
{
	m_Sock = sock;
}


syAsyncSelect::~syAsyncSelect()
{
}
LRESULT		syAsyncSelect::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int iEvent = WSAGETSELECTEVENT(lParam);
	int iSock = WSAGETSELECTEVENT(wParam);
	if (WSAGETSELECTERROR(lParam))
	{
		return 1;
	}
	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_CONNECT:
	{
	}break;
	case FD_READ:
	{
		char recvbuf[256] = { 0, };
		UPACKET packet;
		ZeroMemory(&packet, sizeof(packet));

		int iRecvByte = recv(m_Sock, (char*)&packet.ph, PACKET_HEADER_SIZE, 0);
		if (iRecvByte == 0)
		{
			break;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			printf("\n���� �����");
			break;
		}
		if (iRecvByte == PACKET_HEADER_SIZE)
		{
			int iNumDataByte = packet.ph.len - PACKET_HEADER_SIZE;
			if (false == RecvMsg(m_Sock, packet.msg, iNumDataByte))
			{
				break;
			}
			iRecvByte = 0;

			syNetwork::m_RecvPool.push_back(packet);
		}
	};
	case FD_WRITE:
	{

	}break;
	case FD_CLOSE:
	{
		PostMessage(m_hWnd, WM_ASYNC_SOCKET,
			wParam, FD_READ);
	}break;
	}
}
bool		syAsyncSelect::Init()
{
	//-------------------ASYNC-SELECT---------------------------
	int iRet = WSAAsyncSelect(m_Sock, m_hWnd,
		WM_ASYNC_SOCKET,
		FD_CONNECT |
		FD_CLOSE |
		FD_READ |
		FD_WRITE);
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}