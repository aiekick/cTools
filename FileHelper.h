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
#include <map>

struct PathStruct
{
	std::string path;
	std::string name;
	std::string ext;

	bool isOk = false;

	PathStruct();
	std::string GetFilePathWithNameExt(const std::string& vName, const std::string& vExt);
};

typedef int FileLocation;

struct GLFWwindow;
class FileHelper
{
public: // static
	static std::string AppPath;

public: // var
	std::map<FileLocation, std::string> m_RegisteredPaths;
	std::string m_SlashType;
	std::string m_AppFileName;
	std::vector<std::string> m_SearchPaths;

public: // funcs
	void RegisterPath(FileLocation vLoc, const std::string& vPath);

	std::string GetExistingFilePathForFile(const std::string& vFileName);
	std::string CorrectFilePathName(const std::string &vFilePathName);
#ifdef _DEBUG
	void Test_GetRelativePathToPath();
#endif
	std::string GetRelativePathToPath(const std::string& vFilePathName, const std::string& vRootPath);
	bool IsAbsolutePath(const std::string& vFilePathName);
	
	void SetAppPath(const std::string& vPath);
    std::string GetAppPath();
	std::string GetPathRelativeToApp(const std::string& vFilePathName);
	
	std::string GetCurDirectory();
    bool SetCurDirectory(const std::string& vPath);

	std::string ComposePath(const std::string& vPath, const std::string& vFileName, const std::string& vExt);

	bool IsFileExist(const std::string& name);
	std::string GetID(const std::string& vPathFileName);

	std::string SimplifyFilePath(const std::string& vFilePath);

	std::string LoadFileToString(const std::string& vFilePathName);
	void SaveStringToFile(const std::string& vString, const std::string& vFilePathName);

	std::vector<uint8_t> LoadFileToBytes(const std::string& vFilePathName, int *vError = 0);
	PathStruct ParsePathFileName(const std::string& vPathFileName);

	void DestroyFile(const std::string& filePathName);

	bool IsDirectoryExist(const std::string& name);
    bool CreateDirectoryIfNotExist(const std::string& name);
    bool CreatePathIfNotExist(const std::string& vPath);

	void OpenFile(const std::string& vShaderToOpen);
	void OpenUrl(const std::string& vUrl);
	void SelectFile(const std::string& vFileToSelect);

	std::vector<std::string> GetDrives();

	std::string GetTimeStampToString(const std::string& vSeparator = "_");
	size_t GetTimeStampToNumber();

	std::vector<std::string> GetAbsolutePathForFileLocation(const std::vector<std::string>& vRelativeFilePathNames, FileLocation vFileType);
	std::string GetAbsolutePathForFileLocation(const std::string& vRelativeFilePathName, FileLocation vFileType);
	
	std::string LoadFile(const std::string& vFilePathName, FileLocation vFileType);
	void SaveToFile(const std::string& vCode, const std::string& vFilePathName, FileLocation vFileType);

	// specific function
	std::string GetRelativePathToParent(const std::string& vFilePath, const std::string& vParentPath);

public: /* clipboard */
	void SaveInClipBoard(GLFWwindow *vWin, const std::string& vString);
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
