#include "syStdSelect.h"
#include "syNetwork.h"


syStdSelect::syStdSelect(SOCKET sock)
{
	m_Sock = sock;
}



syStdSelect::~syStdSelect()
{
}
bool	syStdSelect::Init()
{
	return true;
}
bool	syStdSelect::Frame()
{
	FD_ZERO(&rSet);
	FD_ZERO(&wSet);
	FD_SET(m_Sock, &rSet);
	FD_SET(m_Sock, &wSet);

	timeval time;
	time.tv_sec = 10; // 초
	time.tv_usec = 0;// 마이크로 초

	int iRet = select(0, &rSet, &wSet, NULL, &time);
	if (iRet == SOCKET_ERROR)
	{
		return false;
	}
	if (iRet == 0) return true;// timeout

	if (FD_ISSET(m_Sock, &rSet))
	{
		if (RecvData() == false)
		{
			syNetwork::m_bConnect = false;
		}
	}
	if (FD_ISSET(m_Sock, &wSet))
	{
		//printf(".");
	}
	return true;
}