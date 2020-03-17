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

#include <Logger.h>
#include <string>
#include <map>
#include <tinyxml2/tinyxml2.h>

namespace conf
{
	class ConfigAbstract
	{
	public:
		virtual std::string getXml(const std::string& vOffset) = 0;
		virtual void setFromXml(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent) = 0;

	public:
		bool LoadConfigFile(const std::string& vFilePathName)
		{
			bool res = false;

			ifstream docFile(vFilePathName, ios::in);
			if (docFile.is_open())
			{
				stringstream strStream;

				strStream << docFile.rdbuf();//read the file

				res = parseConfigDatas(strStream.str());

				docFile.close();
			}

			return res;
		}

		bool SaveConfigFile(const std::string& vFilePathName)
		{
			bool res = false;

			std::string fileStream;

			fileStream += "<config>\n";

			fileStream += getXml("\t");

			fileStream += "</config>\n";

			std::ofstream configFileWriter(vFilePathName, std::ios::out);
			if (configFileWriter.bad() == false)
			{
				configFileWriter << fileStream;
				configFileWriter.close();
				res = true;
			}

			return res;
		}

		bool parseConfigDatas(const std::string& vDatas)
		{
			bool res = false;

			try
			{
				std::string data = vDatas;
				ct::replaceString(data, "\r\n", "\n");

				tinyxml2::XMLDocument doc;
				tinyxml2::XMLError err = doc.Parse(data.c_str(), vDatas.size());

				if (err == tinyxml2::XMLError::XML_SUCCESS)
				{
					res = true;
					res = res && RecursParsingConfig(doc.FirstChildElement("config"), 0);
				}
			}
			catch (std::exception& ex)
			{
				LogStr("parse error => " + string(ex.what()));
			}

			return res;
		}

		bool RecursParsingConfig(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent)
		{
			bool res = false;

			setFromXml(vElem, vParent);

			res = true;

			// CHILDS 
			// parse through all childs elements
			for (tinyxml2::XMLElement* child = vElem->FirstChildElement(); child != 0; child = child->NextSiblingElement())
			{
				res = res && RecursParsingConfig(child->ToElement(), vElem);
			}

			return res;
		}
	};
}

