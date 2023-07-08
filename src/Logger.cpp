// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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

#include "Logger.h"

#ifdef USE_GLFW3
#include <GLFW/glfw3.h>
#elif defined(USE_SDL2)
#include <SDL.h>
#endif
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
#include <tracy/Tracy.hpp>
#endif

////////////////////////////////////////////////////////////////////////////////
//// STATIC ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

std::function<void(const int& vType, const std::string& vMessage)> Logger::sStandardLogFunction = nullptr;
std::function<void(const int& vType, const std::string& vMessage)> Logger::sOpenGLLogFunction = nullptr;

////////////////////////////////////////////////////////////////////////////////
//// CONSTRUCTORS //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// singleton
ofstream Logger::debugLogFile;
std::mutex Logger::Logger_Mutex;

Logger::Logger(void)
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	debugLogFile.open("debug.log", ios::out);
	lastTick = ct::GetTicks();
	ConsoleVerbose = false;
	lck.unlock();
}

Logger::~Logger(void)
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	Close();
}

#define MAX_BUFFER_SIZE 1024 * 3

void Logger::LogString(const LogMessageTypeEnum* vType, const std::string* vFunction, const int* vLine, const char* vStr)
{
	const int64 ticks = ct::GetTicks();
	const double time = (ticks - lastTick) / 100.0;

	static char TempBufferBis[MAX_BUFFER_SIZE + 1];
	int w = 0;
	if (vFunction && vLine)
		w = snprintf(TempBufferBis, MAX_BUFFER_SIZE, "[%010.3fs][%s:%i] %s", time, vFunction->c_str(), *vLine, vStr);
	else
		w = snprintf(TempBufferBis, MAX_BUFFER_SIZE, "[%010.3fs] %s", time, vStr);
	if (w)
	{
		const std::string msg = std::string(TempBufferBis, (size_t)w);

		puMessages.push_back(msg);

#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
		TracyMessageL(puMessages[puMessages.size() - 1U].c_str());
#endif

		printf("%s\n", msg.c_str());

		if (vStr && sStandardLogFunction)
		{
			int type = 0;

			if (vType)
			{
				type = (int)(*vType);
			}

			auto arr = ct::splitStringToVector(msg, '\n');
			if (arr.size() == 1U)
			{
				sStandardLogFunction(type, msg);
			}
			else
			{
				for (auto m : arr)
				{
					sStandardLogFunction(type, m);
				}
			}
		}

		if (!debugLogFile.bad())
			debugLogFile << msg << std::endl;
	}
}

void Logger::LogString(const LogMessageTypeEnum* vType, const std::string* vFunction, const int* vLine, const char* fmt, va_list vArgs)
{
	static char TempBuffer[MAX_BUFFER_SIZE + 1];
	int w = vsnprintf(TempBuffer, MAX_BUFFER_SIZE, fmt, vArgs);
	if (w)
	{
		LogString(vType, vFunction, vLine, TempBuffer);
	}
}

void Logger::LogSimpleString(const char* fmt, ...)
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	va_list args;
	va_start(args, fmt);
	LogString(nullptr, nullptr, nullptr, fmt, args);
	va_end(args);
	lck.unlock();
}

void Logger::LogSimpleStringByType(const LogMessageTypeEnum& vType, const char* fmt, ...)
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	va_list args;
	va_start(args, fmt);
	LogString(&vType, nullptr, nullptr, fmt, args);
	va_end(args);
	lck.unlock();
}

void Logger::LogStringWithFunction(const std::string& vFunction, const int& vLine, const char* fmt, ...)
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	va_list args;
	va_start(args, fmt);
	LogString(nullptr, &vFunction, &vLine, fmt, args);
	va_end(args);
	lck.unlock();
}

void Logger::LogStringByTypeWithFunction(const LogMessageTypeEnum& vType, const std::string& vFunction, const int& vLine, const char* fmt, ...)
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	va_list args;
	va_start(args, fmt);
	LogString(&vType, &vFunction, &vLine, fmt, args);
	va_end(args);
	lck.unlock();
}

void Logger::LogStringWithFunction_Debug(const std::string& vFunction, const int& vLine, const char* fmt, ...)
{
#ifdef _DEBUG
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	va_list args;
	va_start(args, fmt);
	LogString(nullptr, &vFunction, &vLine, fmt, args);
	va_end(args);
	lck.unlock();
#else
	UNUSED(vFunction);
	UNUSED(vLine);
	UNUSED(fmt);
#endif
}

#ifdef USE_OPENGL
bool Logger::LogGLError(const std::string& vFile, const std::string& vFunc, int vLine, const std::string& vGLFunc) const
{
	UNUSED(vFile);

#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	if (!Logger::Instance()->ConsoleVerbose)
		return false;

	const GLenum err(glGetError());
	if (err != GL_NO_ERROR)
	{
		std::string error;

		switch (err)
		{
		case GL_INVALID_OPERATION:				error = "INVALID_OPERATION";				break;
		case GL_INVALID_ENUM:					error = "INVALID_ENUM";						break;
		case GL_INVALID_VALUE:					error = "INVALID_VALUE";					break;
		case GL_OUT_OF_MEMORY:					error = "OUT_OF_MEMORY";					break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";	break;
		case GL_STACK_UNDERFLOW:				error = "GL_STACK_UNDERFLOW";				break;
		case GL_STACK_OVERFLOW:					error = "GL_STACK_OVERFLOW";				break;
		}

		if (!error.empty())
		{
			const int64 ticks = ct::GetTicks();
			const float time = (ticks - lastTick) / 1000.0f;

			std::string msg;


			if (!vGLFunc.empty())
			{
#ifdef USE_GLFW3
				msg = ct::toStr("[%010.3fs][GLFW3 0x%X][%s:%i] %s in %s\n", time, (uintptr_t)glfwGetCurrentContext(), vFunc.c_str(), vLine, error.c_str(), vGLFunc.c_str());
#elif defined(USE_SDL2)
				msg = ct::toStr("[%010.3fs][SDL2 0x%X][%s:%i] %s in %s\n", time, (uintptr_t)SDL_GL_GetCurrentContext(), vFunc.c_str(), vLine, error.c_str(), vGLFunc.c_str());
#endif
			}
			else
			{
#ifdef USE_GLFW3
				msg = ct::toStr("[%010.3fs][GLFW3 0x%X][%s:%i] %s\n", time, (uintptr_t)glfwGetCurrentContext(), vFunc.c_str(), vLine, error.c_str());
#elif defined(USE_SDL2)
				msg = ct::toStr("[%010.3fs][SDL2 0x%X][%s:%i] %s\n", time, (uintptr_t)SDL_GL_GetCurrentContext(), vFunc.c_str(), vLine, error.c_str());
#endif
			}
			
			LogVarLightError("%s", msg.c_str());

			if (sOpenGLLogFunction)
			{
				auto arr = ct::splitStringToVector(msg, '\n');
				if (arr.size() == 1U)
				{
					sOpenGLLogFunction(2, msg);
				}
				else
				{
					for (auto m : arr)
					{
						sOpenGLLogFunction(2, m);
					}
				}
			}

			if (!debugLogFile.bad())
				debugLogFile << msg << std::endl;

			return true;
		}
	}

	return false;
}
#endif

void Logger::Close()
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	debugLogFile.close();
	lck.unlock();
}

std::string Logger::GetLastErrorAsString()
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