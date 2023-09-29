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
#pragma warning(disable : 4251)

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || defined(__WIN64__) || defined(WIN64) || \
    defined(_WIN64) || defined(_MSC_VER)
#if defined(ctools_EXPORTS)
#define CTOOLS_API __declspec(dllexport)
#elif defined(BUILD_CTOOLS_SHARED_LIBS)
#define CTOOLS_API __declspec(dllimport)
#else
#define CTOOLS_API
#endif
#else
#define CTOOLS_API
#endif

#include <ctools/cTools.h>

#include <cstdarg> /* va_list, va_start, va_arg, va_end */

#include <mutex>
#include <cassert>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <memory>
#include <functional>
using namespace std;

typedef long long int64;

#ifdef MSVC
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

typedef int LogMessageType;
enum _LogMessageType {
    LOGGING_MESSAGE_TYPE_INFOS = 0,
    LOGGING_MESSAGE_TYPE_WARNING,
    LOGGING_MESSAGE_TYPE_ERROR
};

#define IsVerboseMode Logger::Instance()->ConsoleVerbose == true

// #define LogVar(s, ...) Logger::Instance()->LogStringWithFunction(std::string(__FUNCTION__), (int)(__LINE__), s,
// ##__VA_ARGS__)

#define LogVarError(s, ...)                          \
    Logger::Instance()->LogStringByTypeWithFunction( \
        LOGGING_MESSAGE_TYPE_ERROR, std::string(__FUNCTION__), (int)(__LINE__), s, ##__VA_ARGS__)

#define LogVarWarning(s, ...)                                                                         \
    Logger::Instance()->LogStringByTypeWithFunction(LOGGING_MESSAGE_TYPE_WARNING, \
        std::string(__FUNCTION__), (int)(__LINE__), s, ##__VA_ARGS__)

#define LogVarInfo(s, ...)                           \
    Logger::Instance()->LogStringByTypeWithFunction( \
        LOGGING_MESSAGE_TYPE_INFOS, std::string(__FUNCTION__), (int)(__LINE__), s, ##__VA_ARGS__)

#define LogVarDebugError(s, ...)                          \
    Logger::Instance()->LogStringByTypeWithFunction_Debug( \
        LOGGING_MESSAGE_TYPE_ERROR, std::string(__FUNCTION__), (int)(__LINE__), s, ##__VA_ARGS__)

#define LogVarDebugWarning(s, ...)                        \
    Logger::Instance()->LogStringByTypeWithFunction_Debug( \
        LOGGING_MESSAGE_TYPE_WARNING, std::string(__FUNCTION__), (int)(__LINE__), s, ##__VA_ARGS__)

#define LogVarDebugInfo(s, ...)                           \
    Logger::Instance()->LogStringByTypeWithFunction_Debug( \
        LOGGING_MESSAGE_TYPE_INFOS, std::string(__FUNCTION__), (int)(__LINE__), s, ##__VA_ARGS__)

#define LogVarLightError(s, ...) \
    Logger::Instance()->LogSimpleStringByType(LOGGING_MESSAGE_TYPE_ERROR, s, ##__VA_ARGS__)

#define LogVarLightWarning(s, ...) \
    Logger::Instance()->LogSimpleStringByType(LOGGING_MESSAGE_TYPE_WARNING, s, ##__VA_ARGS__)

#define LogVarLightInfo(s, ...) \
    Logger::Instance()->LogSimpleStringByType(LOGGING_MESSAGE_TYPE_INFOS, s, ##__VA_ARGS__)

#define LogVarTag(t, s, ...) \
    Logger::Instance()->LogStringByTypeWithFunction(t, std::string(__FUNCTION__), (int)(__LINE__), s, ##__VA_ARGS__)

#define LogVarLightTag(t, s, ...) \
    Logger::Instance()->LogSimpleStringByType(t, s, ##__VA_ARGS__)

#define LogAssert(a, b, ...)           \
    if (!(a)) {                        \
        LogVarDebugInfo(b, ##__VA_ARGS__); \
        assert(a);                     \
    }

#ifdef USE_OPENGL
#define LogGlError() Logger::Instance()->LogGLError("" /*__FILE__*/, __FUNCTION__, __LINE__, "")
#define LogGlErrorVar(var) Logger::Instance()->LogGLError("" /*__FILE__*/, __FUNCTION__, __LINE__, var)
#endif

struct ImGuiContext;
class CTOOLS_API Logger {
public:
    static std::function<void(const int& vType, const std::string& vMessage)> sStandardLogFunction;
    static std::function<void(const int& vType, const std::string& vMessage)> sOpenGLLogFunction;

protected:
    static std::mutex Logger_Mutex;

private:
    static ofstream debugLogFile;
    int64 lastTick = 0;

private:
    void LogString(const LogMessageType* vType, const std::string* vFunction, const int* vLine, const char* vStr);
    void LogString(const LogMessageType* vType,
        const std::string* vFunction,
        const int* vLine,
        const char* fmt,
        va_list vArgs);

public:
    static Logger* Instance() {
        static Logger _Instance;
        return &_Instance;
    }

public:
    bool ConsoleVerbose = false;
    // file, function, line, msg
    std::vector<std::string> puMessages;

public:
    Logger();
    ~Logger();
    void LogSimpleString(const char* fmt, ...);
    void LogSimpleStringByType(const LogMessageType& vType, const char* fmt, ...);
    void LogStringWithFunction(const std::string& vFunction, const int& vLine, const char* fmt, ...);
    void LogStringByTypeWithFunction(
        const LogMessageType& vType, const std::string& vFunction, const int& vLine, const char* fmt, ...);
    void LogStringByTypeWithFunction_Debug(
        const LogMessageType& vType, const std::string& vFunction, const int& vLine, const char* fmt, ...);
    void LogStringWithFunction_Debug(const std::string& vFunction, const int& vLine, const char* fmt, ...);
#ifdef USE_OPENGL
    bool LogGLError(
        const std::string& vFile, const std::string& vFunc, int vLine, const std::string& vGLFunc = "") const;
#endif
    void Close();

public:
    std::string GetLastErrorAsString();
};
