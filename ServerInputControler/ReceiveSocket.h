#pragma once
#include "afxsock.h"

#include "MouseControler.h"
#include "KeyboardControler.h"

class CReceiveSocket :
	public CAsyncSocket
{
public:
	CReceiveSocket(void);
	~CReceiveSocket(void);

protected:
	void OnReceive(int nErrorCode);
	void OnSend(int nErrorCode);
	void OnOutOfBandData(int nErrorCode);
	void OnAccept(int nErrorCode);
	void OnConnect(int nErrorCode);
	void OnClose(int nErrorCode);

public:
	BOOL m_bConnected;    //是否连接
	UINT m_nLength;        //消息长度
	char m_szBuffer[4096];    //消息缓冲区
	MouseControler mMouseControler;
	KeyboardControler mKeyboardControler;
};
