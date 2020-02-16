#ifndef _LOGGER_H_
#define _LOGGER_H_

#ifdef COCOS2D
#include "cocos2d.h"
#endif

#include "cTools.h"

#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <map>
#include <vector>
#include <sstream>
#include <exception>
using namespace std;

typedef long long int64;

#define LogStr(n) Logger::Instance()->LogString(std::string(__FILE__), std::string(__FUNCTION__), ct::toStr(__LINE__), (n))
//#define LogStr(n) Logger::Instance()->LogString(std::string(__FILE__) + " " + std::string(__FUNCTION__) + " " + ct::toStr(__LINE__) + " " + (n))
#define LogValue(s, n) Logger::Instance()->LogString(/*std::string(__FILE__) + " " + */std::string(__FUNCTION__) + " " + ct::toStr(__LINE__) + " : " + (s) + " = " + ct::toStr(n))
#define LogGlError() Logger::Instance()->LogGLError(""/*__FILE__*/,__FUNCTION__,__LINE__, "")
#define LogGlErrorVar(var) Logger::Instance()->LogGLError(""/*__FILE__*/,__FUNCTION__,__LINE__,var)
#define LogAssert(a,b) if (!(a)) { LogStr(b); assert(a); }

struct ImGuiContext;
class Logger
{
private:
	static ofstream *debugLogFile;
	static wofstream *wdebugLogFile;
	int64 lastTick = 0;

public:
	static Logger* Instance()
	{
		static Logger *m_instance = new Logger();
		return m_instance;
	}

public:
	bool ConsoleVerbose = false;
	// file, function, line, msg
	std::map<std::string, std::map<std::string, std::map<std::string, std::list<std::string>>>> m_ConsoleMap;

public:
	Logger(void);
	~Logger(void);
	void LogString(std::string vFile, std::string vFunction, std::string vLine, std::string vMsg);
	void LogString(std::string str);
	void LogString(wstring str);
	void LogGLError(std::string vFile, std::string vFunc, int vLine, std::string vGLFunc = "");
	void Close();

public:
	/////////////////////////////////////////////////////////////
	///////// Returns the last Win32 error //////////////////////
	/////////////////////////////////////////////////////////////
	std::string GetLastErrorAsString()
	{
        std::string msg;

#ifdef WIN32
		//Get the error message, if any.
		DWORD errorMessageID = ::GetLastError();
		if (errorMessageID == 0 || errorMessageID == 6)
			return std::string(); //No error message has been recorded

		LPSTR messageBuffer = nullptr;
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

        msg = std::string(messageBuffer, size);

		//Free the buffer.
		LocalFree(messageBuffer);
#else
		//cAssert(0, "to implement");
#endif
		return msg;
	}
};

#endif /* _DEBUGLOGGER_H_ */
