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

#include <tinyxml2.h>

#include <fstream> // ifstream
#include <sstream> // stringstream
#include <string>
#include <map>

namespace conf
{
	class CTOOLS_API ConfigAbstract
	{
	public:
		virtual std::string getXml(const std::string& vOffset, const std::string& vUserDatas = "") = 0;
		// return true for continue xml parsing of childs in this node or false for interrupt the child exploration (if we want explore child ourselves)
		virtual bool setFromXml(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent, const std::string& vUserDatas = "") = 0;

	public:
		// replace patterns (who can break a xml code) by corresponding escaped pattern
        std::string escapeXmlCode(std::string vDatas);

		// replace xml excaped pattern by corresponding good pattern
        std::string unEscapeXmlCode(std::string vDatas);

		tinyxml2::XMLError LoadConfigString(const std::string& vConfigString, const std::string& vUserDatas = "", const std::string& vFirstElement = "config");

		std::string SaveConfigString(const std::string& vUserDatas = "", const std::string& vFirstElement = "config");

		tinyxml2::XMLError LoadConfigFile(const std::string& vFilePathName, const std::string& vUserDatas = "", const std::string& vFirstElement = "config");

		bool SaveConfigFile(const std::string& vFilePathName, const std::string& vUserDatas = "");

		tinyxml2::XMLError parseConfigDatas(std::string vDatas, const std::string& vUserDatas = "", const std::string& vFirstElement = "config");

		void RecursParsingConfig(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent, const std::string& vUserDatas = "");

		void RecursParsingConfigChilds(tinyxml2::XMLElement* vElem, const std::string& vUserDatas = "");

		std::string getTinyXml2ErrorMessage(tinyxml2::XMLError vErrorCode);

	private:
        bool m_replaceString(::std::string& str, const ::std::string& oldStr, const ::std::string& newStr);
	};
}
