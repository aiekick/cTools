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
#endif
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
#include <tracy/Tracy.hpp>
#endif

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// singleton
ofstream *Logger::debugLogFile = new ofstream("debug.log", ios::out);
//wofstream *Logger::wdebugLogFile = new wofstream("wdebug.log", ios::out);
std::mutex Logger::Logger_Mutex;

Logger::Logger(void) 
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
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

void Logger::LogString(const char* fmt, ...)
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	va_list args;
	va_start(args, fmt);
	static char TempBuffer[3072 + 1];//3072 = 1024 * 3
	int w = vsnprintf(TempBuffer, 3072, fmt, args);
	if (w)
	{
		const int64 ticks = ct::GetTicks();
		const float time = (ticks - lastTick) / 100.0f;

		static char TempBufferBis[3072 + 1];
		w = snprintf(TempBufferBis, 3072, "[%.3fs]%s", time, TempBuffer);
		if (w)
		{
			const std::string msg = std::string(TempBufferBis, w);
			puMessages.push_back(msg);
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
			TracyMessageL(puMessages[puMessages.size() - 1U].c_str());
#endif
			printf("%s\n", msg.c_str());
			if (!debugLogFile->bad())
				*debugLogFile << msg << std::endl;
		}
	}
	va_end(args);
	lck.unlock();
}

void Logger::LogStringWithFunction_Debug(const std::string& vFunction, int vLine, const char* fmt, ...)
{
#ifdef _DEBUG
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	va_list args;
	va_start(args, fmt);
	static char TempBuffer[1024 * 3 + 1];
	int w = vsnprintf(TempBuffer, 1024 * 3, fmt, args);
	if (w)
	{
		const int64 ticks = ct::GetTicks();
		const float time = (ticks - lastTick) / 100.0f;

		static char TempBufferBis[1024 * 3 + 1];
		w = snprintf(TempBufferBis, 1024 * 3, "[%.3fs][%s:%i] => %s", time, vFunction.c_str(), vLine, TempBuffer);
		if (w)
		{
			const std::string msg = std::string(TempBufferBis, w);
			puMessages.push_back(msg);
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
			TracyMessageL(puMessages[puMessages.size() - 1U].c_str());
#endif
			printf("%s\n", msg.c_str());
			if (!debugLogFile->bad())
				*debugLogFile << msg << std::endl;
		}
	}
	va_end(args);
	lck.unlock();
#else
	UNUSED(vFunction);
	UNUSED(vLine);
	UNUSED(fmt);
#endif
}

void Logger::LogStringWithFunction(const std::string& vFunction, int vLine, const char* fmt, ...)
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	va_list args;
	va_start(args, fmt);
	static char TempBuffer[1024 * 3 + 1];
	int w = vsnprintf(TempBuffer, 1024 * 3, fmt, args);
	if (w)
	{
		const int64 ticks = ct::GetTicks();
		const float time = (ticks - lastTick) / 100.0f;
		
		static char TempBufferBis[1024 * 3 + 1];
		w = snprintf(TempBufferBis, 1024 * 3, "[%.3fs][%s:%i] => %s", time, vFunction.c_str(), vLine, TempBuffer);
		if (w)
		{
			const std::string msg = std::string(TempBufferBis, w);
			puMessages.push_back(msg);
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
			TracyMessageL(puMessages[puMessages.size() - 1U].c_str());
#endif
			printf("%s\n", msg.c_str());
			if (!debugLogFile->bad())
				*debugLogFile << msg << std::endl;
		}
	}
	va_end(args);
	lck.unlock();
}

#ifdef USE_OPENGL
void Logger::LogGLError(const std::string& vFile, const std::string& vFunc, int vLine, const std::string& vGLFunc) const
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	if (!Logger::Instance()->ConsoleVerbose)
		return;

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
#ifdef USE_GLFW3
			GLFWwindow* currentWindow = glfwGetCurrentContext();
			error = "thread(" + ct::toStr(currentWindow) + ") ";
#endif 
			error += "OpenGL error : " + error + " in " + vFile + " " + vFunc + " " + ct::toStr(vLine) + " " + vGLFunc;
			const int64 ticks = ct::GetTicks();
			const float time = (ticks - lastTick) / 1000.0f;
			std::cout << "t:" << time << "s : " << error << std::endl;
			if (!debugLogFile->bad())
				*debugLogFile << "t:" << time << "s : " << error << std::endl;

			CTOOL_DEBUG_BREAK;
		}
	}
}
#endif

void Logger::Close()
{
#if defined(TRACY_ENABLE) && defined(LOG_TRACY_MESSAGES)
	ZoneScoped;
#endif
	std::unique_lock<std::mutex> lck(Logger::Logger_Mutex, std::defer_lock);
	lck.lock();
	debugLogFile->close();
	lck.unlock();
}
