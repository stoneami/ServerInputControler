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
	BOOL m_bConnected;    //�Ƿ�����
	UINT m_nLength;        //��Ϣ����
	char m_szBuffer[4096];    //��Ϣ������
	MouseControler mMouseControler;
	KeyboardControler mKeyboardControler;
};
