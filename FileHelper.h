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

#include <string>
#include <vector>

struct PathStruct
{
	std::string path;
	std::string name;
	std::string ext;

	bool isOk = false;

	PathStruct()
	{
		isOk = false;
	}
};

struct GLFWwindow;
class FileHelper
{
public: // static
	static std::string AppPath;

public: // var
	std::string m_SlashType;
	std::string m_AppFileName;
	std::vector<std::string> m_SearchPaths;

public: // funcs
	std::string GetExistingFilePathForFile(const std::string& vFileName);
	
#ifdef _DEBUG
	void Test_GetRelativePathToPath();
#endif
	std::string GetRelativePathToPath(const std::string& vFilePathName, const std::string& vRootPath);
	bool IsAbsolutePath(const std::string& vFilePathName);
	
	void SetAppPath(std::string vPath);
    std::string GetAppPath();
	std::string GetCurDirectory();
    bool SetCurDirectory(std::string vPath);

	bool IsFileExist(const std::string& name);
	std::string GetID(const std::string& vPathFileName);

	std::string SimplifyFilePath(const std::string& vFilePath);

	std::string LoadFileToString(const std::string& vFilePathName);
	void SaveStringToFile(const std::string& vString, const std::string& vFilePathName);

	PathStruct ParsePathFileName(const std::string& vPathFileName);

	void DestroyFile(const std::string& filePathName);

	bool IsDirectoryExist(const std::string& name);
    bool CreateDirectoryIfNotExist(const std::string& name);
    bool CreatePathIfNotExist(const std::string& vPath);

	void OpenFile(std::string vShaderToOpen);
	void OpenUrl(std::string vUrl);
	void SelectFile(std::string vFileToSelect);

	std::vector<std::string> GetDrives();

	std::string getTimeStampToString(std::string vSeparator = "_");
	size_t getTimeStampToNumber();

public: /* clipboard */
	void SaveInClipBoard(GLFWwindow *vWin, std::string vString);
	std::string GetFromClipBoard(GLFWwindow *vWin);

public: // singleton
	static FileHelper *Instance()
	{
		static FileHelper *_instance = new FileHelper();
		return _instance;
	}

protected:
	FileHelper(); // Prevent construction
	FileHelper(const FileHelper&) {}; // Prevent construction by copying
	FileHelper& operator =(const FileHelper&) { return *this; }; // Prevent assignment
	~FileHelper(); // Prevent unwanted destruction
};
