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

#include <ctools/ConfigAbstract.h>

namespace conf {

// replace patterns (who can break a xml code) by corresponding escaped pattern
std::string ConfigAbstract::escapeXmlCode(std::string vDatas) {
    // escape some patterns
    // https://stackoverflow.com/questions/1091945/what-characters-do-i-need-to-escape-in-xml-documents/46637835#46637835
    m_replaceString(vDatas, "&", "&amp;");  // do that in first :) else it will modify the others code who are starting by &
    m_replaceString(vDatas, "<", "&lt;");
    m_replaceString(vDatas, "\"", "&quot;");
    m_replaceString(vDatas, "'", "&apos;");
    m_replaceString(vDatas, ">", "&gt;");
    return vDatas;
}

// replace xml excaped pattern by corresponding good pattern
std::string ConfigAbstract::unEscapeXmlCode(std::string vDatas) {
    // unescape some patterns
    // https://stackoverflow.com/questions/1091945/what-characters-do-i-need-to-escape-in-xml-documents/46637835#46637835
    m_replaceString(vDatas, "&lt;", "<");
    m_replaceString(vDatas, "&amp;", "&");
    m_replaceString(vDatas, "&quot;", "\"");
    m_replaceString(vDatas, "&apos;", "'");
    m_replaceString(vDatas, "&gt;", ">");
    return vDatas;
}

tinyxml2::XMLError ConfigAbstract::LoadConfigString(const std::string& vConfigString, const std::string& vUserDatas, const std::string& vFirstElement) {
    return parseConfigDatas(vConfigString, vUserDatas, vFirstElement);
}

std::string ConfigAbstract::SaveConfigString(const std::string& vUserDatas, const std::string& vFirstElement) {
    return "<" + vFirstElement + ">\n" + getXml("\t", vUserDatas) + "</" + vFirstElement + ">\n";
}

tinyxml2::XMLError ConfigAbstract::LoadConfigFile(const std::string& vFilePathName, const std::string& vUserDatas, const std::string& vFirstElement) {
    tinyxml2::XMLError res = tinyxml2::XMLError::XML_CAN_NOT_CONVERT_TEXT;

    std::ifstream docFile(vFilePathName, std::ios::in);
    if (docFile.is_open()) {
        std::stringstream strStream;

        strStream << docFile.rdbuf();  // read the file

        res = LoadConfigString(strStream.str(), vUserDatas, vFirstElement);

        docFile.close();
    } else {
        res = tinyxml2::XMLError::XML_ERROR_FILE_COULD_NOT_BE_OPENED;
    }

    return res;
}

bool ConfigAbstract::SaveConfigFile(const std::string& vFilePathName, const std::string& vUserDatas) {
    bool res = false;

    std::string data = SaveConfigString(vUserDatas);
    std::ofstream configFileWriter(vFilePathName, std::ios::out);
    if (!configFileWriter.bad()) {
        configFileWriter << data;
        configFileWriter.close();
        res = true;
    }

    return res;
}

tinyxml2::XMLError ConfigAbstract::parseConfigDatas(std::string vDatas, const std::string& vUserDatas, const std::string& vFirstElement) {
    tinyxml2::XMLError res = tinyxml2::XMLError::XML_CAN_NOT_CONVERT_TEXT;

    try {
        m_replaceString(vDatas, "\r\n", "\n");

        tinyxml2::XMLDocument doc;
        res = doc.Parse(vDatas.c_str(), vDatas.size());

        if (res == tinyxml2::XMLError::XML_SUCCESS) {
            RecursParsingConfig(doc.FirstChildElement(vFirstElement.c_str()), 0, vUserDatas);
        } else {
            doc.PrintError();
        }
    } catch (std::exception& ex) {
        printf("error during XML Parsing => %s", std::string(ex.what()).c_str());
    }

    return res;
}

void ConfigAbstract::RecursParsingConfig(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent, const std::string& vUserDatas) {
    if (setFromXml(vElem, vParent, vUserDatas)) {
        RecursParsingConfigChilds(vElem, vUserDatas);
    }
}

void ConfigAbstract::RecursParsingConfigChilds(tinyxml2::XMLElement* vElem, const std::string& vUserDatas) {
    // CHILDS
    // parse through all childs elements
    for (tinyxml2::XMLElement* child = vElem->FirstChildElement(); child != 0; child = child->NextSiblingElement()) {
        RecursParsingConfig(child->ToElement(), vElem, vUserDatas);
    }
}

std::string ConfigAbstract::getTinyXml2ErrorMessage(tinyxml2::XMLError vErrorCode) {
    tinyxml2::XMLDocument doc;
    return std::string(doc.ErrorIDToName(vErrorCode));
}

bool ConfigAbstract::m_replaceString(::std::string& str, const ::std::string& oldStr, const ::std::string& newStr) {
    bool found = false;
    size_t pos = 0;
    while ((pos = str.find(oldStr, pos)) != ::std::string::npos) {
        found = true;
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
    return found;
}

}  // namespace conf
