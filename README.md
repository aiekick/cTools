# cTools

a two files helper im using from more than 10 years, in all my project.

Contain usefull templated things for c++ like vec2, vec3, vec4, variant, actionTime and more.

need a bit of refactoring btw :)

use the namespace ct

## Class's in cTools :

- ct::cCyclicArray => circular list
- ct::cActionTime => define when to do action according to time of last event
- ct::cTexture => opengl texture simple container
- ct::cColor => color class for conversion
- ct::vec2<T> => vec2 class for quick operation / math x,y
- ct::mat2<T> => mat2 class for matrix 2x2
- ct::vec3<T> => vec3 class for quick operation / math x,y,z
- ct::vec4<T> => vec4 class for quick operation / math x,y,z,w
- ct::rect<T> => rect class for quick operation / math x,y,w,h
- ct::AABB<T> => AABB 2D
- ct::AABBCC<T> => AABBCC 3D
- ct::variant<T> => variant class for quick conversion between many types and string

and other string conversion / extraction etc..

## Method's in Logger :

Log method for check/write in auto in a log file

- LogStr(n)
- LogValue(s, n)
- LogGlError()
- LogGlErrorVar(var)
- LogAssert(a,b)

## ConfigAbstract

ConfigAbstract let you load/save a config file easily from class 

using lib [tinyxml2](https://github.com/leethomason/tinyxml2)

Usage :
```cpp
class toto : public conf::ConfigAbstract
{
public:
	toto()
	{
		LoadConfigFile("config.xml");
	}

	~toto()
	{
		SaveConfigFile("config.xml");
	}

	std::string getXml(const std::string& vOffset);
	void setFromXml(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent);
};


std::string toto::getXml(const std::string& vOffset)
{
	std::string str;

	str += vOffset + "\t<tata value=\"" + "true" + "\"/>\n";
	
	return str;
}

void toto::setFromXml(tinyxml2::XMLElement* vElem, tinyxml2::XMLElement* vParent)
{
	// The value of this child identifies the name of this element
	std::string strName = "";
	std::string strValue = "";
	std::string strParentName = "";

	strName = vElem->Value();
	if (vElem->GetText())
		strValue = vElem->GetText();
	if (vParent != 0)
		strParentName = vParent->Value();

	auto att = vElem->FirstAttribute();
	if (att && std::string(att->Name()) == "value")
	{
		strValue = att->Value();
		if (strName == "tata")
			youvar = strValue;
	}
}
```
