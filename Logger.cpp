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

#include <Logger.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui_internal.h"

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
		
		GLFWwindow* currentWindow = glfwGetCurrentContext();
		str = "thread(" + ct::toStr(currentWindow) + ") " + str;
		int64 ticks = ct::GetTicks(); 
		float time = (ticks - lastTick) / 1000.0f;
		std::cout << "t:" << time << "s " << str << std::endl;
		if (debugLogFile->bad() == false)
			*debugLogFile << "t:" << time << "s " << str << std::endl;
	}
}

void Logger::LogString(std::string vFile, std::string vFunction, std::string vLine, std::string vMsg)
{
	if (vMsg.size() > 0/* && Logger::Instance()->ConsoleVerbose*/)
	{
		m_ConsoleMap[vFile][vFunction][vLine].push_back(vMsg);

		GLFWwindow* currentWindow = glfwGetCurrentContext();
		std::string str = "thread(" + ct::toStr(currentWindow) + ") " + vFile + " " + vFunction + " " + vLine + " " + vMsg;
		int64 ticks = ct::GetTicks();
		float time = (ticks - lastTick) / 1000.0f;
		std::cout << "t:" << time << "s " << str << std::endl;
		if (debugLogFile->bad() == false)
			*debugLogFile << "t:" << time << "s " << str << std::endl;
	}
}

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
			GLFWwindow* currentWindow = glfwGetCurrentContext();
			error = "thread(" + ct::toStr(currentWindow) + ") OpenGL error : " + error + " in " + vFile + " " + vFunc + " " + ct::toStr(vLine) + " " + vGLFunc;
			int64 ticks = ct::GetTicks();
			float time = (ticks - lastTick) / 1000.0f;
			std::cout << "t:" << time << "s : " << error << std::endl;
			if (debugLogFile->bad() == false)
				*debugLogFile << "t:" << time << "s : " << error << std::endl;
		}
	}
}

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

void Logger::Close()
{
	debugLogFile->close();
}
