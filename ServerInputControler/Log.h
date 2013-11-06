#pragma once

class Log
{
public:
	Log(void);
	~Log(void);

	//////////wchar_t Version
	static void W(wchar_t* tag, wchar_t* msg, int msgLen);
	static void E(wchar_t* tag, wchar_t* msg, int msgLen);
	static void I(wchar_t* tag, wchar_t* msg, int msgLen);

	//msg must be ended by '\0'
	static void W(wchar_t* tag, wchar_t* msg);

	//msg must be ended by '\0'
	static void E(wchar_t* tag, wchar_t* msg);

	//msg must be ended by '\0'
	static void I(wchar_t* tag, wchar_t* msg);

	/////////char Version
	//msg must be ended by '\0'
	static void W(char* tag, char* msg);

	//msg must be ended by '\0'
	static void E(char* tag, char* msg);

	//msg must be ended by '\0'
	static void I(char* tag, char* msg);

private:
	static void PrintLog(char type, wchar_t* tag, wchar_t* buf, int bufLen);

	static const int MAX_CHAR=200;
};
