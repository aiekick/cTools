/*
MIT License

Copyright (c) 2010-2020 Stephane Cuillerdier (aka Aiekick)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#ifdef COCOS2D
#include "cocos2d.h"
#endif

#include <cTools.h>

#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

#include <cassert>
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

#ifdef MSVC
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#define LogStr(n) Logger::Instance()->LogString(std::string(__FILE__), std::string(__PRETTY_FUNCTION__), ct::toStr(__LINE__), (n))
#define LogVar(s, ...) Logger::Instance()->LogString(std::string(__PRETTY_FUNCTION__), ct::toStr(__LINE__), s, __VA_ARGS__);
#define LogValue(s, n) Logger::Instance()->LogString(/*std::string(__FILE__) + " " + */std::string(__PRETTY_FUNCTION__) + " " + ct::toStr(__LINE__) + " : " + (s) + " = " + ct::toStr(n))
#ifdef USE_OPENGL
#define LogGlError() Logger::Instance()->LogGLError(""/*__FILE__*/,__FUNCTION__,__LINE__, "")
#define LogGlErrorVar(var) Logger::Instance()->LogGLError(""/*__FILE__*/,__FUNCTION__,__LINE__,var)
#endif
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
	void LogString(const char* fmt, ...);
	void LogString(std::string vPrettyFunction, std::string vLine, const char* fmt, ...);
#ifdef USE_OPENGL
	void LogGLError(std::string vFile, std::string vFunc, int vLine, std::string vGLFunc = "");
#endif
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
