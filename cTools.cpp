// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "cTools.h"

#ifdef WIN32
#include <Windows.h>
#elif defined(LINUX) or defined(APPLE)
#endif

#include <stdarg.h>  // For va_start, etc.

#include <sstream>
#include <cmath>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <functional>
#include <algorithm> // ::std::reverse

::std::list<::std::string> ct::splitStringToList(const ::std::string& text, char delimiter, bool pushEmpty, bool vInversion)
{
	::std::list<::std::string> arr;
	if (text.size() > 0)
	{
		::std::string::size_type start = 0;
		::std::string::size_type end = text.find(delimiter, start);
		while (end != ::std::string::npos)
		{
			::std::string token = text.substr(start, end - start);
			if (token.size() > 0 || (token.empty() && pushEmpty))
				if (vInversion)
					arr.push_front(token);
				else
					arr.push_back(token);
			start = end + 1;
			end = text.find(delimiter, start);
		}
		if (vInversion)
			arr.push_front(text.substr(start));
		else
			arr.push_back(text.substr(start));
	}
	return arr;
}

::std::vector<::std::string> ct::splitStringToVector(const ::std::string& text, char delimiter, bool pushEmpty)
{
	::std::vector<::std::string> arr;
	if (text.size() > 0)
	{
		::std::string::size_type start = 0;
		::std::string::size_type end = text.find(delimiter, start);
		while (end != ::std::string::npos)
		{
			::std::string token = text.substr(start, end - start);
			if (token.size() > 0 || (token.empty() && pushEmpty))
				arr.push_back(token);
			start = end + 1;
			end = text.find(delimiter, start);
		}
		arr.push_back(text.substr(start));
	}
	return arr;
}

/////////////////////////////////////////////////////////////
///////// StringToVector ////////////////////////////////////
/////////////////////////////////////////////////////////////

::std::vector<::std::string> ct::StringToStringVector(const ::std::string& text, char delimiter)
{
	::std::vector<::std::string> arr;
	::std::string::size_type start = 0;
	::std::string::size_type end = text.find(delimiter, start);
	while (end != ::std::string::npos)
	{
		::std::string token = text.substr(start, end - start);
		arr.push_back(token);
		start = end + 1;
		end = text.find(delimiter, start);
	}
	arr.push_back(text.substr(start));
	return arr;
}
/*
#ifndef MINGW32
bool ct::StringToFloat(const ::std::string &vWord, float *vFloat)
{
	::std::stringstream ss;
	float vUniform = 0.0f;
	if (vWord.find_first_not_of("-+0123456789.") == ::std::string::npos)
	{
		
		ss.
		IsItaFloat >> vUniform;
		if (IsItaFloat)
		{
			*vFloat = vUniform;
			return true;
		}
	}
	return false;
}
bool ct::StringToInt(::std::string vWord, int *vInt)
{
	int vUniform = 0;
	if (vWord.find_first_not_of("-+0123456789") == ::std::string::npos)
	{
		::std::stringstream IsItaInt = ::std::stringstream(vWord);
		IsItaInt >> vUniform;
		if (IsItaInt)
		{
			*vInt = vUniform;
			return true;
		}
	}
	return false;
}
#endif
*/

#ifdef WXWIDGETS
::std::wstring ct::s2ws(const ::std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	::std::wstring r(buf);
	delete[] buf;
	return r;
}
#endif

::std::vector<::std::string::size_type> ct::strContains(const ::std::string& text, const ::std::string& word)
{
	::std::vector<::std::string::size_type> result;

	::std::string::size_type loc = 0;
	while ((loc = text.find(word, loc)) != ::std::string::npos)
	{
		result.push_back(loc);
		loc += word.size();
	}

	return result;
}

/////////////////////////////////////////////////////////////
///////// replaceString ////////////////////////////////////
/////////////////////////////////////////////////////////////

bool ct::replaceString(::std::string& str, const ::std::string& oldStr, const ::std::string& newStr)
{
	bool found = false;
	size_t pos = 0;
	while ((pos = str.find(oldStr, pos)) != ::std::string::npos)
	{
		found = true;
		str.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}
	return found;
}

/////////////////////////////////////////////////////////////
///////// Count Occurence ///////////////////////////////////
/////////////////////////////////////////////////////////////

size_t ct::cGetCountOccurence(::std::string vSrcString, ::std::string vStringToCount)
{
	size_t count = 0;
	size_t pos = 0;
	while ((pos = vSrcString.find(vStringToCount, pos)) != ::std::string::npos)
	{
		count++;
		pos += vStringToCount.length();
	}
	return count;
}
size_t ct::cGetCountOccurenceInSection(::std::string vSrcString, size_t vStartPos, size_t vEndpos, ::std::string vStringToCount)
{
	size_t count = 0;
	size_t pos = vStartPos;
	while (pos < vEndpos && (pos = vSrcString.find(vStringToCount, pos)) != ::std::string::npos)
	{
		if (pos < vEndpos)
		{
			count++;
			pos += vStringToCount.length();
		}
	}
	return count;
}
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////
///////// cActionTime ///////////////////////////////////////
/////////////////////////////////////////////////////////////
ct::int64 ct::GetTicks()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();
}

static ct::int64 lastTick = ct::GetTicks();

float ct::GetTimeInterval()
{
	int64 ticks = GetTicks();
	float interval = (ticks - lastTick) / 1000.0f;
	lastTick = ticks;
	return interval;
}

ct::cActionTime::cActionTime()
{
	lastTick = GetTicks();
}

void ct::cActionTime::Fix() // fixe le marqueur de temps
{
	lastTick = GetTicks();
}

void ct::cActionTime::Pause()
{
	pauseTick = GetTicks();
}

void ct::cActionTime::Resume()
{
	resumeTick = GetTicks();
	lastTick += resumeTick - pauseTick;
}

ct::int64 ct::cActionTime::get() { return (int64)(ct::GetTicks() - lastTick); }

bool ct::cActionTime::IsTimeToAct(long vMs, bool vFix)
{
	if (get() > vMs)
	{
		if (vFix)
			Fix();
		return true;
	}
	return false;
}

/////////////////////////////////////////////////////////////
///// cTexture //////////////////////////////////////////////
/////////////////////////////////////////////////////////////

::std::string ct::cTexture::getString()
{
	::std::string res;

	res += "----------------------------------------------\n";
	
	if (glTextureType == GL_TEXTURE_1D)					res += "type = GL_TEXTURE_1D\n";
	else if (glTextureType == GL_TEXTURE_2D)			res += "type = GL_TEXTURE_2D\n";
	else if (glTextureType == GL_TEXTURE_3D)			res += "type = GL_TEXTURE_3D\n";
		
	if (glformat == GL_RGBA)							res += "format = GL_RGBA\n";
	else if (glformat == GL_RGB)						res += "format = GL_RGB\n";

	if (glinternalformat == GL_RGBA)					res += "internal format = GL_RGBA\n";
	else if (glinternalformat == GL_RGBA32F)			res += "internal format = GL_RGBA32F\n";

	if (gldatatype == GL_FLOAT)							res += "Data Type = GL_FLOAT\n";
	else if (gldatatype == GL_UNSIGNED_BYTE)			res += "Data Type = GL_UNSIGNED_BYTE\n";

	if (glWrapS == GL_CLAMP_TO_EDGE)					res += "Wrap S = GL_CLAMP_TO_EDGE\n";
	else if (glWrapS == GL_REPEAT)						res += "Wrap S = GL_REPEAT\n";
	else if (glWrapS == GL_MIRRORED_REPEAT)				res += "Wrap S = GL_MIRRORED_REPEAT\n";

	if (glWrapT == GL_CLAMP_TO_EDGE)					res += "Wrap T = GL_CLAMP_TO_EDGE\n";
	else if (glWrapT == GL_REPEAT)						res += "Wrap T = GL_REPEAT\n";
	else if (glWrapT == GL_MIRRORED_REPEAT)				res += "Wrap T = GL_MIRRORED_REPEAT\n";

	if (glWrapR == GL_CLAMP_TO_EDGE)					res += "Wrap R = GL_CLAMP_TO_EDGE\n";
	else if (glWrapR == GL_REPEAT)						res += "Wrap R = GL_REPEAT\n";
	else if (glWrapR == GL_MIRRORED_REPEAT)				res += "Wrap R = GL_MIRRORED_REPEAT\n";

	if (useMipMap)										res += "Use MipMap = True\n";
	else												res += "Use MipMap = False\n";

	res += "MipMap Max Level = " + ct::toStr(maxMipMapLvl) + "\n";

	if (glMinFilter == GL_LINEAR)						res += "Min Filter = GL_LINEAR\n";
	else if (glMinFilter == GL_NEAREST)					res += "Min Filter = GL_NEAREST\n";
	else if (glMinFilter == GL_NEAREST_MIPMAP_NEAREST)	res += "Min Filter = GL_NEAREST_MIPMAP_NEAREST\n";
	else if (glMinFilter == GL_LINEAR_MIPMAP_NEAREST)	res += "Min Filter = GL_LINEAR_MIPMAP_NEAREST\n";
	else if (glMinFilter == GL_NEAREST_MIPMAP_LINEAR)	res += "Min Filter = GL_NEAREST_MIPMAP_LINEAR\n";
	else if (glMinFilter == GL_LINEAR_MIPMAP_LINEAR)	res += "Min Filter = GL_LINEAR_MIPMAP_LINEAR\n";

	if (glMagFilter == GL_LINEAR)						res += "Mag Filter = GL_LINEAR\n";
	else if (glMagFilter == GL_NEAREST)					res += "Mag Filter = GL_NEAREST\n";

	res += "Size = " + ct::toStr(w) + "," + ct::toStr(h) + "," + ct::toStr(d) + "\n";

	res += "----------------------------------------------\n";

	return res;
}

/////////////////////////////////////////////////////////////
///////// BUFFERS ///////////////////////////////////////////
/////////////////////////////////////////////////////////////

void ct::AppendToBuffer(char* vBuffer, size_t vBufferLen, ::std::string vStr)
{
	::std::string st = vStr;
	if (st != "" && st != "\n")
	{
        ct::replaceString(st, "\r", "");
        ct::replaceString(st, "\n", "");
		//LogStr(st);
	}

	size_t slen = strlen(vBuffer);
	vBuffer[slen] = '\0';
	::std::string str = ::std::string(vBuffer);
	if (str.size() > 0) str += "\n";
	str += vStr;
	size_t len = ct::mini<size_t>(vBufferLen - 1, str.size());

#ifndef MINGW32
	strncpy_s(vBuffer, vBufferLen, str.c_str(), len);
#else
	strncpy(vBuffer, str.c_str(), len);
#endif

	vBuffer[len] = '\0';
}

void ct::ResetBuffer(char* vBuffer)
{
	vBuffer[0] = '\0';
}

/////////////////////////////////////////////////////////////
///////// getNewBufferFromList //////////////////////////////
/////////////////////////////////////////////////////////////

// Buffer a destroy apres utilisationBufferSize
// in : lst, offset
// out : return, BufferSize
template<typename T>
T* ct::getNewBufferFromList(list<T> &lst, int offsetBefore, int offsetAfter, int *BufferSize)
{
	int count = (int)lst.size();
	if (count > 0)
	{
		*BufferSize = count + offsetBefore + offsetAfter;
		T *Buffer = new T[(*BufferSize)]; int idx = offsetBefore;
		// before init
		for (size_t i = 0; i < offsetBefore; i++)
		{
			Buffer[i] = T();
		}
		// content
		for (typename ::std::list<T>::iterator it = lst.begin(); it != lst.end(); ++it)
		{
			T obj = *it;
			Buffer[idx++] = obj;
		}
		// after init
		for (size_t i = 0; i < offsetAfter; i++)
		{
			Buffer[idx + i] = T();
		}
		return Buffer;
	}
	return 0;
}

/////////////////////////////////////////////////////////////
///////// getNewBufferFromMap ///////////////////////////////
/////////////////////////////////////////////////////////////

// Buffer a destroy apres utilisationBufferSize
// in : lst, offset
// out : return, BufferSize
template<typename T, typename P>
P* ct::getNewBufferFromMap(::std::map<T, P> &mp, int offsetBefore, int offsetAfter, int *BufferSize)
{
	int count = (int)mp.size();
	if (count > 0)
	{
		*BufferSize = count + offsetBefore + offsetAfter;
		P *Buffer = new P[(*BufferSize)]; int idx = offsetBefore;
		// before init
		for (size_t i = 0; i < (size_t)offsetBefore; i++)
		{
			Buffer[i] = P();
		}
		// content
		for (typename ::std::map<T, P>::iterator it = mp.begin(); it != mp.end(); ++it)
		{
			//			T key = it->first;
			P obj = it->second;

			Buffer[idx++] = obj;
		}
		// after init
		for (size_t i = 0; i < (size_t)offsetAfter; i++)
		{
			Buffer[idx + i] = P();
		}
		return Buffer;
	}
	return 0;
}

/////////////////////////////////////////////////////////////
///////// DeleteObjectsAndClearPointerList //////////////////
/////////////////////////////////////////////////////////////

template<typename T>
void ct::DeleteObjectsAndClearPointerList(::std::list<T*> &lst)
{
	if (lst.size() > 0)
	{
		for (typename ::std::list<T*>::iterator it = lst.begin(); it != lst.end(); ++it)
		{
			T* type = 0;
			type = *it;
			if (type != 0)
			{
				delete type;
				*it = 0;
			}
		}
		lst.clear();
	}
}

template<typename T>
void ct::DeleteObjectsAndClearPointerVector(::std::vector<T*> &vec)
{
	if (vec.size() > 0)
	{
		for (typename ::std::vector<T*>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			T* type = 0;
			type = *it;
			if (type != 0)
			{
				delete type;
				*it = 0;
			}
		}
		vec.clear();
	}
}

template<typename T>
::std::string ct::VectorToString(::std::vector<T> &vec, char vCharDelimiter)
{
	::std::string res;

	if (vec.size() > 0)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (it != vec.begin())
				res += vCharDelimiter;
			res += ct::toStr(*it);
		}
	}
	return res;
}

template<typename T>
::std::string ct::VectorVec2ToString(::std::vector<ct::vec2<T>> &vec, char vCharDelimiter)
{
	::std::string res;

	if (vec.size() > 0)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (it != vec.begin())
				res += vCharDelimiter;
			res += (*it).getString();
		}
	}
	return res;
}

template<typename T>
::std::string ct::VectorVec3ToString(::std::vector<ct::vec3<T>> &vec, char vCharDelimiter)
{
	::std::string res;

	if (vec.size() > 0)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (it != vec.begin())
				res += vCharDelimiter;
			res += (*it).getString();
		}
	}
	return res;
}

template<typename T>
::std::string ct::VectorVec4ToString(::std::vector<ct::vec4<T>> &vec, char vCharDelimiter)
{
	::std::string res;

	if (vec.size() > 0)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (it != vec.begin())
				res += vCharDelimiter;
			res += (*it).getString();
		}
	}
	return res;
}

// return "vParamName=\"" + ct::toStr(vValue) + "\";
template<typename T>
::std::string ct::ParamToXMLString(::std::string vParamName, T vValue)
{
	return " " + vParamName + "=\"" + ct::toStr(vValue) + "\"";
}

// return "vParamName=\"" + ct::toStr(vValue) + "\" si vValue est different de vValueDiff;
template<typename T>
::std::string ct::ParamToXMLStringDiff(::std::string vParamName, T vValue, T vValueDiff)
{
	if (vValue != vValueDiff)
		return " " + vParamName + "=\"" + ct::toStr(vValue) + "\"";
	return "";
}
/// Mix : get value based on ratio and inf and sup limit // https://www.opengl.org/sdk/docs/man/html/mix.xhtml
// ex : ct::mix(2.0f, 6.0f, 0.5f) => 4.0f

template<typename T>
ct::vec2<T> ct::mix(const ct::vec2<T>& vInf, const ct::vec2<T>& vSup, const ct::vec2<T>& vRatio)
{
	return vInf * (1.0f - vRatio) + vSup * vRatio;
}

template<typename T>
ct::vec3<T> ct::mix(const ct::vec3<T>& vInf, const ct::vec3<T>& vSup, const ct::vec3<T>& vRatio)
{
	return vInf * (1.0f - vRatio) + vSup * vRatio;
}

template<typename T>
ct::vec4<T> ct::mix(const ct::vec4<T>& vInf, const ct::vec4<T>& vSup, const ct::vec4<T>& vRatio)
{
	return vInf * (1.0f - vRatio) + vSup * vRatio;
}

/// get ratio based on value and inf and sup limit
// ex : cRatio(2.0f, 6.0f, 4.0f) => 0.5f
template<typename T>
ct::vec2<T> ct::invMix(const ct::vec2<T>& vInf, const ct::vec2<T>& vSup, const ct::vec2<T>& vValue)
{
	return (vValue - vInf) / (vSup - vInf);
}

template<typename T>
ct::vec3<T> ct::invMix(const ct::vec3<T>& vInf, const ct::vec3<T>& vSup, const ct::vec3<T>& vValue)
{
	return (vValue - vInf) / (vSup - vInf);
}

template<typename T>
ct::vec4<T> ct::invMix(const ct::vec4<T>& vInf, const ct::vec4<T>& vSup, const ct::vec4<T>& vValue)
{
	return (vValue - vInf) / (vSup - vInf);
}

/// clamp

template<typename T>
ct::vec2<T> ct::clamp(const ct::vec2<T>& vValue, const ct::vec2<T>& vInf, const ct::vec2<T>& vSup)
{
	ct::vec2<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf.x, vSup.x);
	vUniform.y = ct::clamp(vUniform.y, vInf.y, vSup.y);
	return vUniform;
}

template<typename T>
ct::vec3<T> ct::clamp(const ct::vec3<T>& vValue, const ct::vec3<T>& vInf, const ct::vec3<T>& vSup)
{
	ct::vec3<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf.x, vSup.x);
	vUniform.y = ct::clamp(vUniform.y, vInf.y, vSup.y);
	vUniform.z = ct::clamp(vUniform.z, vInf.z, vSup.z);
	return vUniform;
}

template<typename T>
ct::vec4<T> ct::clamp(const ct::vec4<T>& vValue, const ct::vec4<T>& vInf, const ct::vec4<T>& vSup)
{
	ct::vec4<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf.x, vSup.x);
	vUniform.y = ct::clamp(vUniform.y, vInf.y, vSup.y);
	vUniform.z = ct::clamp(vUniform.z, vInf.z, vSup.z);
	vUniform.w = ct::clamp(vUniform.w, vInf.w, vSup.w);
	return vUniform;
}

template<typename T>
ct::vec2<T> ct::clamp(const ct::vec2<T>& vValue, const T& vInf, const T& vSup)
{
	ct::vec2<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf, vSup);
	vUniform.y = ct::clamp(vUniform.y, vInf, vSup);
	return vUniform;
}

template<typename T>
ct::vec3<T> ct::clamp(const ct::vec3<T>& vValue, const T& vInf, const T& vSup)
{
	ct::vec3<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf, vSup);
	vUniform.y = ct::clamp(vUniform.y, vInf, vSup);
	vUniform.z = ct::clamp(vUniform.z, vInf, vSup);
	return vUniform;
}

template<typename T>
ct::vec4<T> ct::clamp(const ct::vec4<T>& vValue, const T& vInf, const T& vSup)
{
	ct::vec4<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x, vInf, vSup);
	vUniform.y = ct::clamp(vUniform.y, vInf, vSup);
	vUniform.z = ct::clamp(vUniform.z, vInf, vSup);
	vUniform.w = ct::clamp(vUniform.w, vInf, vSup);
	return vUniform;
}


template<typename T>
ct::vec2<T> ct::clamp(const ct::vec2<T>& vValue)
{
	ct::vec2<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x);
	vUniform.y = ct::clamp(vUniform.y);
	return vUniform;
}

template<typename T>
ct::vec3<T> ct::clamp(const ct::vec3<T>& vValue)
{
	ct::vec3<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x);
	vUniform.y = ct::clamp(vUniform.y);
	vUniform.z = ct::clamp(vUniform.z);
	return vUniform;
}

template<typename T>
ct::vec4<T> ct::clamp(const ct::vec4<T>& vValue)
{
	ct::vec4<T> vUniform = vValue;
	vUniform.x = ct::clamp(vUniform.x);
	vUniform.y = ct::clamp(vUniform.y);
	vUniform.z = ct::clamp(vUniform.z);
	vUniform.w = ct::clamp(vUniform.w);
	return vUniform;
}

// cMod

template<typename T>
ct::vec2<T> ct::mod(const ct::vec2<T>& vValue, const ct::vec2<T>& vLim)
{
	ct::vec2<T> vUniform = vValue;
	vUniform.x = cMod(vUniform.x, vLim.x);
	vUniform.y = cMod(vUniform.y, vLim.y);
	return vUniform;
}

template<typename T>
ct::vec3<T> ct::mod(const ct::vec3<T>& vValue, const ct::vec3<T>& vLim)
{
	ct::vec3<T> vUniform = vValue;
	vUniform.x = cMod(vUniform.x, vLim.x);
	vUniform.y = cMod(vUniform.y, vLim.y);
	vUniform.z = cMod(vUniform.z, vLim.z);
	return vUniform;
}

template<typename T>
ct::vec4<T> ct::mod(const ct::vec4<T>& vValue, const ct::vec4<T>& vLim)
{
	ct::vec4<T> vUniform = vValue;
	vUniform.x = cMod(vUniform.x, vLim.x);
	vUniform.y = cMod(vUniform.y, vLim.y);
	vUniform.z = cMod(vUniform.z, vLim.z);
	vUniform.w = cMod(vUniform.w, vLim.w);
	return vUniform;
}

template<typename T>
ct::vec2<T> ct::mod(const ct::vec2<T>& vValue, const T& vLim)
{
	ct::vec2<T> vUniform = vValue;
	vUniform.x = cMod(vUniform.x, vLim);
	vUniform.y = cMod(vUniform.y, vLim);
	return vUniform;
}

template<typename T>
ct::vec3<T> ct::mod(const ct::vec3<T>& vValue, const T& vLim)
{
	ct::vec3<T> vUniform = vValue;
	vUniform.x = cMod(vUniform.x, vLim);
	vUniform.y = cMod(vUniform.y, vLim);
	vUniform.z = cMod(vUniform.z, vLim);
	return vUniform;
}

template<typename T>
ct::vec4<T> ct::mod(const ct::vec4<T>& vValue, const T& vLim)
{
	ct::vec4<T> vUniform = vValue;
	vUniform.x = cMod(vUniform.x, vLim);
	vUniform.y = cMod(vUniform.y, vLim);
	vUniform.z = cMod(vUniform.z, vLim);
	vUniform.w = cMod(vUniform.w, vLim);
	return vUniform;
}
// ReRange value from range 0-MaxRange to range Sup-Inf and return new value
// 0 ----- Inf ----- value ---- Sup ---- MaxRange
template<typename T>
T ct::cReRange(const T& vMaxRange,
	const T& vNewRangeInf, const T& vNewRangeSup,
	const T& vValue)
{
	return (vValue - vNewRangeInf) * vMaxRange / (vNewRangeSup - vNewRangeInf);
}

/// Returns 1 for non-negative values and -1 for negative values.
size_t ct::cRatioOfSizeT(size_t t, float r)
{
	return (size_t)(t * r);
}

//////////////////////////////////////////////////////
///////// cColor /////////////////////////////////////
//////////////////////////////////////////////////////

ct::cColor ct::cColor::RandomColor()
{
	int r = (rand() % (256)); // 0 � 3
	int g = (rand() % (256)); // 0 � 3
	int b = (rand() % (256)); // 0 � 3
	int a = 255;
	return ct::cColor(r, g, b, a);
}
ct::cColor::cColor()
{
	r = g = b = a = 1.0f;
}
ct::cColor::cColor(::std::string colorName, char c)
{
	if (colorName == "red") setColor(1.0f, 0.0f, 0.0f, 1.0f);
	else if (colorName == "green") setColor(0.0f, 1.0f, 0.0f, 1.0f);
	else if (colorName == "blue") setColor(0.0f, 0.0f, 1.0f, 1.0f);
	else if (colorName == "purple") setColor(1.0f, 0.0f, 1.0f, 1.0f);
	else if (colorName == "neutral") setColor(0.0f, 1.0f, 1.0f, 1.0f);
	else //may be in format "0.2f,0.3f,0.4f"
	{
		::std::vector<float> result = StringToNumberVector<float>(colorName, c);
		if (result.size() == 3) setColor(result[0], result[1], result[2], 1.0f);
		else if (result.size() == 4) setColor(result[0], result[1], result[2], result[3]);
	}
}
ct::cColor::cColor(int _r, int _g, int _b, int _a)
{
	setColor(_r, _g, _b, _a);
}
ct::cColor::cColor(float _r, float _g, float _b, float _a)
{
	setColor(_r, _g, _b, _a);
}
ct::cColor::cColor(int _rgba)
{
	setColor(_rgba, _rgba, _rgba, _rgba);
}
ct::cColor::cColor(float _rgba)
{
	setColor(_rgba, _rgba, _rgba, _rgba);
}
ct::cColor::cColor(int _rgb, int _a)
{
	setColor(_rgb, _rgb, _rgb, _a);
}
ct::cColor::cColor(float _rgb, float _a)
{
	setColor(_rgb, _rgb, _rgb, _a);
}
ct::cColor::cColor(float col[], int size, float range)
{
	if (range == 0.0f) range = 1.0f;
	if (size > 0) r = col[0] / range;
	if (size > 1) g = col[1] / range;
	if (size > 2) b = col[2] / range;
	if (size > 3) a = col[3] / range;
}
#ifdef IMGUI
ct::cColor::cColor(ImVec4 _rgba)
{
	setColor(_rgba.x, _rgba.y, _rgba.z, _rgba.w);
}
#endif
void ct::cColor::setColor(int _r, int _g, int _b, int _a)
{
	r = _r / 255.0f;
	g = _g / 255.0f;
	b = _b / 255.0f;
	a = _a / 255.0f;
}
void ct::cColor::setColor(float _r, float _g, float _b, float _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}
void ct::cColor::setColor(const ct::cColor col)
{
	r = col.r;
	g = col.g;
	b = col.b;
	a = col.a;
}
void ct::cColor::getFloat3Arr(float col[3], float range)
{
	col[0] = r * range;
	col[1] = g * range;
	col[2] = b * range;
}
void ct::cColor::getFloat4Arr(float col[4], float range)
{
	col[0] = r * range;
	col[1] = g * range;
	col[2] = b * range;
	col[3] = a * range;
}
#ifdef COCOS2D
cocos2d::Color3B ct::cColor::getCCColor3B()
{
	cocos2d::Color3B col;
	col.r = r * 255;
	col.g = g * 255;
	col.b = b * 255;
	return col;
}
cocos2d::Color4F ct::cColor::getCCColor4F()
{
	cocos2d::Color4F col;
	col.r = r;
	col.g = g;
	col.b = b;
	col.a = a;
	return col;
}
#endif
void ct::cColor::setColorCanal(char canal, float value)
{
	if (canal == 'r') r = value;
	if (canal == 'g') g = value;
	if (canal == 'b') b = value;
	if (canal == 'a') a = value;
}
void ct::cColor::setColorCanal(char canal, int value)
{
	if (canal == 'r') r = value / 255.0f;
	if (canal == 'g') g = value / 255.0f;
	if (canal == 'b') b = value / 255.0f;
	if (canal == 'a') a = value / 255.0f;
}
#ifdef SDL2
SDL_Color ct::cColor::getSDLColor()
{
	SDL_Color col;
	col.r = uint8(r * 255.0f);
	col.g = uint8(g * 255.0f);
	col.b = uint8(b * 255.0f);
	col.a = uint8(a * 255.0f);
	return col;
}
#endif
#ifdef WXWIDGETS
wxColour ct::cColor::getWxColour()
{
	return wxColour(r * 255, g * 255, b * 255);
}
#endif
std::string ct::cColor::getColor3String()
{
	return ct::toStr(r) + ";" + toStr(g) + ";" + toStr(b);
}
std::string ct::cColor::getColor4String()
{
	return ct::toStr(r) + ";" + toStr(g) + ";" + toStr(b) + ";" + toStr(a);
}
#ifdef IMGUI
ImVec4 ct::cColor::ToImVec4()
{
	return ImVec4(r, g, b, a);
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////

//https://stackoverflow.com/questions/2685911/is-there-a-way-to-round-numbers-into-a-reader-friendly-format-e-g-1-1k?noredirect=1&lq=1
std::string ct::FormatNum(size_t vNum, int vDecimalCount)
{
	// 2 decimal places => 100, 3 => 1000, etc
	size_t decimalCount = (size_t)std::pow(10, vDecimalCount);

	// Enumerate number abbreviations
	char abbrev[] = { 'k', 'M', 'G', 'T' };
	int abbrevLength = 4;

	// Go through the array backwards, so we do the largest first
	for (int i = abbrevLength - 1; i >= 0; i--)
	{
		// Convert array index to "1000", "1000000", etc
		size_t size = (size_t)std::pow(10, (i + 1) * 3);

		// If the number is bigger or equal do the abbreviation
		if (size <= vNum)
		{
			// Here, we multiply by decPlaces, round, and then divide by decPlaces.
			// This gives us nice rounding to a particular decimal place.
			vNum = (size_t)std::round(vNum*decimalCount / size) / decimalCount;

			// Handle special case where we round up to the next abbreviation
			if ((vNum == 1000) && (i < abbrevLength - 1)) {
				vNum = 1;
				i++;
			}

			// Add the letter for the abbreviation
			return ct::toStr(vNum) + " " + abbrev[i];

			// We are done... stop
			break;
		}
	}

	return ct::toStr(vNum);
}