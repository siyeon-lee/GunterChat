#include "syNetwork.h"
#include "syAsyncSelect.h"
#include "syEventSelect.h"
#include "syStdSelect.h"

std::list<UPACKET>  syNetwork::m_RecvPool;
std::list<UPACKET>  syNetwork::m_SendPool;
bool				syNetwork::m_bConnect = false;

syNetwork::syNetwork()
{
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);
	m_pModel = nullptr;
}


syNetwork::~syNetwork()
{
	WSACleanup();
}


bool syNetwork::CreateSock()
{
	m_Sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Sock == INVALID_SOCKET)
	{
		return false;
	}
	unsigned long iMode = 0;
	ioctlsocket(m_Sock, FIONBIO, &iMode);
	return true;
}
bool syNetwork::SendPacketPool()
{
	if (syNetwork::m_bConnect == false) return true;
	for (UPACKET& packet : syNetwork::m_SendPool)
	{
		if (m_pModel->SendMsg(packet) == false)
		{
			ShutDown();
			break;
		}
	}
	syNetwork::m_SendPool.clear();
	return true;
}
bool syNetwork::SendMsg(int type, char* data, int iSize)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(UPACKET));
	packet.ph.type = type;
	packet.ph.len = PACKET_HEADER_SIZE + iSize;
	if (data != nullptr)
	{
		memcpy(packet.msg, data, iSize);
	}
	m_SendPool.push_back(packet);
	return true;
}
bool	syNetwork::Connect(const char* ip, int port, HWND hWnd)
{
	m_ipAddress = ip;
	m_iPort = port;
	m_hWnd = hWnd;

	if (CreateSock() == false)
	{
		return false;
	}

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);
	sa.sin_addr.s_addr = inet_addr(ip);
	int ret = connect(m_Sock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("connect");
		return false;
	}
	m_bConnect = true;
	return true;
}
LRESULT	syNetwork::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pModel == nullptr) return 1;
	return m_pModel->MsgProc(hWnd, msg, wParam, lParam);
}
bool	syNetwork::ShutDown()
{
	m_bConnect = false;
	closesocket(m_Sock);
	m_RecvPool.clear();
	m_SendPool.clear();
	return true;
}
bool	syNetwork::SetModel(std::shared_ptr<sySelectModel> pModel)
{
	if (pModel == nullptr) return false;

	m_pModel = pModel;
	m_pModel->m_hWnd = m_hWnd;
	m_pModel->Init();
	return true;
}
bool	syNetwork::Init()
{
	return true;
}
bool	syNetwork::Frame()
{
	if (m_pModel == nullptr) return true;
	if (m_bConnect == false)
	{
		// Àç Á¢¼Ó
		if (Connect(m_ipAddress.c_str(), m_iPort, m_hWnd) == false)
		{
			ShutDown();
			return false;
		}
		m_pModel->m_Sock = m_Sock;
		m_pModel->Init();
	}
	if (m_pModel->Frame() == false)
	{
		ShutDown();
		return false;
	}
	return true;
}
bool	syNetwork::Render()
{
	return true;
}
bool	syNetwork::Release()
{
	ShutDown();
	return true;
}