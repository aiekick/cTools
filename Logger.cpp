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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// singleton
ofstream *Logger::debugLogFile = new ofstream("debug.log", ios::out);
//wofstream *Logger::wdebugLogFile = new wofstream("wdebug.log", ios::out);

Logger::Logger(void) 
{
	lastTick = ct::GetTicks();
	ConsoleVerbose = false;
}

Logger::~Logger(void) 
{

}

void Logger::LogString(std::string str)
{
	if (str.size() > 0/* && Logger::Instance()->ConsoleVerbose*/)
	{
		m_ConsoleMap["App"][""][""].push_back(str);
		
#ifdef USE_GLFW3
		GLFWwindow* currentWindow = glfwGetCurrentContext();
		str = "thread(" + ct::toStr(currentWindow) + ") " + str;
#endif
		int64 ticks = ct::GetTicks(); 
		float time = (ticks - lastTick) / 1000.0f;
		std::cout << "t:" << time << "s " << str << std::endl;
		if (!debugLogFile->bad())
			*debugLogFile << "t:" << time << "s " << str << std::endl;
	}
}

void Logger::LogString(std::string vFile, std::string vFunction, std::string vLine, std::string vMsg)
{
	if (vMsg.size() > 0/* && Logger::Instance()->ConsoleVerbose*/)
	{
		m_ConsoleMap[vFile][vFunction][vLine].push_back(vMsg);
		std::string str = vFile + " " + vFunction + " " + vLine + " " + vMsg;
#ifdef USE_GLFW3
		GLFWwindow* currentWindow = glfwGetCurrentContext();
		str = "thread(" + ct::toStr(currentWindow) + ") " + str;
#endif 
		int64 ticks = ct::GetTicks();
		float time = (ticks - lastTick) / 1000.0f;
		std::cout << "t:" << time << "s " << str << std::endl;
		if (!debugLogFile->bad())
			*debugLogFile << "t:" << time << "s " << str << std::endl;
	}
}

#ifdef USE_OPENGL
void Logger::LogGLError(std::string vFile, std::string vFunc, int vLine, std::string vGLFunc)
{
	if (!Logger::Instance()->ConsoleVerbose)
		return;

	GLenum err(glGetError());
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

		if (error.size() > 0)
		{
#ifdef USE_GLFW3
			GLFWwindow* currentWindow = glfwGetCurrentContext();
			error = "thread(" + ct::toStr(currentWindow) + ") ";
#endif 
			error += "OpenGL error : " + error + " in " + vFile + " " + vFunc + " " + ct::toStr(vLine) + " " + vGLFunc;
			int64 ticks = ct::GetTicks();
			float time = (ticks - lastTick) / 1000.0f;
			std::cout << "t:" << time << "s : " << error << std::endl;
			if (!debugLogFile->bad())
				*debugLogFile << "t:" << time << "s : " << error << std::endl;
		}
	}
}
#endif

void Logger::LogString(wstring str)
{
	if (str.size() > 0)
	{
		//int ticks = 0;// SDL_GetTicks();
		//float time = ticks / 1000.0f;
		//std::cout << "t:" << time << "s " << str << std::endl;
		//if (wdebugLogFile->bad() == false)
		//	*wdebugLogFile << "t:" << time << "s " << str << std::endl;
	}
}

void Logger::LogString(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char TempBuffer[1024 * 3 + 1];
	int w = vsnprintf(TempBuffer, 1024 * 3 + 1, fmt, args);
	if (w)
	{
		std::string msg = std::string(TempBuffer, w);
		m_ConsoleMap["App"][""][""].push_back(msg);
		std::string str = msg;
#ifdef USE_GLFW3
		GLFWwindow* currentWindow = glfwGetCurrentContext();
		str = "thread(" + ct::toStr(currentWindow) + ") " + msg;
#endif 
		int64 ticks = ct::GetTicks();
		float time = (ticks - lastTick) / 1000.0f;
		std::cout << "t:" << time << "s " << str << std::endl;
		if (!debugLogFile->bad())
			*debugLogFile << "t:" << time << "s " << str << std::endl;
	}
	va_end(args);
}


void Logger::LogString(std::string vPrettyFunction, std::string vLine, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	char TempBuffer[1024 * 3 + 1];
	int w = vsnprintf(TempBuffer, 1024 * 3 + 1, fmt, args);
	if (w)
	{
		std::string msg = vPrettyFunction + ":line(" + vLine + ") => " + std::string(TempBuffer, w);
		m_ConsoleMap["App"][""][""].push_back(msg);
		std::string str = msg;
#ifdef USE_GLFW3
		GLFWwindow* currentWindow = glfwGetCurrentContext();
		str = "thread(" + ct::toStr(currentWindow) + ") " + msg;
#endif 
		int64 ticks = ct::GetTicks();
		float time = (ticks - lastTick) / 1000.0f;
		std::cout << "t:" << time << "s " << str << std::endl;
		if (!debugLogFile->bad())
			*debugLogFile << "t:" << time << "s " << str << std::endl;
	}
	va_end(args);
}

void Logger::Close()
{
	debugLogFile->close();
}
