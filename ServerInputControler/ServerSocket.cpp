#include "StdAfx.h"
#include "ServerSocket.h"

ServerSocket::ServerSocket(void)
{
}

ServerSocket::~ServerSocket(void)
{
}

void ServerSocket::OnReceive(int nErrorCode)
{
}

void ServerSocket::OnSend(int nErrorCode){}

void ServerSocket::OnOutOfBandData(int nErrorCode){}

void ServerSocket::OnAccept(int nErrorCode)
{
	//侦听到连接请求，调用Accept函数
	CReceiveSocket* pSocket = new CReceiveSocket();
	if(Accept(*pSocket))
	{
		pSocket->AsyncSelect(FD_READ);
		m_pSocket=pSocket;
	}
	else
		delete pSocket;
}

void ServerSocket::OnConnect(int nErrorCode){}

void ServerSocket::OnClose(int nErrorCode){}
