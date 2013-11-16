#include "StdAfx.h"
#include "ReceiveSocket.h"

CReceiveSocket::CReceiveSocket(void)
{
}

CReceiveSocket::~CReceiveSocket(void)
{
}

void CReceiveSocket::OnSend(int nErrorCode)
{
	CAsyncSocket::OnSend(nErrorCode);
}

void CReceiveSocket::OnOutOfBandData(int nErrorCode)
{
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void CReceiveSocket::OnAccept(int nErrorCode)
{
	CAsyncSocket::OnAccept(nErrorCode);
}

void CReceiveSocket::OnConnect(int nErrorCode)
{
	CAsyncSocket::OnConnect(nErrorCode);
}

void CReceiveSocket::OnClose(int nErrorCode)
{
	CAsyncSocket::OnClose(nErrorCode);
}

int CReceiveSocket::GetMessageType(char* msg, int msgLen)
{
	if(NULL == msg || msgLen < 1) return MSG_UNKNOW;

	if(msg[0] != '#')
	{
		return MSG_MOUSE_ACTION;
	}
	//mouse moving, it's like "###r20u52", "###l2d100"
	else if(msgLen>3 && msg[0]=='#' && msg[1]=='#' && msg[2]=='#')
	{
		return MSG_MOUSE_MOVE;
	}
	// text message like "##aa", "##bb"
	else if(msgLen>2 && msg[0]=='#' && msg[1]=='#')
	{
		return MSG_PLAIN_TEXT;
	}
	//set move accuracy like "#10","#20"
	else if(msgLen>1 && msg[0]=='#')
	{
		return MSG_MOUSE_ACCURACY;
	}
	//mouse action: move or click, like "rr","rrddllrr"
	else
	{
		return MSG_UNKNOW;
	}
}

BOOL CReceiveSocket::HandlerMessage(char* msg, int msgLen)
{
	//char log[200];
	//sprintf(log,"%s: msg=%s, len=%d","HandlerMessage()",msg,msgLen);
	Log::I("ReceiveSocket", msg);

	int msgType = GetMessageType(msg, msgLen);

	switch(msgType)
	{
	case MSG_MOUSE_ACTION:
		mMouseControler.HandleMouseEvent(msg, msgLen);
		return true;
	case MSG_PLAIN_TEXT:
		mKeyboardControler.SendMultiKey(msg+2, msgLen-2);
		return true;
	case MSG_MOUSE_MOVE:
		mMouseControler.HandleMouseEvent(msg, msgLen);
		return true;
	case MSG_MOUSE_ACCURACY:
		MouseControler::SetStep(atoi(msg + 1));
		return true;
	default:
		Log::E("ReceiveSocket", "Unknown Message !");
		return false;
	}
}

//Handle message from client.
void CReceiveSocket::OnReceive(int nErrorCode)
{
	m_nLength = Receive(m_szBuffer,sizeof(m_szBuffer),0);

	m_szBuffer[m_nLength] = '\0';

	HandlerMessage(m_szBuffer, m_nLength);
	
	/*
	if(m_nLength < 1) return;

	if(m_nLength>3 && m_szBuffer[0]=='#' && m_szBuffer[1]=='#' && m_szBuffer[2]=='#')//mouse moving, it's like "###r20u52", "###l2d100"
	{
		mMouseControler.HandleMouseEvent(m_szBuffer, m_nLength);
	}
	else if(m_nLength>2 && m_szBuffer[0]=='#' && m_szBuffer[1]=='#')// text message like "##aa", "##bb"
	{
		mKeyboardControler.SendMultiKey(m_szBuffer+2, m_nLength - 2);
	}
	else if(m_nLength>1 && m_szBuffer[0]=='#')//set move step like "#10","#20"
	{
		MouseControler::SetStep(atoi(m_szBuffer + 1));
	}
	else//mouse action: move or click, like "rr","rrddllrr"
	{
		mMouseControler.HandleMouseEvent(m_szBuffer, m_nLength);
	}
	*/
}