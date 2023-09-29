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

#include <string>
#include <vector>
#include <map>
#include <memory>

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

struct CTOOLS_API PathStruct
{
	std::string path;
	std::string name;
	std::string ext;

	bool isOk = false;

	PathStruct();
	PathStruct(const std::string& vPath, const std::string& vName, const std::string& vExt);

	// FPNE mean FilePathNameExt
	std::string GetFPNE();
	std::string GetFPNE_WithPathNameExt(std::string vPath, const std::string& vName, const std::string& vExt);
	std::string GetFPNE_WithPath(const std::string& vPath);
	std::string GetFPNE_WithPathName(const std::string& vPath, const std::string& vName);
	std::string GetFPNE_WithPathExt(const std::string& vPath, const std::string& vExt);
	std::string GetFPNE_WithName(const std::string& vName);
	std::string GetFPNE_WithNameExt(const std::string& vName, const std::string& vExt);
	std::string GetFPNE_WithExt(const std::string& vExt);
};

typedef int FileLocation;

#ifdef USE_GLFW3
struct GLFWwindow;
#endif
class CTOOLS_API FileHelper
{
public: // static
	static std::string AppPath;

private:
	std::map<FileLocation, std::string> puRegisteredPaths;

public: // var
	std::string puSlashType;
	std::string puAppFileName;
	std::vector<std::string> puSearchPaths;

public: // funcs
	PathStruct ParsePathFileName(const std::string& vPathFileName) const;

	void RegisterPath(FileLocation vLoc, const std::string& vPath);
	std::string GetRegisteredPath(FileLocation vLoc) const;

	std::string GetExistingFilePathForFile(const std::string& vFileName, bool vSilentMode = false);
	std::string CorrectSlashTypeForFilePathName(const std::string& vFilePathName) const;
#ifdef _DEBUG
	void Test_GetRelativePathToPath();
#endif
    std::string GetAppRelativeFilePathName(const std::string& vFilePathName);
	std::string GetRelativePathToPath(const std::string& vFilePathName, const std::string& vRootPath);
	bool IsAbsolutePath(const std::string& vFilePathName);

	void SetAppPath(const std::string& vPath);
	std::string GetAppPath();
	std::string GetPathRelativeToApp(const std::string& vFilePathName);

	std::string GetCurDirectory() const;
	bool SetCurDirectory(const std::string& vPath) const;

	std::string ComposePath(const std::string& vPath, const std::string& vFileName, const std::string& vExt) const;

	bool IsFileExist(const std::string& name, bool vSilentMode = false) const;
	std::string GetID(const std::string& vPathFileName) const;

	std::string SimplifyFilePath(const std::string& vFilePath) const;

	std::string LoadFileToString(const std::string& vFilePathName, bool vSilentMode = false);
	void SaveStringToFile(const std::string& vString, const std::string& vFilePathName);

	std::vector<uint8_t> LoadFileToBytes(const std::string& vFilePathName, int* vError = nullptr);

	void DestroyFile(const std::string& filePathName) const;

	bool IsDirectoryExist(const std::string& name) const;
	bool CreateDirectoryIfNotExist(const std::string& name) const;
	bool CreatePathIfNotExist(const std::string& vPath) const;

	void OpenFile(const std::string& vShaderToOpen) const;
	void OpenUrl(const std::string& vUrl) const;
	void SelectFile(const std::string& vFileToSelect) const;

	std::vector<std::string> GetDrives() const;

	std::string GetTimeStampToString(const std::string& vSeparator = "_") const;
	size_t GetTimeStampToNumber() const;

	std::vector<std::string> GetAbsolutePathForFileLocation(const std::vector<std::string>& vRelativeFilePathNames, FileLocation vFileType = (FileLocation)0);
	std::string GetAbsolutePathForFileLocation(const std::string& vRelativeFilePathName, FileLocation vFileType = (FileLocation)0);

	std::string LoadFile(const std::string& vFilePathName, FileLocation vFileType = (FileLocation)0);
	void SaveToFile(const std::string& vCode, const std::string& vFilePathName, FileLocation vFileType = (FileLocation)0);

	// specific function
	std::string GetRelativePathToParent(const std::string& vFilePath, const std::string& vParentPath, bool vSilentMode = false) const;

#ifdef USE_GLFW3
public: /* clipboard */
	void SaveInClipBoard(GLFWwindow* vWin, const std::string& vString);
	std::string GetFromClipBoard(GLFWwindow* vWin);
#endif

public: // singleton
	static FileHelper* Instance(FileHelper* vCopy = nullptr, bool vForce = false)
	{
		static FileHelper _instance;
		static FileHelper* _instance_copy = nullptr;
		if (vCopy || vForce)
			_instance_copy = vCopy;
		if (_instance_copy)
			return _instance_copy;
		return &_instance;
	}

public:
	FileHelper(); // Prevent construction
	FileHelper(const FileHelper&) {}; // Prevent construction by copying
	FileHelper& operator =(const FileHelper&) { return *this; }; // Prevent assignment
	~FileHelper(); // Prevent unwanted destruction
};
