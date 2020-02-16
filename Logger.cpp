// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Logger.h"
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
