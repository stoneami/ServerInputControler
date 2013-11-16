#pragma once
#include "afxsock.h"

#include "MouseControler.h"
#include "KeyboardControler.h"
#include "Log.h"
#include "Utils.h"

#define MSG_MOUSE_ACTION 0xA0
#define MSG_MOUSE_MOVE 0xA1
#define MSG_MOUSE_ACCURACY 0xA2
#define MSG_PLAIN_TEXT 0xA3
#define MSG_UNKNOW 0

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
	BOOL m_bConnected;
	UINT m_nLength;
	char m_szBuffer[4096];

	MouseControler mMouseControler;
	KeyboardControler mKeyboardControler;

private:
	//There are four types of message:
	//1.MSG_MOUSE_ACTION: mouse action, like "r", "u", "m","s", etc.
	//2.MSG_MOUSE_ACCURACY: set move accuracy, like "#10","#20".
	//3.MSG_PLAIN_TEXT: text, like "##abcdefg","##hello".
	//4.MSG_MOUSE_MOVE: mouse moving, like "###r20u52", "###l2d100"
	int GetMessageType(char* msg, int msgLen);
	BOOL HandlerMessage(char* msg, int msgLen);
};
