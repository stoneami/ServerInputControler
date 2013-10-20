#include "StdAfx.h"
#include "ReceiveSocket.h"

CReceiveSocket::CReceiveSocket(void)
{
}

CReceiveSocket::~CReceiveSocket(void)
{
}

void CReceiveSocket::OnSend(int nErrorCode){}

void CReceiveSocket::OnOutOfBandData(int nErrorCode){}

void CReceiveSocket::OnAccept(int nErrorCode){}

void CReceiveSocket::OnConnect(int nErrorCode){}

void CReceiveSocket::OnClose(int nErrorCode){}


//Handle message from client.
//There there types of message:
//1.mouse action, it's like "r", "u" etc.
//2.set move step, it's like "#10","#20".
//3.text, it's like "##abcdefg","##hello".
void CReceiveSocket::OnReceive(int nErrorCode)
{
	m_nLength = Receive(m_szBuffer,sizeof(m_szBuffer),0);
	if(m_nLength < 1) return;

	if(m_szBuffer[0] != '#')//mouse action: move or click, like "rr","rrddllrr"
	{
		mMouseControler.HandleMouseEvent(m_szBuffer, m_nLength);
	}
	else
	{
		if(m_szBuffer[1] != '#')//set move step like "#10","#20"
		{
			MouseControler::SetStep(atoi(m_szBuffer + 1));
		}
		else// text message like "##aa", "##bb"
		{
			mKeyboardControler.SendMultiKey(m_szBuffer+2, m_nLength - 2);
		}
	}	
	//AfxMessageBox(Utils::getWChar(m_nLength));
	//AfxMessageBox(Utils::getWChar(atoi(m_szBuffer + 1)));//step
}