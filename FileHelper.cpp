// This is an open source non-commercial project. Dear PVS-Studio, please check it.
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

//#pragma warning(disable:4311)
//#pragma warning(disable:4302)

#include "FileHelper.h"

#include "cTools.h"
#include "Logger.h"

// for clipboard
#include <GLFW/glfw3.h>

// general
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cerrno>
#include <chrono>
#include <ctime>
#include <cstdio>  /* defines FILENAME_MAX */

// specific
#ifdef WIN32
	// includes
	#include <windows.h>
	#include <shellapi.h>
	#pragma comment(lib,"shlwapi.lib")
	#include <direct.h>
	// defines
	#define stat _stat
	#define S_IFDIR _S_IFDIR
	#define GetCurrentDir _getcwd
	#define SetCurrentDir _chdir
#elif defined(UNIX)
	// includes
	#include <unistd.h>
	#include <sys/param.h>
	#include <sys/file.h>
	#include <sys/wait.h>
	#include <ctype.h>
	#include <pwd.h>
	#include <time.h>
	#include <signal.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <dirent.h>
	#include <cstdlib>
	#include <stdio.h>
	#ifdef APPLE
		#include <dlfcn.h>
		#include <sys/syslimits.h> // PATH_MAX
	#endif
	#ifdef STDC_HEADERS
		#include <stdlib.h>
		#include <stddef.h>
	#else
		#ifdef HAVE_STDLIB_H
			#include <stdlib.h>
		#endif
	#endif /* STDC_HEADERS */
	#ifdef HAVE_STRING_H
		#include <string.h>
	#endif /* HAVE_STRING_H */
	#ifdef HAVE_UNISTD_H
		#include <unistd.h>
	#endif
	// defines
	#define GetCurrentDir getcwd
	#define SetCurrentDir chdir
	#ifndef S_IFDIR
		#define S_IFDIR __S_IFDIR
	#endif
	#ifndef MAX_PATH
		#define MAX_PATH PATH_MAX
	#endif
	#ifndef PATH_MAX
		#define PATH_MAX MAX_PATH
	#endif
#endif

PathStruct::PathStruct()
{
	isOk = false;
}

std::string PathStruct::GetFilePathWithNameExt(const std::string& vName, const std::string& vExt) // need a refactoring
{
	if (path[0] == FileHelper::Instance()->m_SlashType[0])
	{
#ifdef WIN32
		// if it happening on window this seem that this path msut be a relative path but with an error

		path = path.substr(1); // bad formated path go relative
#endif
	}
	else
	{
#ifdef UNIX
		path = "/" + path; // make it absolute
#endif
	}

	return path + FileHelper::Instance()->m_SlashType + vName + vExt;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// static
std::string FileHelper::AppPath = std::string();

FileHelper::FileHelper()
{
#ifdef WIN32
	m_SlashType = "\\";
#endif
#ifdef UNIX
	m_SlashType = "/";
#endif
#ifdef _DEBUG
	//Test_GetRelativePathToPath();
#endif
}

FileHelper::~FileHelper() = default;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string FileHelper::LoadFileToString(const std::string& vFilePathName)
{
	std::string fileCode;

	std::ifstream docFile(vFilePathName, std::ios::in);
	if (docFile.is_open())
	{
		std::stringstream strStream;
		strStream << docFile.rdbuf();//read the file

		fileCode = strStream.str();

		ct::replaceString(fileCode, "\r\n", "\n");

		docFile.close();
	}
	else
	{
		printf("File %s Not Found !\n", vFilePathName.c_str());
	}

	return fileCode;
}

void FileHelper::SaveStringToFile(const std::string& vString, const std::string& vFilePathName)
{
	std::ofstream fileWriter(vFilePathName, std::ios::out);
	if (!fileWriter.bad())
	{
		fileWriter << vString;
		fileWriter.close();
	}
}

std::vector<uint8_t> FileHelper::LoadFileToBytes(const std::string& vFilePathName, errno_t *vError)
{
	std::vector<uint8_t> bytes;

	FILE* intput_file = NULL;
#if defined(MSVC)
	fopen_s(&intput_file, vFilePathName.c_str(), "rb");
#else
	intput_file = fopen(vFilePathName.c_str(), "rb");
#endif
	if (vError)
		*vError = errno;
	if (intput_file != reinterpret_cast<FILE*>(NULL))
	{
		long fileSize = 0;
		
		// obtain file size:
		fseek(intput_file, 0, SEEK_END);
		fileSize = ftell(intput_file);
		rewind(intput_file);

		bytes.resize(fileSize);

		// copy the file into the buffer:
		fread(bytes.data(), 1, fileSize, intput_file);

		// terminate
		fclose(intput_file);
	}
	else
	{

	}

	return bytes;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
PathStruct FileHelper::ParsePathFileName(const std::string& vPathFileName)
{
	PathStruct res;

	if (vPathFileName.size() > 0)
	{
		std::string pfn = CorrectFilePathName(vPathFileName);
		size_t lastSlash = pfn.find_last_of(m_SlashType);
		if (lastSlash != std::string::npos)
		{
			res.name = pfn.substr(lastSlash + 1);
			res.path = pfn.substr(0, lastSlash);
			res.isOk = true;
		}

		size_t lastPoint = pfn.find_last_of('.');
		if (lastPoint != std::string::npos)
		{
			if (!res.isOk)
			{
				res.name = pfn;
				res.isOk = true;
			}
			res.ext = pfn.substr(lastPoint + 1);
			ct::replaceString(res.name, "." + res.ext, "");
		}
	}

	return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void FileHelper::RegisterPath(FileLocation vLoc, const std::string& vPath)
{
	m_RegisteredPaths[vLoc] = vPath;
}

std::string FileHelper::GetExistingFilePathForFile(const std::string& vFileName)
{
	std::string res;

	std::string path;
	for (auto it = m_SearchPaths.begin(); it != m_SearchPaths.end(); ++it)
	{
		path = *it + m_SlashType + vFileName;
		if (IsFileExist(path))
		{
			res = path;
			break;
		}
	}

		if (res.empty())
			printf("Cant found file %s\n", vFileName.c_str());
	
	return res;
}

/* correct file path between os and different slash tyupe between window and unix */
std::string FileHelper::CorrectFilePathName(const std::string &vFilePathName)
{
	std::string res = vFilePathName;
	ct::replaceString(res, "\\", m_SlashType);
	ct::replaceString(res, "/", m_SlashType);
	return res;
}

#ifdef _DEBUG
void FileHelper::Test_GetRelativePathToPath()
{
	printf("------------------------------------------------------\n");
	printf("-- Test of FileHelper::Test_GetRelativePathToPath() --\n");
	printf("------------------------------------------------------\n\n");

	std::string rootPath;
	std::string in;
	std::string out;

	rootPath = "C:\\gamedev\\github\\ImGuiFontStudio_avp\\projects";
	in = "C:\\gamedev\\github\\ImGuiFontStudio_avp\\fontawesome-webfont.ttf";
	out = GetRelativePathToPath(in, rootPath);
	printf("root = %s\n", rootPath.c_str());
	printf("in <= %s\n", in.c_str());
	printf("out => %s\n === %s ===\n\n", out.c_str(), out == "..\\fontawesome-webfont.ttf" ? "OK" : "NOK");

	rootPath = "C:\\gamedev\\github\\ImGuiFontStudio_avp\\projects\\toto";
	in = "C:\\gamedev\\github\\ImGuiFontStudio_avp\\fontawesome-webfont.ttf";
	out = GetRelativePathToPath(in, rootPath);
	printf("root = %s\n", rootPath.c_str());
	printf("in <= %s\n", in.c_str());
	printf("out => %s\n === %s ===\n\n", out.c_str(), out == "..\\..\\fontawesome-webfont.ttf" ? "OK" : "NOK");

	rootPath = "C:\\gamedev\\github\\ImGuiFontStudio_avp\\projects";
	in = "C:\\gamedev\\github\\ImGuiFontStudio_avp\\samples_Fonts\\fontawesome-webfont.ttf";
	out = GetRelativePathToPath(in, rootPath);
	printf("root = %s\n", rootPath.c_str());
	printf("in <= %s\n", in.c_str());
	printf("out => %s\n === %s ===\n\n", out.c_str(), out == "..\\samples_Fonts\\fontawesome-webfont.ttf" ? "OK" : "NOK");

	rootPath = "C:\\gamedev\\github\\ImGuiFontStudio_avp";
	in = "C:\\gamedev\\github\\ImGuiFontStudio_avp\\samples_Fonts\\fontawesome-webfont.ttf";
	out = GetRelativePathToPath(in, rootPath);
	printf("root = %s\n", rootPath.c_str());
	printf("in <= %s\n", in.c_str());
	printf("out => %s\n === %s ===\n\n", out.c_str(), out == "samples_Fonts\\fontawesome-webfont.ttf" ? "OK" : "NOK");

	printf("------------------------------------------------------\n\n");
}
#endif

std::string FileHelper::GetRelativePathToPath(const std::string& vFilePathName, const std::string& vRootPath)
{
	std::string res = vFilePathName;

	// vFilePathName and vRootPath must be absolute paths
	// if not this func will not work
	if (!vFilePathName.empty() && !vRootPath.empty())
	{
		if (IsAbsolutePath(vFilePathName))
		{
			//vRootPath = "C:\\gamedev\\github\\ImGuiFontStudio_avp\\build\\Debug\\..\\..\\projects"
			//vFilePathName = "C:\\gamedev\\github\\ImGuiFontStudio_avp\\samples_Fonts\\fontawesome-webfont.ttf"
			auto rootArr = ct::splitStringToVector(CorrectFilePathName(vRootPath), m_SlashType);
			auto inArr = ct::splitStringToVector(CorrectFilePathName(vFilePathName), m_SlashType);
			if (!inArr.empty() && !rootArr.empty())
			{
				std::vector<std::string> outArr;
				size_t ro = 0, in = 0;
				while (ro < rootArr.size() || in < inArr.size())
				{
					if (ro < rootArr.size() && in < inArr.size())
					{
						if (rootArr[ro] != inArr[in])
						{
							outArr.emplace_back("..");
							ro++;
						}
						else
						{
							ro++;
							in++;
						}
					}
					else if (ro < rootArr.size()) // rootArr > inArr
					{
						outArr.emplace_back("..");
						ro++;
					}
					else if (in < inArr.size()) // rootArr < inArr
					{
						outArr.emplace_back(inArr[in]);
						in++;
					}
				}

				// assemble path
				res.clear();
				for (auto &it : outArr)
				{
					if (!res.empty())
						res += m_SlashType;
					res += it;
				}
			}
		}
#ifdef _DEBUG
		else
		{
			printf("Path %s is relative !?\n", res.c_str());
		}
#endif
	}

	return res;
}

bool FileHelper::IsAbsolutePath(const std::string& vFilePathName)
{
#ifdef WIN32
	// on window an absolute path can be like "C:\\" (disk) or "\\" (network)
	if ((vFilePathName.size() > 3 &&
		vFilePathName[1] == ':' &&
		vFilePathName[2] == m_SlashType[0]) ||
		vFilePathName[0] == m_SlashType[0])
#elif defined(UNIX)
	if (vFilePathName[0] == m_SlashType[0]) // absolute path for linux / apple
#endif

	{
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(APPLE)
static std::string GetMacOsAppPath()
{
    Dl_info module_info;
    if (dladdr((void*)GetMacOsAppPath, &module_info))
    {
        return std::string(module_info.dli_fname);
    }

    return "";
}
#endif

void FileHelper::SetAppPath(const std::string& vPath)
{
    if (vPath.size() > 0)
    {
        std::string::size_type pos = vPath.find_last_of("\\/");
        if (pos != std::string::npos)
        {
            FileHelper::AppPath = vPath.substr(0, pos);
        }
    }
}

std::string FileHelper::GetPathRelativeToApp(const std::string& vFilePathName)
{
	return GetRelativePathToPath(vFilePathName, GetAppPath());
}

std::string FileHelper::GetAppPath()
{
	if (FileHelper::AppPath.empty())
	{
        char buffer[MAX_PATH] = {};
#ifdef WIN32
        GetModuleFileName(NULL, buffer, MAX_PATH);
#elif defined(LINUX)
        char szTmp[32];
        sprintf(szTmp, "/proc/%d/exe", getpid());
        int bytes = ct::mini<int>(readlink(szTmp, buffer, MAX_PATH), MAX_PATH - 1);
        if(bytes >= 0)
            buffer[bytes] = '\0';
#elif defined(APPLE)
		std::string path = GetMacOsAppPath();
        std::string::size_type pos = path.find_last_of("\\/");
		FileHelper::AppPath = path.substr(0, pos);
#endif
#if defined(WIN32) || defined(LINUX)
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		FileHelper::AppPath = std::string(buffer).substr(0, pos);
#endif
	}
	
	return FileHelper::AppPath;
}

std::string FileHelper::GetCurDirectory()
{
	char cCurrentPath[FILENAME_MAX];
	if (GetCurrentDir(cCurrentPath, FILENAME_MAX))
	{
		return std::string(cCurrentPath) + m_SlashType;
	}
	return "";
}

bool FileHelper::SetCurDirectory(const std::string& vPath)
{
    return SetCurrentDir(vPath.c_str()) == 0;
}

std::string FileHelper::ComposePath(const std::string& vPath, const std::string& vFileName, const std::string& vExt)
{
	std::string res = vPath;
	if (!vFileName.empty())
	{
		if (!vPath.empty()) res += m_SlashType;
		res += vFileName;
		if (!vExt.empty()) res += "." + vExt;
	}
	return res;
}

bool FileHelper::IsFileExist(const std::string& name)
{
    std::string fileToOpen = name;
	fileToOpen = CorrectFilePathName(fileToOpen);
    ct::replaceString(fileToOpen, "\"", "");
    ct::replaceString(fileToOpen, "\n", "");
    ct::replaceString(fileToOpen, "\r", "");

	std::ifstream docFile(fileToOpen, std::ios::in);
	if (docFile.is_open())
	{
		docFile.close();
		return true;
	}
	else
    {
	    printf("fail to found file %s\n", name.c_str());
    }

	return false;
}

bool FileHelper::IsDirectoryExist(const std::string& name)
{
    bool bExists = false;

    if (name.size() > 0)
    {
		std::string dir = CorrectFilePathName(name);
		struct stat sb;
		if (stat(dir.c_str(), &sb))
			bExists = (sb.st_mode & S_IFDIR);
    }

	return bExists;    // this is not a directory!
}

void FileHelper::DestroyFile(const std::string& vFilePathName)
{
	if (vFilePathName.size() > 0)
	{
		auto filePathName = CorrectFilePathName(vFilePathName);
		if (IsFileExist(filePathName))
		{
			if (remove(filePathName.c_str()))
			{
				printf("%s Cant be deleted !\n", vFilePathName.c_str());
			}
		}
	}
}

bool FileHelper::CreateDirectoryIfNotExist(const std::string& name)
{
    bool res = false;

    if (name.size() > 0)
    {
		auto filePathName = CorrectFilePathName(name);
		if (!IsDirectoryExist(filePathName))
        {
            res = true;

#ifdef WIN32
            CreateDirectory(filePathName.c_str(), NULL);
#elif defined(UNIX)
            char buffer[MAX_PATH] = {};
            snprintf(buffer, MAX_PATH, "mkdir -p %s", filePathName.c_str());
            const int dir_err = std::system(buffer);
            if (dir_err == -1)
            {
                LogStr("Error creating directory " + filePathName);
                res = false;
            }
#endif
        }
    }

    return res;
}

bool FileHelper::CreatePathIfNotExist(const std::string& vPath)
{
    bool res = false;

    if (vPath.size() > 0)
	{
		auto path = CorrectFilePathName(vPath);
		if (!IsDirectoryExist(path))
		{
		    res = true;

			ct::replaceString(path, "/", "|");
			ct::replaceString(path, "\\", "|");
			auto arr = ct::splitStringToVector(path, "|");
			std::string fullPath;
			for (auto it = arr.begin(); it != arr.end(); ++it)
			{
				fullPath += *it;

				res &= CreateDirectoryIfNotExist(fullPath);

				// si sur windows
				fullPath += m_SlashType;
			}
		}
	}

    return res;
}

std::string FileHelper::SimplifyFilePath(const std::string& vFilePath)
{
	std::string newPath = CorrectFilePathName(vFilePath);

	// the idea is to simplify a path where there is some ..
	// by ex : script\\kifs\\../space3d.glsl => can be simplified in /script/space3d.glsl

	size_t dpt = 0;
	while((dpt = newPath.find("..")) != std::string::npos)
	{
		ct::replaceString(newPath, "\\", m_SlashType);
		ct::replaceString(newPath, "/", m_SlashType);

		size_t sl = newPath.rfind(m_SlashType, dpt);
		if (sl != std::string::npos)
		{
			if (sl > 0)
			{
				sl = newPath.rfind(m_SlashType, sl - 1);
				if (sl != std::string::npos)
				{
					std::string str = newPath.substr(sl, dpt + 2 - sl);
					ct::replaceString(newPath, str, "");
				}
				else
				{

				}
			}
		}
	}

	return newPath;
}

std::string FileHelper::GetID(const std::string& vPathFileName)
{
	auto pathFileName = CorrectFilePathName(vPathFileName);
	return "";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void FileHelper::OpenFile(const std::string&vShaderToOpen)
{
	auto shaderToOpen = CorrectFilePathName(vShaderToOpen);

#if defined(WIN32)
	auto result = ShellExecute(0, "", shaderToOpen.c_str(), 0, 0, SW_SHOW);
	if (result < (HINSTANCE)32)
	{
		// try to open an editor
		result = ShellExecute(0, "edit", shaderToOpen.c_str(), 0, 0, SW_SHOW);
		if (result == (HINSTANCE)SE_ERR_ASSOCINCOMPLETE || result == (HINSTANCE)SE_ERR_NOASSOC)
		{
			// open associating dialog
			std::string sCmdOpenWith = "shell32.dll,OpenAs_RunDLL \"" + shaderToOpen + "\"";
			result = ShellExecute(0, "", "rundll32.exe", sCmdOpenWith.c_str(), NULL, SW_NORMAL);
		}
		if (result < (HINSTANCE)32) // open in explorer
		{
			std::string sCmdExplorer = "/select,\"" + shaderToOpen + "\"";
			ShellExecute(0, "", "explorer.exe", sCmdExplorer.c_str(), NULL, SW_NORMAL); // ce serait peut etre mieu d'utilsier la commande system comme dans SelectFile
		}
	}
#elif defined(LINUX)
	int pid = fork();
    if (pid == 0)
    {
        execl("/usr/bin/xdg-open", "xdg-open", shaderToOpen.c_str(), (char *)0);
    }
#elif defined(APPLE)
    //string command = "open -a Tincta " + vShaderToOpen;
    string command = "open " + shaderToOpen;
    std::system(command.c_str());
#endif
}

void FileHelper::OpenUrl(const std::string& vUrl)
{
	auto url = CorrectFilePathName(vUrl);

#ifdef WIN32
	ShellExecute(0, 0, url.c_str(), 0, 0, SW_SHOW);
#elif defined(LINUX)
	char buffer[MAX_PATH] = {};
	snprintf(buffer, MAX_PATH, "<mybrowser> %s", url.c_str());
    std::system(buffer);
#elif defined(APPLE)
    //std::string sCmdOpenWith = "open -a Firefox " + vUrl;
    std::string sCmdOpenWith = "open " + url;
    std::system(sCmdOpenWith.c_str());
#endif
}

void FileHelper::SelectFile(const std::string& vFileToSelect)
{
	auto fileToSelect = CorrectFilePathName(vFileToSelect);

#ifdef WIN32
	if (fileToSelect.size() > 0)
	{
		std::string sCmdOpenWith = "explorer /select," + fileToSelect;
		std::system(sCmdOpenWith.c_str());
	}

	/*int result = (int)ShellExecute(0, "", vShaderToOpen.c_str(), 0, 0, SW_SHOW);
	if (result < 32)
	{
		// try to open an editor
		result = (int)ShellExecute(0, "edit", vShaderToOpen.c_str(), 0, 0, SW_SHOW);
		if (result == SE_ERR_ASSOCINCOMPLETE || result == SE_ERR_NOASSOC)
		{
			// open associating dialog
			std::string sCmdOpenWith = "shell32.dll,OpenAs_RunDLL \"" + vShaderToOpen + "\"";
			result = (int)ShellExecute(0, "", "rundll32.exe", sCmdOpenWith.c_str(), NULL, SW_NORMAL);
		}
		if (result < 32) // open in explorer
		{
			std::string sCmdExplorer = "/select,\"" + vShaderToOpen + "\"";
			ShellExecute(0, "", "explorer.exe", sCmdExplorer.c_str(), NULL, SW_NORMAL);
		}
	}*/

#elif defined(LINUX)
	// is there a similar command on linux ?
#elif defined(APPLE)
    if (fileToSelect.size() > 0)
    {
        std::string sCmdOpenWith = "open -R " + fileToSelect;
        std::system(sCmdOpenWith.c_str());
    }
#endif
}

std::vector<std::string> FileHelper::GetDrives()
{
	std::vector<std::string> res;

#ifdef WIN32
	DWORD mydrives = 2048;
	char lpBuffer[2048];

	DWORD countChars = GetLogicalDriveStrings(mydrives, lpBuffer);

	if (countChars > 0)
	{
		std::string var = std::string(lpBuffer, countChars);
		ct::replaceString(var, "\\", "");
		res = ct::splitStringToVector(var, "\0");
	}
#endif

	return res;
}

std::string FileHelper::getTimeStampToString(const std::string& vSeparator)
{
	std::string res;

	auto now = std::chrono::system_clock::now();
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
#ifdef MSVC
	struct tm *parts = 0;
	errno_t err = localtime_s(parts, &now_c);
	if (!err && parts)
#else
	struct tm *parts = std::localtime(&now_c);
	if (parts)
#endif
	{
		float time_seconds = (float)(parts->tm_hour * 3600 + parts->tm_min * 60 + parts->tm_sec + (float)(ms.count() % 1000) / 1000.0f);

		float year = ct::fract((float)(1900 + parts->tm_year) / 100.0f) * 100.0f;
		float month = (float)(1 + parts->tm_mon);
		float day = (float)(parts->tm_mday);
		float seconds = time_seconds;

		res = ct::toStr(year) + vSeparator + ct::toStr(month) + vSeparator + ct::toStr(day) + vSeparator + ct::toStr(seconds);
	}
	return res;
}

size_t FileHelper::getTimeStampToNumber()
{
	size_t timeStamp = 0;

	auto now = std::chrono::system_clock::now();
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
#ifdef MSVC
	struct tm *parts = 0;
	errno_t err = localtime_s(parts, &now_c);
	if (!err && parts)
#else
	struct tm *parts = std::localtime(&now_c);
	if (parts)
#endif
	{
		int year = 1900 + parts->tm_year - 2000;
		int month = 1 + parts->tm_mon;
		int day = parts->tm_mday;
		int seconds = parts->tm_hour * 3600 + parts->tm_min * 60 + parts->tm_sec;

		std::string res = ct::toStr(year) + ct::toStr(month) + ct::toStr(day) + ct::toStr(seconds);

		timeStamp = ct::uvariant(res).getU();
	}
	return timeStamp;
}

// Need GLFW

void FileHelper::SaveInClipBoard(GLFWwindow *vWin, const std::string& vString)
{
	if (vString.size() > 0)
	{
		glfwSetClipboardString(vWin, vString.c_str());
	}
}

std::string FileHelper::GetFromClipBoard(GLFWwindow *vWin)
{
	std::string res = glfwGetClipboardString(vWin);
	return res;
}

std::vector<std::string> FileHelper::GetAbsolutePathForFileLocation(const std::vector<std::string>& vRelativeFilePathNames, FileLocation vFileType)
{
	std::vector<std::string> res;

	for (auto &it : vRelativeFilePathNames)
	{

		res.emplace_back(GetAbsolutePathForFileLocation(it, vFileType));
	}

	return res;
}

std::string FileHelper::GetAbsolutePathForFileLocation(const std::string& vRelativeFilePathName, FileLocation vFileType)
{
	std::string registeredPath = m_RegisteredPaths[vFileType];
	if (vRelativeFilePathName.find(registeredPath) != std::string::npos) // deja un chemin absolu
	{
		return vRelativeFilePathName;
	}

	return registeredPath + m_SlashType + vRelativeFilePathName;
}

std::string FileHelper::LoadFile(const std::string& vFilePathName, FileLocation vFileType)
{
	std::string file;
	std::string filePathName;

	filePathName = GetAbsolutePathForFileLocation(vFilePathName, vFileType);

	std::ifstream docFile(filePathName, std::ios::in);
	if (docFile.is_open())
	{
		std::stringstream strStream;
		strStream << docFile.rdbuf();//read the file

		file = strStream.str();
        ct::replaceString(file, "\r\n", "\n");

        docFile.close();
	}

	return file;
}

void FileHelper::SaveToFile(const std::string& vCode, const std::string& vFilePathName, FileLocation vFileType)
{
	std::string filePathName;

	filePathName = GetAbsolutePathForFileLocation(vFilePathName, vFileType);

	std::ofstream fileWriter(filePathName, std::ios::out);
	if (fileWriter.bad() == false)
	{
		fileWriter << vCode;
		fileWriter.close();
	}
}

//////////////////////////////////////////////////////////////
/////////////// SPECIFIC FUNCTION ////////////////////////////
//////////////////////////////////////////////////////////////

std::string FileHelper::GetRelativePathToParent(const std::string& vFilePath, const std::string& vParentPath)
{
	std::string newPath = vFilePath;

	if (IsFileExist(newPath))
	{

	}
	else
	{
		newPath = vParentPath + FileHelper::Instance()->m_SlashType + vFilePath;

		if (IsFileExist(newPath))
		{

		}
		else
		{
			std::string incPath = "";
			newPath = incPath + FileHelper::Instance()->m_SlashType + vFilePath;

			if (IsFileExist(newPath))
			{

			}
			else
			{
				// error
				printf("File %s Not Found !\n", newPath.c_str());

				newPath.clear();
			}
		}
	}

	return newPath;
}