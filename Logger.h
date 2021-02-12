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

#include "cTools.h"

#include <cstdarg>     /* va_list, va_start, va_arg, va_end */

#include <mutex>
#include <cassert>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
using namespace std;

typedef long long int64;

#ifdef MSVC
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#define IsVerboseMode Logger::Instance()->ConsoleVerbose == true
#define LogVar(s, ...) Logger::Instance()->LogStringWithFunction(std::string(__FUNCTION__), (int)(__LINE__), s, __VA_ARGS__)
#define LogVarDebug(s, ...) Logger::Instance()->LogStringWithFunction_Debug(std::string(__FUNCTION__), (int)(__LINE__), s, __VA_ARGS__)
#define LogVarLight(s, ...) Logger::Instance()->LogString(s, __VA_ARGS__)
#define LogAssert(a,b,...) if (!(a)) { LogVarDebug(b,__VA_ARGS__); assert(a); }

#ifdef USE_OPENGL
#define LogGlError() Logger::Instance()->LogGLError(""/*__FILE__*/,__FUNCTION__,__LINE__, "")
#define LogGlErrorVar(var) Logger::Instance()->LogGLError(""/*__FILE__*/,__FUNCTION__,__LINE__,var)
#endif

struct ImGuiContext;
class Logger
{
protected:
	static std::mutex Logger_Mutex;

private:
	static ofstream *debugLogFile;
	static wofstream *wdebugLogFile;
	int64 lastTick = 0;

public:
	static Logger* Instance()
	{
		static auto*puinstance = new Logger();
		return puinstance;
	}

public:
	bool ConsoleVerbose = false;
	// file, function, line, msg
	std::vector<std::string> puMessages;

public:
	Logger(void);
	~Logger(void);
	void LogString(const char* fmt, ...);
	void LogStringWithFunction(const std::string& vFunction, int vLine, const char* fmt, ...);
	void LogStringWithFunction_Debug(const std::string& vFunction, int vLine, const char* fmt, ...);
#ifdef USE_OPENGL
	void LogGLError(const std::string& vFile, const std::string& vFunc, int vLine, const std::string& vGLFunc = "") const;
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
        const DWORD errorMessageID = ::GetLastError();
		if (errorMessageID == 0 || errorMessageID == 6)
			return std::string(); //No error message has been recorded

		LPSTR messageBuffer = nullptr;
        const size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                           nullptr, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, nullptr);

        msg = std::string(messageBuffer, size);

		//Free the buffer.
		LocalFree(messageBuffer);
#else
		//cAssert(0, "to implement");
#endif
		return msg;
	}
};
