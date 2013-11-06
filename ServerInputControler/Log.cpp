#include "StdAfx.h"
#include "Log.h"
#include "Utils.h"
#include <sys/timeb.h>

Log::Log(void)
{
}

Log::~Log(void)
{
}

void Log::PrintLog(char type,wchar_t* tag, wchar_t* buf, int bufLen)
{
	wchar_t tmp[MAX_CHAR-10]={0};
	if(bufLen > MAX_CHAR-10 -1) bufLen = MAX_CHAR-10 -1;
	for(int i=0,j=0; j<bufLen&&i<MAX_CHAR-10-1; i++,j++)
		tmp[i] = buf[j];

	//get date and time
	CTime tm = CTime::GetCurrentTime();
	CString str = tm.Format("%Y-%m-%d %X");

	//get millisecond 
	CString second;
	struct _timeb timebuffer;    
	_ftime(&timebuffer);
	second.Format(L"%d",timebuffer.millitm);
	int minSecond=_tstoi(second);

	wchar_t msg[MAX_CHAR]={0};
	swprintf_s(msg,L"%s.%d %c/%s: %s%c",str,minSecond,type,tag,tmp,'\n');
	OutputDebugString(msg);
}

void Log::W(wchar_t* tag, wchar_t* msg, int msgLen)
{
	PrintLog('W',tag,msg,msgLen);
}

void Log::E(wchar_t* tag,wchar_t* msg,int msgLen)
{
	PrintLog('E', tag, msg,msgLen);
}

void Log::I(wchar_t* tag, wchar_t* msg, int msgLen)
{
	PrintLog('I', tag, msg, msgLen);
}

//msg must be ended by '\0'
void Log::W(wchar_t* tag, wchar_t* msg)
{
	int len = wcslen(msg);
	W(tag, msg, len);
}

//msg must be ended by '\0'
void Log::E(wchar_t* tag, wchar_t* msg)
{
	int len = wcslen(msg);
	E(tag, msg, len);
}

//msg must be ended by '\0'
void Log::I(wchar_t* tag, wchar_t* msg)
{
	int len = wcslen(msg);
	I(tag, msg, len);
}

//msg must be ended by '\0'
void Log::W(char* tag, char* msg)
{
	int len = strlen(msg);
	W(Utils::getWChar(tag),Utils::getWChar(msg),len);
}

//msg must be ended by '\0'
void Log::E(char* tag, char* msg)
{
	int len = strlen(msg);
	E(Utils::getWChar(tag),Utils::getWChar(msg),len);
}

//msg must be ended by '\0'
void Log::I(char* tag, char* msg)
{
	int len = strlen(msg);
	I(Utils::getWChar(tag),Utils::getWChar(msg),len);
}
