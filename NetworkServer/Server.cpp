#include "syServerStd.h"
#include "Protocol.h"
#include <list>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct syUser 
{
	static SOCKET	findSock;
	bool			isChatting;
	bool			bConnect;
	std::string		name;
	SOCKET			sock;
	SOCKADDR_IN		clientaddr;
	int				m_iRecvByte;
	char			m_szRecvBuffer[PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE];
	bool			RecvData();
	bool operator() (syUser& val) const
	{
		return (findSock == val.sock);
	}
	syUser()
	{
		bConnect = false;
		m_iRecvByte = 0;
	}
};
struct SY_PACKET
{
	UPACKET packet;
	syUser* pUser;
};

std::list <syUser*> g_Userlist;
std::list <SY_PACKET> g_PacketPool;

template<typename T> class syCheck
{
public:
	bool operator() (T val) const
	{
		return (val->sock == m_iSock);
	}
	SOCKET m_iSock;
};

bool syUser::RecvData()
{
	if (m_iRecvByte < PACKET_HEADER_SIZE)
	{
		int iRecvByte = recv(sock, &m_szRecvBuffer[m_iRecvByte], PACKET_HEADER_SIZE - m_iRecvByte, 0);
		if (iRecvByte == 0)
		{
			return false;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() !=
				WSAEWOULDBLOCK)
			{
				E_MSG("Server::recv");
				return false;
			}
		}
		else
		{
			m_iRecvByte += iRecvByte;
		}
	}
	else
	{
		UPACKET* uPacket = (UPACKET*)m_szRecvBuffer;	//패킷 조립하는 부분
		int iRecvByte = recv(sock,
			&m_szRecvBuffer[m_iRecvByte],
			uPacket->ph.len - m_iRecvByte, 0);

		if (iRecvByte == 0)
		{
			return false;
		}
		if (iRecvByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() !=
				WSAEWOULDBLOCK)
			{
				E_MSG("Server::recv");
				return false;
			}
		}
		else
		{
			m_iRecvByte += iRecvByte;
			// 1개의 패킷 완성
			if (uPacket->ph.len == m_iRecvByte)
			{
				SY_PACKET tPacket;
				ZeroMemory(&tPacket, sizeof(tPacket));
				tPacket.pUser = this;
				memcpy(&tPacket.packet,
					m_szRecvBuffer,
					uPacket->ph.len);

				g_PacketPool.push_back(tPacket);	//해석하기 위해 받은 패킷을 패킷풀에 보내
				m_iRecvByte = 0;
			}
		}
	}
	return true;
}
bool SendMsg(syUser* pUser, UPACKET& packet)
{
	int iSendByte = 0;
	do {
		int iPacketByte = send(pUser->sock, (char*)&packet, packet.ph.len - iSendByte, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				E_MSG("SERVER::SEND");
				return false;
			}
		}
		else
		{
			iSendByte += iPacketByte;
		}
	} while (packet.ph.len > iSendByte);
	return true;
}
bool SendMsg(syUser* pUser, int type, char* data, int iSize)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(UPACKET));
	packet.ph.type = type;
	packet.ph.len = PACKET_HEADER_SIZE + iSize;
	if (data != nullptr)
	{
		memcpy(packet.msg, data, iSize);
	}
	int iSendByte = 0;
	do {
		int iPacketByte = send(pUser->sock, (char*)&packet, packet.ph.len - iSendByte, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				E_MSG("SERVER::SEND");
				return false;
			}
		}
		else
		{
			iSendByte += iPacketByte;
		}
	} while (packet.ph.len > iSendByte);
	return true;
}

void AddUser(SOCKET	sock, SOCKADDR_IN clientaddr)
{
	syUser* client = new syUser;
	client->sock = sock;
	client->clientaddr = clientaddr;

	g_Userlist.push_back(client);

	printf("\n접속[%s][%d]=%d",
		inet_ntoa(clientaddr.sin_addr),
		ntohs(clientaddr.sin_port),
		g_Userlist.size());
}
void AddUser(syUser* user)
{
	user->bConnect = true;
	g_Userlist.push_back(user);

	USER_NAME_REQ nameReq;
	ZeroMemory(&nameReq, sizeof(USER_NAME_REQ));
	USER_BASE username;
	username.iIndex = 9;
	memcpy(username.szName, "SERVER", sizeof(char) * 7);
	memcpy(nameReq.msg, "환영합니다.", sizeof(char) * 12);
	memcpy(&nameReq.base, &username, sizeof(USER_BASE));

	UPACKET packet;
	packet.ph.len = sizeof(USER_NAME_REQ) + PACKET_HEADER_SIZE;
	packet.ph.type = PACKET_CHAR_NAME_SC_REQ;
	memcpy(packet.msg, &nameReq, sizeof(USER_NAME_REQ));
	SendMsg(user, packet);

	printf("접속[%s][%d]=%d\n",
		inet_ntoa(user->clientaddr.sin_addr),
		ntohs(user->clientaddr.sin_port),
		g_Userlist.size());
}

void DelUser(SOCKET		sock)
{
	syCheck<syUser*> check;
	check.m_iSock = sock;
	std::list<syUser*>::iterator iter;
	iter = find_if(g_Userlist.begin(),
		g_Userlist.end(),
		check);
	syUser* pUser = (syUser*)*iter;
	/*TUser::findSock = sock;
	iter = find_if( g_Userlist.begin(),
					g_Userlist.end(),
					TUser());*/
	closesocket(pUser->sock);
	printf("\n종료[%s][%d]=%d",
		inet_ntoa(pUser->clientaddr.sin_addr),
		ntohs(pUser->clientaddr.sin_port),
		g_Userlist.size());

	delete *iter;
	g_Userlist.erase(iter);
}
void DelUser(syUser* pUser)
{
	std::list<syUser*>::iterator iter;
	iter = find(g_Userlist.begin(), g_Userlist.end(), pUser);
	closesocket(pUser->sock);
	printf("\n종료[%s][%d]=%d",
		inet_ntoa(pUser->clientaddr.sin_addr),
		ntohs(pUser->clientaddr.sin_port),
		g_Userlist.size());
	delete *iter;
	g_Userlist.erase(iter);
}
void Broadcast(SY_PACKET& tPacket)
{
	USER_CHAT_MSG msg;
	ZeroMemory(&msg, sizeof(USER_CHAT_MSG));
	memcpy(&msg, tPacket.packet.msg, tPacket.packet.ph.len - PACKET_HEADER_SIZE);
	printf("%s : %s\n", msg.szName, msg.msg);
	for (syUser* user : g_Userlist) 
	{
		//if (tPacket.pUser == user || user->isChatting == false) continue;
		if (SendMsg(user, tPacket.packet) == false)
		{
			user->bConnect == false;				//원래는 delete해야하는데 메인함수에서 bConnect==false면 userlist에서 제거 해주니까
		}
	}
}
void   Broadcast(const char* msg, int ibyte)
{
	//printf("\n%s", msg);
	for (syUser* user : g_Userlist)
	{
		int iSendByte = send(user->sock, msg, ibyte, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			closesocket(user->sock);
		}
	}
}
bool RecvMsg(syUser* pUser, char* pBuffer, int iNumDataByte)
{
	if (iNumDataByte == 0) return true;
	int iRecvByte = 0;
	do {
		int iByte = recv(pUser->sock, &pBuffer[iRecvByte], iNumDataByte - iRecvByte, 0);
		if (iByte == 0)
		{
			return false;
		}
		if (iByte == SOCKET_ERROR)
		{
			return false;
		}
		iRecvByte += iByte;
	} while (iNumDataByte > iRecvByte);
	return true;
}
void PacketThread()
{
	for (SY_PACKET& tPacket : g_PacketPool)
	{
		switch (tPacket.packet.ph.type)
		{
		case PACKET_DRUP_CS_REQ:
		{
			USER_BASE info;
			info.iIndex = 9;
			tPacket.pUser->isChatting = false;
			memcpy(info.szName, tPacket.pUser->name.c_str(), tPacket.pUser->name.size());
			for (syUser* user : g_Userlist)
			{
				if (user->isChatting != true) continue;
				SendMsg(user, PACKET_DRUP_USERS_SC, (char*)&info, sizeof(USER_BASE));

			}

			SendMsg(tPacket.pUser, PACKET_DRUP_SC_ACK, nullptr, 0);
		} break;
		case PACKET_RESULT_CS:
		{
			RESULT_SC msg;
			ZeroMemory(&msg, sizeof(RESULT_SC));
			memcpy(&msg, tPacket.packet.msg, tPacket.packet.ph.len - PACKET_HEADER_SIZE);
		
			for (syUser* user : g_Userlist)
			{
				//if (tPacket.pUser == user || user->isChatting == false) continue;
				if (SendMsg(user, PACKET_RESULT_SC, (char*)&msg, sizeof(RESULT_SC)) == false)
				{
					user->bConnect == false;				//원래는 delete해야하는데 메인함수에서 bConnect==false면 userlist에서 제거 해주니까
				}
			}
		}break;
		case PACKET_CHAR_MSG:
		{
			//브로드캐스트
			Broadcast(tPacket);

		}break;

		case PACKET_CHAR_NAME_CS_ACK:
		{
			std::list<syUser*>::iterator iter;
			iter = find(g_Userlist.begin(), g_Userlist.end(), tPacket.pUser);
			syUser* pUser = (*iter);

			USER_NAME_ACK userName;
			memcpy(&userName, tPacket.packet.msg, sizeof(USER_NAME_ACK));
			pUser->name = userName.szName;
			printf("\n%s", userName.szName);
			//클라이언트 등록 허가
			SendMsg(pUser, PACKET_JOIN_SIGNIN_SC, nullptr, 0);
			//다른 클라이언트 유저 접속 통지
			USER_BASE info;
			ZeroMemory(&info, sizeof(USER_BASE));
			info.iIndex = 9;
			memcpy(info.szName, userName.szName, USER_NAME_SIZE);
			for (syUser* user : g_Userlist)
			{
				if (user->isChatting != true) continue;
				SendMsg(user, PACKET_JOIN_USER_SC, (char*)&info, sizeof(USER_BASE));
			}
			pUser->isChatting = true;
		} break;
		
		}
	}
	g_PacketPool.clear();
}

void main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);	//소켓 구조체 만듦
	SOCKET listensock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	int ret = bind(listensock, (SOCKADDR*)&sa, sizeof(sa));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("SERVER::BIND");
		return;
	}
	ret = listen(listensock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		E_MSG("SERVER::LISTEN");
		return;
	}

	unsigned long iMode = 1;	//논블로킹 함수
	ioctlsocket(listensock, FIONBIO, &iMode);

	printf("\n 서버 시작!! \n");

	FD_SET rSet, wSet;

	int addlen = sizeof(SOCKADDR_IN);
	while (1)
	{
		FD_ZERO(&rSet);
		FD_ZERO(&wSet);
		FD_SET(listensock, &rSet);
		for (syUser* pUser : g_Userlist)
		{
			if (pUser->bConnect)
			{
				FD_SET(pUser->sock, &rSet);
				FD_SET(pUser->sock, &wSet);
			}
		}

		timeval time;
		time.tv_sec = 10;
		time.tv_usec = 0;

		int iRet = select(0, &rSet, &wSet, NULL, &time);
		if (iRet == SOCKET_ERROR)
		{
			break;
		}
		if (iRet == 0) continue;	//timeout

		if (FD_ISSET(listensock, &rSet))
		{
			syUser* user = new syUser;
			user->sock = accept(listensock, (SOCKADDR*)&user->clientaddr, &addlen);
			if (user->sock == INVALID_SOCKET)
			{
				E_MSG("SERVER::ACCEPT");
			}
			AddUser(user);
		}
		for (syUser* pUser : g_Userlist)
		{
			if (FD_ISSET(pUser->sock, &rSet))
			{
				if (pUser->RecvData() == false)
				{
					pUser->bConnect == false;
				}
			}
			if (FD_ISSET(pUser->sock, &wSet))
			{
				//
			}
		}
		//유저 삭제
		for (std::list<syUser*>::iterator iter = g_Userlist.begin();
			iter != g_Userlist.end();)
		{
			syUser* pUser = (syUser*)*iter;
			if (pUser->bConnect == false)
			{
				closesocket(pUser->sock);
				printf("\n종료[%s][%d]=%d",
					inet_ntoa(pUser->clientaddr.sin_addr),
					ntohs(pUser->clientaddr.sin_port),
					g_Userlist.size());
				iter = g_Userlist.erase(iter);
			}
			else
			{
				iter++;
			}

		}
	
		PacketThread();
	}

	
	closesocket(listensock);
	WSACleanup();
}