#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Clientsample.h"
#include "syStdSelect.h"
#include "syEventSelect.h"
#include "syAsyncSelect.h"

syNetwork		m_Network;
HWND			m_hEdit;
HWND			m_hButton;
HWND			m_hList;
HWND			m_hScoreList;
WNDPROC			old_edit_proc;
//edit box서 엔터 치면 메세지 전송
LRESULT CALLBACK myEditProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CHAR:
		{
			switch (wParam)
			{
				case VK_RETURN:
				{
					char buffer[2048] = { 0, };
					USER_CHAT_MSG message;
					ZeroMemory(&message, sizeof(USER_CHAT_MSG));
					SendMessageA(m_hEdit,
						WM_GETTEXT,
						MAX_PATH,
						(LPARAM)buffer);
					memcpy(&message.szName, GetWtM(g_username), sizeof(TCHAR)*wcslen(g_username));
					//memcpy(&message.szName, g_username, wcslen(g_username));
					memcpy(&message.msg, buffer,  strlen(buffer));
					if (strlen(message.msg) > 0)
					{
						m_Network.SendMsg(PACKET_CHAR_MSG, (char*)&message, USER_NAME_SIZE + strlen(buffer));
					}
					SetWindowText(m_hEdit, L"");
					break;
				}break;
			}
		
		}break;
	}
	return CallWindowProc(old_edit_proc, hWnd, msg, wParam, lParam);
}
Clientsample::Clientsample()
{
}
Clientsample::~Clientsample()
{
}


bool Clientsample::Init()
{
	// window api control
	DWORD style = WS_CHILD | WS_VISIBLE /*| ES_MULTILINE*/;
	m_hEdit = CreateWindow(L"edit", NULL, style,
		10, 490, 510, 100, g_hWnd, (HMENU)100,
		NULL, NULL);
	old_edit_proc = (WNDPROC)SetWindowLongPtr(m_hEdit, GWLP_WNDPROC, (LONG_PTR)myEditProc);

	style = WS_CHILD | WS_VISIBLE | BS_NOTIFY;
	m_hButton = CreateWindow(L"button", L"Send", style,
		530, 490, 100, 100, g_hWnd, (HMENU)200,
		g_hInstance, NULL);

	style = WS_CHILD | WS_VISIBLE /*| WS_VSCROLL | WS_HSCROLL | ES_MULTILINE*/;
	m_hList = CreateWindow(L"listbox", NULL, style,
		650, 120, 330, 470, g_hWnd, (HMENU)300,
		g_hInstance, NULL);
	style = WS_CHILD | WS_VISIBLE;
	m_hScoreList = CreateWindow(L"listbox", NULL, style,
		650, 10, 330, 100, g_hWnd, (HMENU)400,
		g_hInstance, NULL);
	if (!m_hScoreList)
	{
		E_MSG("here");
	}
	SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)L"채팅시작합니다.");
	SendMessage(m_hScoreList, LB_ADDSTRING, 0, (LPARAM)L"점수 순위");
	// 1)초기화
	if (!m_Network.Init())
	{
		return false;
	}
	// 2)접속
	if (!m_Network.Connect("192.168.0.51", 10000, g_hWnd))
	{
		return false;
	}
	// 3)모델 선택
	m_Network.SetModel(make_shared<syEventSelect>(m_Network.m_Sock));
	return true;
}
bool		Clientsample::PreFrame()
{
	m_Network.Frame();
	PacketProcess();
	return true;
}
bool		Clientsample::Frame()
{
	//Sleep(1000);	
	//m_Network.SendMsg(PACKET_CHAR_MSG, g_username, sizeof(g_username));
	return true;
}
bool		Clientsample::PostRender()
{
	m_Network.SendPacketPool();
	return true;
}
bool		Clientsample::Release()
{
	m_Network.Release();
	return true;
}
bool		Clientsample::PacketProcess()
{
	for (UPACKET& packet : syNetwork::m_RecvPool)
	{
		switch (packet.ph.type)
		{
		case PACKET_DRUP_USERS_SC:
		{
			USER_BASE userinfo;
			ZeroMemory(&userinfo, sizeof(USER_BASE));
			memcpy(&userinfo, packet.msg, packet.ph.len - PACKET_HEADER_SIZE);
			printf("%s:님이 퇴장하였습니다.", userinfo.szName);
		}break;
		case PACKET_DRUP_SC_ACK:
		{
			printf("\n채팅방 퇴장.");
		}break;
		case PACKET_JOIN_SIGNIN_SC:
		{
			printf("\n채팅방 입장.\n");
		}break;
		case  PACKET_CHAR_MSG:
		{
			USER_CHAT_MSG message;
			ZeroMemory(&message, sizeof(USER_CHAT_MSG));
			memcpy(&message, packet.msg, packet.ph.len - PACKET_HEADER_SIZE);
			//printf("\n[%s]%s", message.szName, message.msg);
			C_STR msg = "[";
			msg += message.szName;
			msg += "]";
			msg += message.msg;
			OutputDebugStringA(msg.c_str());

 			int iCnt = SendMessage(m_hList, LB_GETCOUNT, 0, 0);
			DWORD e = GetLastError();
			if (iCnt > 20)
			{
				SendMessage(m_hList, LB_RESETCONTENT, 0, 0);
			}
			SendMessageA(m_hList, LB_ADDSTRING, 0, (LPARAM)msg.c_str());

		}break;
		case PACKET_RESULT_SC :
		{
			RESULT_SC message;
			ZeroMemory(&message, sizeof(RESULT_SC));
			memcpy(&message, packet.msg, packet.ph.len - PACKET_HEADER_SIZE);
			//printf("\n[%s]%s", message.szName, message.msg);
			C_STR msg = "[";
			msg += message.szName;
			msg += "]";
			msg += message.msg;
			OutputDebugStringA(msg.c_str());

			SendMessageA(m_hScoreList, LB_ADDSTRING, 0, (LPARAM)msg.c_str());
		}break;
		case  PACKET_CHAR_NAME_SC_REQ:
		{
			USER_BASE data;
			ZeroMemory(&data, sizeof(USER_BASE));
			data.iIndex = 8;
			memcpy(&data.szName, GetWtM(g_username), sizeof(TCHAR)*wcslen(g_username));
			m_Network.m_pModel->SendMsg(m_Network.m_Sock, PACKET_CHAR_NAME_CS_ACK, (char*)&data, sizeof(USER_BASE));
		}break;
		}
	}
	syNetwork::m_RecvPool.clear();
	return true;
}

LRESULT Clientsample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case 200:		
				{
					switch (HIWORD(wParam))
					{
					case BN_CLICKED:
						char buffer[2048] = { 0, };
						RESULT_CS message;
						ZeroMemory(&message, sizeof(RESULT_CS));
						SendMessageA(m_hEdit,
							WM_GETTEXT,
							MAX_PATH,
							(LPARAM)buffer);
						memcpy(&message.szName, GetWtM(g_username), sizeof(TCHAR)*wcslen(g_username));
						memcpy(&message.msg, buffer, strlen(buffer));
						if (strlen(message.msg) > 0)
						{
							m_Network.SendMsg(PACKET_CHAR_MSG, (char*)&message, USER_NAME_SIZE + strlen(buffer));
						}
						SetWindowText(m_hEdit, L"");
						break;
					}
				}
			}
		}
	}
	return m_Network.MsgProc(hWnd, msg, wParam, lParam);
}

bool Clientsample::PostResult()
{
	USER_CHAT_MSG message;
	ZeroMemory(&message, sizeof(USER_CHAT_MSG));
	memcpy(&message.szName, GetWtM(g_username), sizeof(TCHAR)*wcslen(g_username));
	char buffer[2048] = { 0, };
	sprintf(buffer, "[%d]점을 획득하였습니다", g_score);
	memcpy(&message.msg, buffer, strlen(buffer));
	m_Network.SendMsg(PACKET_CHAR_MSG, (char*)&message, USER_NAME_SIZE + strlen(buffer));

	if (g_score == 0) return true;
	RESULT_CS resultmes;
	ZeroMemory(&resultmes, sizeof(RESULT_CS));
	memcpy(&resultmes.szName, GetWtM(g_username), sizeof(TCHAR)*wcslen(g_username));
	sprintf(buffer, "%d", g_score);
	memcpy(&resultmes.msg, buffer, strlen(buffer));
	m_Network.SendMsg(PACKET_RESULT_CS, (char*)&resultmes, USER_NAME_SIZE + strlen(buffer));
	return true;
}