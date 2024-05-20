﻿/*
MIT License

Copyright (c) 2010-2021 Stephane Cuillerdier (aka Aiekick)

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

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || defined(__WIN64__) || defined(WIN64) || defined(_WIN64) || defined(_MSC_VER)
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

#ifdef WIN32
#include <Windows.h>
#endif

#ifndef CTOOLS
#define CTOOLS
#endif

#include <cassert>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <float.h>
#include <unordered_map>
#include <cstdarg> /* va_list, va_start, va_arg, va_end */
#include <sstream>
#include <iostream>
#include <chrono>
#include <iomanip>      // std::setprecision
#include <type_traits>  // std::is_same
#include <memory>
#include <clocale>  // std::setlocale
#include <locale>   // toupper, tolower (with locale)

#ifdef COCOS2D
#ifndef USE_OPENGL
#define USE_OPENGL
#endif
#include <cocos2d.h>
using namespace cocos2d;
#else
#ifdef GLEW
#ifndef USE_OPENGL
#define USE_OPENGL
#endif
#include <GL/glew.h>
#include <GL/wglew.h>
#define SAFE_DELETE_GL_BUFFER(a) \
    if (a > 0)                   \
    glDeleteBuffers(1, &a), a = 0
#define SAFE_DELETE_GL_VERTEX_ARRAY(a) \
    if (a > 0)                         \
    glDeleteVertexArrays(1, &a), a = 0
#endif
#ifdef GL3W
#ifndef USE_OPENGL
#define USE_OPENGL
#endif
#include <glad/glad.h>
#define SAFE_DELETE_GL_BUFFER(a) \
    if (a > 0)                   \
    glDeleteBuffers(1, &a), a = 0
#define SAFE_DELETE_GL_VERTEX_ARRAY(a) \
    if (a > 0)                         \
    glDeleteVertexArrays(1, &a), a = 0
#endif
#ifdef GLAD
#ifndef USE_OPENGL
#define USE_OPENGL
#endif
#include <glad/glad.h>
#define SAFE_DELETE_GL_BUFFER(a) \
    if (a > 0)                   \
    glDeleteBuffers(1, &a), a = 0
#define SAFE_DELETE_GL_VERTEX_ARRAY(a) \
    if (a > 0)                         \
    glDeleteVertexArrays(1, &a), a = 0
#endif
#define SAFE_DELETE(a) \
    if (a != 0)        \
    delete a, a = 0
#define SAFE_DELETE_ARRAY(a) \
    if (a != 0)              \
    delete[] a, a = 0
#endif

#define SAFE_SET_POINTERS_ARRAY(buf, size, value) \
    for (int i = 0; i < size; i++)                \
    buf[i] = value
#define SAFE_RESET_CHAR_ARRAY(buf) buf[0] = 0

#ifdef _MSC_VER
#define CTOOL_DEBUG_BREAK    \
    if (IsDebuggerPresent()) \
    __debugbreak()
#else
#define CTOOL_DEBUG_BREAK
#endif

#ifdef WXWIDGETS
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#endif

#ifdef USE_BOX2D
#include USE_BOX2D
#endif

#ifdef USE_SDL2
#include <SDL.h>
#include "Logger.h"
#endif

// simple macro for block debuggers
#if !defined(_DEBUG) && defined(_MSC_VER)
#define BLOCK_DEBUGGER(ret)  \
    if (IsDebuggerPresent()) \
    return ret
#else
#define BLOCK_DEBUGGER(ret)
#endif

namespace ct  // cTools
{

/////////////////////////////////////////////
////// DATEs Conversions ////////////////////
/////////////////////////////////////////////
        
// convert a string ISO8601 time to epoch time
bool iso8601ToEpoch(const std::string& vIsoDateTime, const std::string& vTimeFormat, std::time_t& vOutTime);

// convert a epoch time to a string ISO8601 time
bool epochToISO8601(const std::time_t& vEpochTime, std::string& vOutTime);

/////////////////////////////////////////////
////// UTF8 <> WideString ///////////////////
/////////////////////////////////////////////

// Convert a wide Unicode String to a UTF8 string
CTOOLS_API std::string UTF8Encode(const std::wstring& wstr);

// Convert a UTF8 string to a wide Unicode String
CTOOLS_API std::wstring UTF8Decode(const std::string& str);

/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////

// is a user datas of type void* is used
// we cant do a dynamic_cast, so for test if we have the good class
// we can use a magic number, because this member will not cause compiling issue
// and if this is the good class, the magic_number will point to a random memory zone
// so will not have the good value

CTOOLS_API int64_t EncodeId(const std::string& vArr);

CTOOLS_API bool IsIdEqualTo(const int64_t& vId, char vArr[8]);

/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////

template <typename T>
class SearchableVector {
private:
    std::unordered_map<T, size_t> m_Dico;
    std::vector<T> m_Array;

public:
    void clear() {
        m_Dico.clear();
        m_Array.clear();
    }
    bool empty() const {
        return m_Array.empty();
    }
    size_t size() const {
        return m_Array.size();
    }
    T& operator[](const size_t& vIdx) {
        return m_Array[vIdx];
    }
    T& at(const size_t& vIdx) {
        return m_Array.at(vIdx);
    }
    T* data() {
        return m_Array.data();
    }
    typename std::vector<T>::iterator begin() {
        return m_Array.begin();
    }
    typename std::vector<T>::const_iterator begin() const {
        return m_Array.begin();
    }
    typename std::vector<T>::iterator end() {
        return m_Array.end();
    }
    typename std::vector<T>::const_iterator end() const {
        return m_Array.end();
    }
    bool try_add(T vKey) {
        if (!exist(vKey)) {
            m_Dico[vKey] = m_Array.size();
            m_Array.push_back(vKey);
            return true;
        }
        return false;
    }
    bool try_set_existing(T vKey) {
        if (exist(vKey)) {
            auto row = m_Dico.at(vKey);
            m_Array[row] = vKey;
            return true;
        }
        return false;
    }
    bool exist(const T& vKey) const {
        return (m_Dico.find(vKey) != m_Dico.end());
    }
};

CTOOLS_API std::string toStr(const char* fmt, ...);

CTOOLS_API std::string toUpper(const std::string& vStr, const std::locale& vLocale = std::locale());
CTOOLS_API std::string toLower(const std::string& vStr, const std::locale& vLocale = std::locale());

// convert a string byte content to hex string
CTOOLS_API std::string toHex(const std::string& vStr);

template <typename T>
::std::string toStrFromArray(T* arr, size_t n, char delimiter = ';') {
    if (arr) {
        std::ostringstream os;
        for (size_t i = 0; i < n; ++i) {
            os << arr[i];
            if (i < n - 1)
                os << delimiter;
        }
        return os.str();
    }
    return "";
}

template <typename T>
::std::string toStr(T t) {
    std::ostringstream os;
    os << t;
    return os.str();
}

#include <ios>
template <typename T>
std::string toHexStr(T t) {
    std::ostringstream os;
    os << std::hex << t;
    return os.str();
}
template <typename T>
std::string toDecStr(T t) {
    std::ostringstream os;
    os << std::dec << t;
    return os.str();
}

#ifdef WIN32
typedef __int64 int64;
typedef unsigned __int64 uint64;
#else  // !WIN32
typedef long long int64;
typedef unsigned long long uint64;
#endif

#define _maxFloat FLT_MAX
#define _pi 3.14159265359f
#define _2pi 6.28318530717f

#define IS_FLOAT_DIFFERENT(a, b) (fabs((a) - (b)) > FLT_EPSILON)
#define IS_FLOAT_EQUAL(a, b) (fabs((a) - (b)) < FLT_EPSILON)
#define IS_DOUBLE_DIFFERENT(a, b) (fabs((a) - (b)) > DBL_EPSILON)
#define IS_DOUBLE_EQUAL(a, b) (fabs((a) - (b)) < DBL_EPSILON)

#define UNUSED(param) (void)param

/////////////////////////////////////////////////////////////
///////// DEGTORAD / RADTODEG ///////////////////////////////
/////////////////////////////////////////////////////////////

// usage : n *= DEGTORAD (n in degree to radian) or n *= RADTODEG (n in radian to degree)
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define DEGTORAD_D 0.0174532925199432957
#define RADTODEG_D 57.295779513082320876

/////////////////////////////////////////////////////////////

#define IFEXIST(ptr) \
    if (ptr)         \
    ptr

#ifdef USE_BOX2D
#define SAFE_USE_BOX2D_DESTROY_BODY(world, body) \
    if (world != 0 && body != 0)                 \
        world->DestroyBody(body);                \
    body = 0
#endif

/////////////////////////////////////////////////////////////
///////// bitwize ///////////////////////////////////////////
/////////////////////////////////////////////////////////////

// is this bit/bit_group is set and maybe others
bool CTOOLS_API isbitset(int32_t vContainer, int32_t vBit);
// is this bit/bit_group is set and only this one
bool CTOOLS_API isbitset_exclusive(int32_t vContainer, int32_t vBit);
// set this bit/bit_group to 1
void CTOOLS_API setbit(int32_t& vContainer, int32_t vBit);
// set this bit/bit_group to 0
void CTOOLS_API unsetbit(int32_t& vContainer, int32_t vBit);

/////////////////////////////////////////////////////////////
///////// splitStringToVector ///////////////////////////////
/////////////////////////////////////////////////////////////

CTOOLS_API std::list<std::string> splitStringToList(const std::string& text, const std::string& delimiters, bool pushEmpty = false, bool vInversion = false);
CTOOLS_API std::vector<std::string> splitStringToVector(const std::string& text, const std::string& delimiters, bool pushEmpty = false);
CTOOLS_API std::set<std::string> splitStringToSet(const std::string& text, const std::string& delimiters, bool pushEmpty = false);
CTOOLS_API std::list<std::string> splitStringToList(const std::string& text, char delimiter, bool pushEmpty = false, bool vInversion = false);
CTOOLS_API std::vector<std::string> splitStringToVector(const std::string& text, char delimiter, bool pushEmpty = false);
CTOOLS_API std::set<std::string> splitStringToSet(const std::string& text, char delimiter, bool pushEmpty = false);

/////////////////////////////////////////////////////////////
///////// StringToNumber ////////////////////////////////////
/////////////////////////////////////////////////////////////

template <typename T>
T StringToNumber(const std::string& text) {
    T value = (T)0;
    try {
        std::stringstream ss(text);
        ss >> value;
    } catch (std::exception&) {
        printf("%s is not a number\n", text.c_str());
    }
    return value;
}
template <typename T>
std::vector<T> StringToNumberVector(const std::string& text, char delimiter) {
    std::vector<T> arr;
    std::string::size_type start = 0;
    std::string::size_type end = text.find(delimiter, start);
    while (end != std::string::npos) {
        std::string token = text.substr(start, end - start);

        arr.emplace_back(StringToNumber<T>(token));
        start = end + 1;
        end = text.find(delimiter, start);
    }
    arr.emplace_back(StringToNumber<T>(text.substr(start).c_str()));
    return arr;
}

/*
#ifndef MINGW32
bool StringToFloat(std::string vWord, float *vFloat);
bool StringToInt(std::string vWord, int *vInt);
#endif
*/

#ifdef WXWIDGETS
std::wstring s2ws(const std::string& s);
#endif

CTOOLS_API std::vector<std::string::size_type> strContains(const std::string& text, const std::string& word);

CTOOLS_API bool replaceString(std::string& str, const std::string& oldStr, const std::string& newStr);

CTOOLS_API size_t GetCountOccurence(const std::string& vSrcString, const std::string& vStringToCount);
CTOOLS_API size_t GetCountOccurenceInSection(const std::string& vSrcString, size_t vStartPos, size_t vEndpos, const std::string& vStringToCount);
CTOOLS_API size_t GetCountOccurence(const std::string& vSrcString, const char& vStringToCount);
CTOOLS_API size_t GetCountOccurenceInSection(const std::string& vSrcString, size_t vStartPos, size_t vEndpos, const char& vStringToCount);

// std::wstring to std::string
// std::wstring(unicode/multibytes/char16/wchar_t) to std::string(char)
CTOOLS_API std::string wstring_to_string(const std::wstring& wstr);
// std::string to std::wstring
// std::string(char) to std::wstring(unicode/multibytes/char16/wchar_t)
CTOOLS_API std::wstring string_to_wstring(const std::string& mbstr);

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

CTOOLS_API inline std::string round_n(double vvalue, int n) {
    std::stringstream tmp;
    tmp << std::setprecision(n) << std::fixed << vvalue;
    return tmp.str();
}

/// This function is used to ensure that a floating point number is not a NaN or infinity.
CTOOLS_API inline bool floatIsValid(float x) {
    const union {
        float f;
        int32_t i;
    } v = {x};
    return (v.i & 0x7f800000) != 0x7f800000;
}

template <typename T>
inline T round(const T& v) {
    return (T)(std::round((double)v));
}
template <typename T>
inline T floor(const T& v) {
    return (T)(std::floor((double)v));
}
template <typename T>
inline T ceil(const T& v) {
    return (T)(std::ceil((double)v));
}
template <typename T>
inline T fract(const T& v) {
    return v - floor<T>(v);
}
template <typename T>
inline T cos(const T& v) {
    return std::cos(v);
}
template <typename T>
inline T acos(const T& v) {
    return std::acos(v);
}
template <typename T>
inline T sin(const T& v) {
    return std::sin(v);
}
template <typename T>
inline T asin(const T& v) {
    return std::asin(v);
}
template <typename T>
inline T tan(const T& v) {
    return std::tan(v);
}
template <typename T>
inline T atan(const T& v) {
    return std::atan(v);
}
template <typename T>
inline T mini(const T& a, const T& b) {
    return a < b ? a : b;
}
template <typename T>
inline T maxi(const T& a, const T& b) {
    return a > b ? a : b;
}

// for use in internals types, like vec2, vec3, vec4
template <typename T>
inline T internal_mini(const T& a, const T& b) {
    return a < b ? a : b;
}
template <typename T>
inline T internal_maxi(const T& a, const T& b) {
    return a > b ? a : b;
}

// template <typename T> inline T clamp(const T& a, const T& b, const T& c) { return mini<const T&>(maxi<const T&>(a, b), c); }

template <typename T>
inline T clamp(const T& n) {
    return n >= T(0) && n <= T(1) ? n : T(n > T(0));
}  // clamp n => 0 to 1
template <typename T>
inline T clamp(const T& n, const T& b) {
    return n >= T(0) && n <= b ? n : T(n > T(0)) * b;
}  // clamp n => 0 to b
template <typename T>
inline T clamp(const T& n, const T& a, const T& b) {
    return n >= a && n <= b ? n : n < a ? a : b;
}  // clamp n => a to b

template <typename T>
inline T abs(const T& a) {
    return a < 0 ? a * (T)-1 : a;
}
template <typename T>
inline T sign(const T& a) {
    return a < 0 ? (T)-1 : (T)1;
}
template <typename T>
inline T step(const T& a, const T& b) {
    return b < a ? (T)0 : (T)1;
}
template <typename T>
inline T mod(const T& v, const T& l) {
    return std::modf(v, l);
}
template <typename T>
inline T invMix(const T& i, const T& s, const T& r) {
    return (r - i) / (s - i);
}

// https://twitter.com/FreyaHolmer/status/1068293398073929728
template <typename T>
inline T lerp(const T& a, const T& b, const T& t) {
    return a * (1.0f - t) + b * t;
}
template <typename T>
inline T eerp(const T& a, const T& b, const T& t) {
    if (a == (T)0)
        return T(0);
    return pow(a * (b / a), t);
}

template <typename T>
inline T mix(const T& a, const T& b, const T& t) {
    return lerp(a, b, t);
}

/////////////////////////////////////////////////////////////
///////// cCyclicArray //////////////////////////////////////
/////////////////////////////////////////////////////////////

template <typename T>
class cCyclicArray {
private:
    std::vector<T> puArray;
    int puCount = 0;
    T puDefaultValue = (T)0;

public:
    cCyclicArray() {
    }

    void Init(T vDefaultValue, int vCount) {
        puDefaultValue = vDefaultValue;
        puCount = vCount;

        for (int i = 0; i < puCount; ++i) {
            puArray.emplace_back(puDefaultValue);
        }
    }

    void AddValue(T vValue) {
        puArray.erase(puArray.begin());
        puArray.emplace_back(vValue);
    }

    T GetMean() {
        T value = puDefaultValue;
        for (auto it = puArray.begin(); it != puArray.end(); ++it) {
            // if (*it != puDefaultValue)
            value += *it;
        }
        return value / puArray.size();
    }

    T GetMinValue(T vMaxValue) {
        T value = vMaxValue;
        for (auto it = puArray.begin(); it != puArray.end(); ++it) {
            if (*it < value)
                value = *it;
        }
        return value;
    }

    T GetMaxValue(T vMinValue) {
        T value = vMinValue;
        for (auto it = puArray.begin(); it != puArray.end(); ++it) {
            if (*it > value)
                value = *it;
        }
        return value;
    }

    T GetMeanExceptValue(T vExceptValue) {
        T value = puDefaultValue;
        int count = 0;
        for (auto it = puArray.begin(); it != puArray.end(); ++it) {
            if (*it != vExceptValue) {
                ++count;
                value += *it;
            }
        }
        return value / count;
    }
};

/////////////////////////////////////////////////////////////
///////// ActionTime ///////////////////////////////////////
/////////////////////////////////////////////////////////////

CTOOLS_API uint64_t GetTicks();
CTOOLS_API float GetTimeInterval();
class CTOOLS_API ActionTime {
public:
    uint64_t lastTick = 0;
    uint64_t pauseTick = 0;
    uint64_t resumeTick = 0;
    bool play = true;

public:
    ActionTime();
    void Fix();                   // fixe les marqueur de temps
    void FixTime(double vValue);  // fixe les marqueur de temps et set le temps
    void Pause();
    void Resume();
    uint64_t Get() const;
    double GetTime() const;
    void SetTime(double vValue);  // set le temps

    // verifie si vMs millisecond depuis le dernier fix et donc si on peut agir
    // vFix permet de fixer le temps pour la prochaine action
    // on pourrait vouloir interroger sans vouloir permettre la prochaine action
    bool IsTimeToAct(long vMs, bool vFix);
};

/////////////////////////////////////////////////////////////
///////// texture ///////////////////////////////////////////
/////////////////////////////////////////////////////////////
#ifdef USE_OPENGL
class CTOOLS_API texture {
public:
    texture() {
        clear();
    }

    ~texture() {
        if (glTex && glIsTexture(glTex) == GL_TRUE) {
            // on detruit la texture
            glDeleteTextures(1, &glTex);
            glFinish();
        }
    }

    void clear() {
        format.clear();
        relativPath.clear();
        zOrder = 0;
        w = h = d = x = y = z = 0;

#ifdef SDL2
        surface = nullptr;
#endif
        glTextureType = GL_TEXTURE_2D;
        glTex = 0;

        glformat = GL_RGBA;
        glinternalformat = GL_RGBA32F;
        gldatatype = GL_FLOAT;

        glWrapS = GL_CLAMP_TO_EDGE;
        glWrapT = GL_CLAMP_TO_EDGE;
        glWrapR = GL_CLAMP_TO_EDGE;

        glMinFilter = GL_LINEAR;
        glMagFilter = GL_LINEAR;

        flipY = false;
        useMipMap = false;
        maxMipMapLvl = 0;
    }

public:
    std::string GetString() const;

    std::string format;
    std::string relativPath;

    bool flipY = false;
    bool useMipMap = false;
    int maxMipMapLvl = 0;

    GLenum glTextureType = GL_TEXTURE_2D;

    GLenum glformat = GL_RGBA;
    GLenum glinternalformat = GL_RGBA32F;
    GLenum gldatatype = GL_FLOAT;

    GLenum glWrapS = GL_CLAMP_TO_EDGE;  // x
    GLenum glWrapT = GL_CLAMP_TO_EDGE;  // y
    GLenum glWrapR = GL_CLAMP_TO_EDGE;  // z
    GLenum glMinFilter = GL_LINEAR;
    GLenum glMagFilter = GL_LINEAR;

    size_t zOrder = 0;
    size_t w = 0;
    size_t h = 0;
    size_t d = 0;  // depth for texture 3d
    size_t x = 0;
    size_t y = 0;
    size_t z = 0;  // depth for texture 3d

#ifdef SDL2
    SDL_Surface* surface = nullptr;
#endif

    GLuint glTex = 0;

    std::vector<GLuint> glTexLayered;
};
#endif
/////////////////////////////////////////////////////////////
///////// Color /////////////////////////////////////////////
/////////////////////////////////////////////////////////////

template <typename T>
struct Color {
    T r = (T)1, g = (T)1, b = (T)1, a = (T)1;
    Color<T>() {
        r = g = b = a = (T)1;
    }
    Color<T>(T _rgba) {
        setColor(_rgba, _rgba, _rgba, _rgba);
    }
    Color<T>(T _rgb, T _a) {
        setColor(_rgb, _rgb, _rgb, _a);
    }
    Color<T>(T _r, T _g, T _b, T _a, T _Div = (T)1) {
        setColor(_r, _g, _b, _a, _Div);
    }
    Color<T>(T col[], int size, T range) {
        if (range == (T)0)
            range = (T)1;
        if (size > 0)
            r = col[0] / range;
        if (size > 1)
            g = col[1] / range;
        if (size > 2)
            b = col[2] / range;
        if (size > 3)
            a = col[3] / range;
    }
    Color<T>(std::string colorName, char c) {
        if (colorName == "red")
            setColor(1.0f, 0.0f, 0.0f, 1.0f);
        else if (colorName == "green")
            setColor(0.0f, 1.0f, 0.0f, 1.0f);
        else if (colorName == "blue")
            setColor(0.0f, 0.0f, 1.0f, 1.0f);
        else if (colorName == "purple")
            setColor(1.0f, 0.0f, 1.0f, 1.0f);
        else if (colorName == "neutral")
            setColor(0.0f, 1.0f, 1.0f, 1.0f);
        else  // may be in format "0.2f,0.3f,0.4f"
        {
            std::vector<float> result = StringToNumberVector<float>(colorName, c);
            if (result.size() == 3)
                setColor(result[0], result[1], result[2], 1.0f);
            else if (result.size() == 4)
                setColor(result[0], result[1], result[2], result[3]);  //-V112
        }
    }
    Color<T> RandomColor() {
        int _r = (rand() % (256));  // 0 a 3
        int _g = (rand() % (256));  // 0 a 3
        int _b = (rand() % (256));  // 0 a 3
        int _a = 255;
        return Color(_r, _g, _b, _a);
    }
    void setColor(T _r, T _g, T _b, T _a, T Div = (T)1) {
        assert((T)Div != (T)0);

        if ((int)Div == 1) {
            r = (T)_r;
            g = (T)_g;
            b = (T)_b;
            a = (T)_a;
        } else {
            r = (T)_r / Div;
            g = (T)_g / Div;
            b = (T)_b / Div;
            a = (T)_a / Div;
        }
    }
    void setColor(const Color<T>& col) {
        r = col.r;
        g = col.g;
        b = col.b;
        a = col.a;
    }
    void Get3Arr(T col[3], T range = (T)1) {
        col[0] = r * range;
        col[1] = g * range;
        col[2] = b * range;
    }
    void Get4Arr(T col[4], T range = (T)1) {
        col[0] = r * range;
        col[1] = g * range;
        col[2] = b * range;
        col[3] = a * range;
    }
#ifdef COCOS2D
    cocos2d::Color3B GetCCColor3B() {
        cocos2d::Color3B col;
        col.r = r * 255;
        col.g = g * 255;
        col.b = b * 255;
        return col;
    }
    cocos2d::Color4F GetCCColor4F() {
        cocos2d::Color4F col;
        col.r = r;
        col.g = g;
        col.b = b;
        col.a = a;
        return col;
    }
#endif
    void setColorCanal(char canal, float value) {
        if (canal == 'r')
            r = value;
        if (canal == 'g')
            g = value;
        if (canal == 'b')
            b = value;
        if (canal == 'a')
            a = value;
    }
    void setColorCanal(char canal, int value) {
        if (canal == 'r')
            r = value / 255.0f;
        if (canal == 'g')
            g = value / 255.0f;
        if (canal == 'b')
            b = value / 255.0f;
        if (canal == 'a')
            a = value / 255.0f;
    }
#ifdef SDL2
    SDL_Color GetSDLColor() {
        SDL_Color col;
        col.r = uint8_t(r * 255.0f);
        col.g = uint8_t(g * 255.0f);
        col.b = uint8_t(b * 255.0f);
        col.a = uint8_t(a * 255.0f);
        return col;
    }
#endif
#ifdef WXWIDGETS
    wxColour GetWxColour() {
        return wxColour(r * 255, g * 255, b * 255);
    }
#endif
    std::string GetColor3String() {
        return toStr(r) + ";" + toStr(g) + ";" + toStr(b);
    }
    std::string GetColor4String() {
        return toStr(r) + ";" + toStr(g) + ";" + toStr(b) + ";" + toStr(a);
    }
};
typedef Color<uint8_t> ui8Color;
typedef Color<float> fColor;

/////////////////////////////////////////////////////////////
///////// Vec2 //////////////////////////////////////////////
/////////////////////////////////////////////////////////////
template <typename T>
struct vec2 {
    T x = (T)0, y = (T)0;
    vec2<T>() {
        x = (T)0;
        y = (T)0;
    }
    template <typename U>
    vec2<T>(const vec2<U>& a) {
        x = (T)a.x;
        y = (T)a.y;
    }
    vec2<T>(const T& a) {
        x = a;
        y = a;
    }
    vec2<T>(const T& a, const T& b) {
        x = a;
        y = b;
    }
    vec2<T>(const std::string& vec, const char& c = ';', vec2<T>* def = nullptr)  // may be in format "0.2f,0.3f,0.4f"
    {
        if (def) {
            x = def->x;
            y = def->y;
        }
        std::vector<T> result = StringToNumberVector<T>(vec, c);
        const size_t s = result.size();
        if (s > 0)
            x = result[0];
        if (s > 1)
            y = result[1];
    }
#ifdef USE_BOX2D
    vec2<T>(const b2Vec2& vec, const float& vRatio = 1.0f) {
        x = (T)vec.x * vRatio;
        y = (T)vec.y * vRatio;
    }
#endif
    T& operator[](const size_t& i) {
        return (&x)[i];
    }
    vec2<T> Offset(const T& vX, const T& vY) const {
        return vec2<T>(x + vX, y + vY);
    }
    void Set(const T& vX, const T& vY) {
        x = vX;
        y = vY;
    }
    vec2<T> operator-() const {
        return vec2<T>(-x, -y);
    }
    vec2<T> operator!() const {
        return vec2<T>(!(bool)x, !(bool)y);
    }
    vec2<T>& operator++() {
        ++x;
        ++y;
        return *this;
    }  // pre inc
    vec2<T>& operator--() {
        --x;
        --y;
        return *this;
    }  // pre dec
    vec2<T> operator++(int) {
        vec2<T> tmp = *this;
        ++*this;
        return tmp;
    }  // post inc
    vec2<T> operator--(int) {
        vec2<T> tmp = *this;
        --*this;
        return tmp;
    }  // post dec
    void operator+=(const T& a) {
        x += a;
        y += a;
    }
    void operator+=(const vec2<T>& v) {
        x += v.x;
        y += v.y;
    }
    void operator-=(const T& a) {
        x -= a;
        y -= a;
    }
    void operator-=(const vec2<T>& v) {
        x -= v.x;
        y -= v.y;
    }
    bool operator==(const T& a) {
        return (x == a) && (y == a);
    }
    bool operator==(const vec2<T>& v) {
        return (x == v.x) && (y == v.y);
    }
    bool operator!=(const T& a) {
        return (x != a) || (y != a);
    }
    bool operator!=(const vec2<T>& v) {
        return (x != v.x) || (y != v.y);
    }
    void operator*=(const T& a) {
        x *= a;
        y *= a;
    }
    void operator*=(const vec2<T>& v) {
        x *= v.x;
        y *= v.y;
    }
    void operator/=(const T& a) {
        x /= a;
        y /= a;
    }
    void operator/=(const vec2<T>& v) {
        x /= v.x;
        y /= v.y;
    }
    T lengthSquared() const {
        return x * x + y * y;
    }
    T length() const {
        return (T)sqrt(lengthSquared());
    }
    T normalize() {
        T _length = length();
        if (_length < (T)1e-5)
            return (T)0.0;
        T _invLength = (T)1.0 / _length;
        x *= _invLength;
        y *= _invLength;
        return _length;
    }  // return length
    vec2<T> GetNormalized() const {
        vec2<T> n = vec2<T>(x, y);
        n.normalize();
        return n;
    }
    T sum() const {
        return x + y;
    }
    T sumAbs() const {
        return abs<T>(x) + abs<T>(y);
    }
    bool emptyAND() const {
        return x == (T)0 && y == (T)0;
    }
    bool emptyOR() const {
        return x == (T)0 || y == (T)0;
    }
    std::string string(const char& c = ';') const {
        return toStr(x) + c + toStr(y);
    }
    template <typename U>
    U ratioXY() const {
        if (y != (T)0)
            return (U)x / (U)y;
        return (U)0;
    }
    template <typename U>
    U ratioYX() const {
        if (x != (T)0)
            return (U)y / (U)x;
        return (U)0;
    }
    T mini() const {
        return internal_mini<T>(x, y);
    }
    T maxi() const {
        return internal_maxi<T>(x, y);
    }
};

// https://en.cppreference.com/w/cpp/language/operator_incdec
template <typename T>
inline vec2<T>& operator++(vec2<T>& v) {
    ++v;
    return v;
}  // pre inc
template <typename T>
inline vec2<T>& operator--(vec2<T>& v) {
    --v;
    return v;
}  // pre dec
template <typename T>
inline vec2<T> operator++(vec2<T>& v, int) {
    vec2<T> a = v;
    ++a;
    return a;
}  // post inc
template <typename T>
inline vec2<T> operator--(vec2<T>& v, int) {
    vec2<T> a = v;
    --a;
    return a;
}  // post dec
template <typename T>
inline vec2<T> operator+(vec2<T> v, T f) {
    return vec2<T>(v.x + f, v.y + f);
}
template <typename T>
inline vec2<T> operator+(T f, vec2<T> v) {
    return vec2<T>(v.x + f, v.y + f);
}
template <typename T>
inline vec2<T> operator+(vec2<T> v, vec2<T> f) {
    return vec2<T>(v.x + f.x, v.y + f.y);
}
template <typename T>
inline vec2<T> operator-(vec2<T> v, T f) {
    return vec2<T>(v.x - f, v.y - f);
}
template <typename T>
inline vec2<T> operator-(T f, vec2<T> v) {
    return vec2<T>(f - v.x, f - v.y);
}
template <typename T>
inline vec2<T> operator-(vec2<T> v, vec2<T> f) {
    return vec2<T>(v.x - f.x, v.y - f.y);
}
template <typename T>
inline vec2<T> operator*(vec2<T> v, T f) {
    return vec2<T>(v.x * f, v.y * f);
}
template <typename T>
inline vec2<T> operator*(T f, vec2<T> v) {
    return vec2<T>(v.x * f, v.y * f);
}
template <typename T>
inline vec2<T> operator*(vec2<T> v, vec2<T> f) {
    return vec2<T>(v.x * f.x, v.y * f.y);
}
template <typename T>
inline vec2<T> operator/(vec2<T> v, T f) {
    return vec2<T>(v.x / f, v.y / f);
}
template <typename T>
inline vec2<T> operator/(T f, vec2<T> v) {
    return vec2<T>(f / v.x, f / v.y);
}
template <typename T>
inline vec2<T> operator/(vec2<T> v, vec2<T> f) {
    return vec2<T>(v.x / f.x, v.y / f.y);
}
template <typename T>
inline bool operator<(vec2<T> v, vec2<T> f) {
    return v.x < f.x && v.y < f.y;
}
template <typename T>
inline bool operator<(vec2<T> v, T f) {
    return v.x < f && v.y < f;
}
template <typename T>
inline bool operator>(vec2<T> v, vec2<T> f) {
    return v.x > f.x && v.y > f.y;
}
template <typename T>
inline bool operator>(vec2<T> v, T f) {
    return v.x > f && v.y > f;
}
template <typename T>
inline bool operator<=(vec2<T> v, vec2<T> f) {
    return v.x <= f.x && v.y <= f.y;
}
template <typename T>
inline bool operator<=(vec2<T> v, T f) {
    return v.x <= f && v.y <= f;
}
template <typename T>
inline bool operator>=(vec2<T> v, vec2<T> f) {
    return v.x >= f.x && v.y >= f.y;
}
template <typename T>
inline bool operator>=(vec2<T> v, T f) {
    return v.x >= f && v.y >= f;
}
template <typename T>
inline bool operator!=(vec2<T> v, vec2<T> f) {
    return f.x != v.x || f.y != v.y;
}
template <typename T>
inline bool operator==(vec2<T> v, vec2<T> f) {
    return f.x == v.x && f.y == v.y;
}
template <typename T>
inline vec2<T> floor(vec2<T> a) {
    return vec2<T>(floor(a.x), floor(a.y));
}
template <typename T>
inline vec2<T> fract(vec2<T> a) {
    return vec2<T>(fract(a.x), fract(a.y));
}
template <typename T>
inline vec2<T> ceil(vec2<T> a) {
    return vec2<T>(ceil(a.x), ceil(a.y));
}
template <typename T>
inline vec2<T> mini(vec2<T> a, vec2<T> b) {
    return vec2<T>(mini(a.x, b.x), mini(a.y, b.y));
}
template <typename T>
inline vec2<T> maxi(vec2<T> a, vec2<T> b) {
    return vec2<T>(maxi(a.x, b.x), maxi(a.y, b.y));
}
template <typename T>
inline T dot(vec2<T> a, vec2<T> b) {
    return a.x * b.x + a.y * b.y;
}
template <typename T>
inline T det(vec2<T> a, vec2<T> b) {
    return a.x * b.y - a.y * b.x;
}
template <typename T>
inline vec2<T> cross(vec2<T> a, vec2<T> b) {
    return vec2<T>(a.x * b.y - a.y * b.x, a.y * b.x - a.x * b.y);
}
template <typename T>
inline vec2<T> reflect(vec2<T> I, vec2<T> N) {
    return I - (T)2 * dotS(N, I) * N;
}
template <typename T>
inline vec2<T> sign(vec2<T> a) {
    return vec2<T>(a.x < (T)0 ? -(T)1 : (T)1, a.y < (T)0 ? (T)-1 : (T)1);
}
template <typename T>
inline vec2<T> sin(vec2<T> a) {
    return vec2<T>(sin<T>(a.x), sin<T>(a.y));
}
template <typename T>
inline vec2<T> cos(vec2<T> a) {
    return vec2<T>(cos<T>(a.x), cos<T>(a.y));
}
template <typename T>
inline vec2<T> tan(vec2<T> a) {
    return vec2<T>(tan<T>(a.x), tan<T>(a.y));
}
template <typename T>
inline vec2<T> atan(vec2<T> a) {
    return vec2<T>(atan<T>(a.x), atan<T>(a.y));
}
using dvec2 = vec2<double>;
using fvec2 = vec2<float>;
using bvec2 = vec2<bool>;
using i8vec2 = vec2<int8_t>;
using i16vec2 = vec2<int16_t>;
using ivec2 = vec2<int32_t>;
using i32vec2 = vec2<int32_t>;
using i64vec2 = vec2<int64_t>;
using u8vec2 = vec2<uint8_t>;
using u16vec2 = vec2<uint16_t>;
using uvec2 = vec2<uint32_t>;
using u32vec2 = vec2<uint32_t>;
using u64vec2 = vec2<uint64_t>;

// convert
CTOOLS_API inline fvec2 convert(const ivec2& v) {
    return fvec2((float)v.x, (float)v.y);
}
CTOOLS_API inline ivec2 convert(const fvec2& v) {
    return ivec2((int)v.x, (int)v.y);
}

#ifdef USE_BOX2D
CTOOLS_API inline b2Vec2 tob2v2(const fvec2& v) {
    return b2Vec2(v.x, v.y);
}
CTOOLS_API inline b2Vec2 tob2v2(const fvec2& v, const float& r) {
    return b2Vec2(v.x / r, v.y / r);
}
#endif

// specialization for float32 test to fvec2
CTOOLS_API inline bool valid(const fvec2& a) {
    return floatIsValid(a.x) && floatIsValid(a.y);
}

// specialization for fvec2
CTOOLS_API inline bool operator==(const fvec2& v, const fvec2& f) {
    return (IS_FLOAT_EQUAL(f.x, v.x) && IS_FLOAT_EQUAL(f.y, v.y));
}
CTOOLS_API inline bool operator!=(const fvec2& v, const fvec2& f) {
    return (IS_FLOAT_DIFFERENT(f.x, v.x) || IS_FLOAT_DIFFERENT(f.y, v.y));
}

// ne peut focntionner qu'avec double ou float au fond
template <typename T>
inline T prototype_radAngleFromVec2(vec2<T> vec) {
    T angle = 0.0f;
    if (vec.lengthSquared() > T(0) && vec.x != T(0)) {
        angle = atan<T>(vec.y / vec.x);
    }
    return angle;
}

// specialisation
CTOOLS_API inline float radAngleFromVec2(const fvec2& vec) {
    return prototype_radAngleFromVec2(vec);
}
CTOOLS_API inline double radAngleFromVec2(const dvec2& vec) {
    return prototype_radAngleFromVec2(vec);
}

// ne peut focntionner qu'avec double ou float au fond
template <typename T>
inline T prototype_radAngleContinuousFromVec2(vec2<T> vec, T angleOffset) {
    T angle = T(0);
    if (vec.x > T(0))
        angle = atan<T>(vec.y / vec.x);
    if (vec.x < T(0))
        angle = _pi - atan<T>(-vec.y / vec.x);
    return angle - angleOffset;
}

// specialisation
CTOOLS_API inline float radAngleContinuousFromVec2(const fvec2& vec, float angleOffset) {
    return prototype_radAngleContinuousFromVec2(vec, angleOffset);
}
CTOOLS_API inline double radAngleContinuousFromVec2(const dvec2& vec, double angleOffset) {
    return prototype_radAngleContinuousFromVec2(vec, angleOffset);
}

/////////////////////////////////////////////////////////////////////////

template <typename T>
struct mat2 {
    //   0 1
    // 0 x y => 0 1
    // 1 z w => 2 3
    T m[4];
    mat2(T x, T y, T z, T w) {
        m[0] = x;
        m[1] = y;
        m[2] = z;
        m[3] = w;
    }
    T operator[](size_t i) {
        return m[i];
    }
};
template <typename T>
inline mat2<T> operator*(const mat2<T>& a, mat2<T> b) {
    return mat2<T>(a[0] * b[0] + a[2] * b[2], a[0] * b[1] + a[2] * b[3], a[2] * b[0] + a[3] * b[2], a[2] * b[1] + a[3] * b[3]);
}
template <typename T>
inline vec2<T> operator*(const vec2<T>& a, mat2<T> b) {
    return vec2<T>(
        // ax * (x y)
        // ay * (z w)
        a.x * b[0] + a.x * b[1],
        a.y * b[2] + a.y * b[3]);
}
template <typename T>
inline vec2<T> operator*(const mat2<T>& a, vec2<T> b) {
    return vec2<T>(
        // (x y) * bx
        // (z w) * by
        a[0] * b.x + a[1] * b.y,
        a[2] * b.x + a[3] * b.y);
}
typedef mat2<float> mat2f;
typedef mat2<double> mat2d;

/////////////////////////////////////////////////////////////////////////

template <typename T>
struct vec3 {
    T x = (T)0, y = (T)0, z = (T)0;
    vec3() : x((T)0), y((T)0), z((T)0) {
    }
    template <typename U>
    vec3<T>(vec3<U> a) {
        x = (T)a.x;
        y = (T)a.y;
        z = (T)a.z;
    }
    vec3(const T& xyz) : x(xyz), y(xyz), z(xyz) {
    }
    vec3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {
    }
    vec3(const vec2<T>& xy, const T& z) : x(xy.x), y(xy.y), z(z) {
    }
    vec3(const std::string& vec, const char& c = ';', vec3<T>* def = nullptr)  // may be in format "0.2f,0.3f,0.4f"
    {
        if (def) {
            x = def->x;
            y = def->y;
            z = def->z;
        }
        std::vector<T> result = StringToNumberVector<T>(vec, c);
        const size_t s = result.size();
        if (s > 0)
            x = result[0];
        if (s > 1)
            y = result[1];
        if (s > 2)
            z = result[2];
    }
    T& operator[](const size_t& i) {
        return (&x)[i];
    }
    vec3<T> Offset(const T& vX, const T& vY, const T& vZ) const {
        return vec3<T>(x + vX, y + vY, z + vZ);
    }
    void Set(const T& vX, const T& vY, const T& vZ) {
        x = vX;
        y = vY;
        z = vZ;
    }
    vec3<T> operator-() const {
        return vec3<T>(-x, -y, -z);
    }
    vec3<T> operator!() const {
        return vec3<T>(!(bool)x, !(bool)y, !(bool)z);
    }
    vec2<T> xy() const {
        return vec2<T>(x, y);
    }
    vec2<T> xz() const {
        return vec2<T>(x, z);
    }
    vec2<T> yz() const {
        return vec2<T>(y, z);
    }
    vec3 yzx() const {
        return vec3<T>(y, z, x);
    }
    // https://en.cppreference.com/w/cpp/language/operator_incdec
    vec3<T>& operator++() {
        ++x;
        ++y;
        ++z;
        return *this;
    }  // pre inc
    vec3<T>& operator--() {
        --x;
        --y;
        --z;
        return *this;
    }  // pre dec
    vec3<T> operator++(int) {
        vec3<T> tmp = *this;
        ++*this;
        return tmp;
    }  // post inc
    vec3<T> operator--(int) {
        vec3<T> tmp = *this;
        --*this;
        return tmp;
    }  // post dec
    void operator+=(const T& a) {
        x += a;
        y += a;
        z += a;
    }
    void operator+=(const vec3<T>& v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }
    void operator-=(const T& a) {
        x -= a;
        y -= a;
        z -= a;
    }
    void operator-=(const vec3<T>& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }
    bool operator==(const T& a) {
        return (x == a) && (y == a) && (z == a);
    }
    bool operator==(const vec3<T>& v) {
        return (x == v.x) && (y == v.y) && (z == v.z);
    }
    bool operator!=(const T& a) {
        return (x != a) || (y != a) || (z != a);
    }
    bool operator!=(const vec3<T>& v) {
        return (x != v.x) || (y != v.y) || (z != v.z);
    }
    void operator*=(const T& a) {
        x *= a;
        y *= a;
        z *= a;
    }
    void operator*=(const vec3<T>& v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
    }
    void operator/=(const T& a) {
        x /= a;
        y /= a;
        z /= a;
    }
    void operator/=(const vec3<T>& v) {
        x /= v.x;
        y /= v.y;
        z /= v.z;
    }
    T length() const {
        return (T)sqrt(lengthSquared());
    }
    T lengthSquared() const {
        return x * x + y * y + z * z;
    }
    T normalize() {
        T _length = length();
        if (_length < std::numeric_limits<T>::epsilon())
            return (T)0;
        T _invLength = (T)1 / _length;
        x *= _invLength;
        y *= _invLength;
        z *= _invLength;
        return _length;
    }
    vec3<T> GetNormalized() const {
        vec3<T> n = vec3<T>(x, y, z);
        n.normalize();
        return n;
    }
    T sum() const {
        return x + y + z;
    }
    T sumAbs() const {
        return abs<T>(x) + abs<T>(y) + abs<T>(z);
    }
    bool emptyAND() const {
        return x == (T)0 && y == (T)0 && z == (T)0;
    }
    bool emptyOR() const {
        return x == (T)0 || y == (T)0 || z == (T)0;
    }
    std::string string(const char& c = ';') const {
        return toStr(x) + c + toStr(y) + c + toStr(z);
    }
    T mini() const {
        return internal_mini<T>(x, internal_mini<T>(y, z));
    }
    T maxi() const {
        return internal_maxi<T>(x, internal_maxi<T>(y, z));
    }
};
// https://en.cppreference.com/w/cpp/language/operator_incdec
template <typename T>
inline vec3<T>& operator++(vec3<T>& v) {
    ++v;
    return v;
}  // pre inc
template <typename T>
inline vec3<T>& operator--(vec3<T>& v) {
    --v;
    return v;
}  // pre dec
template <typename T>
inline vec3<T> operator++(vec3<T>& v, int) {
    vec3<T> a = v;
    ++a;
    return a;
}  // post inc
template <typename T>
inline vec3<T> operator--(vec3<T>& v, int) {
    vec3<T> a = v;
    --a;
    return a;
}  // post dec
template <typename T>
inline vec3<T> operator+(vec3<T> v, T f) {
    return vec3<T>(v.x + f, v.y + f, v.z + f);
}
template <typename T>
inline vec3<T> operator+(vec3<T> v, vec3<T> f) {
    return vec3<T>(v.x + f.x, v.y + f.y, v.z + f.z);
}
template <typename T>
inline vec3<T> operator+(T f, vec3<T> v) {
    return vec3<T>(f + v.x, f + v.y, f + v.z);
}
template <typename T>
inline vec3<T> operator-(vec3<T> v, T f) {
    return vec3<T>(v.x - f, v.y - f, v.z - f);
}
template <typename T>
inline vec3<T> operator-(vec3<T> v, vec3<T> f) {
    return vec3<T>(v.x - f.x, v.y - f.y, v.z - f.z);
}
template <typename T>
inline vec3<T> operator-(T f, vec3<T> v) {
    return vec3<T>(f - v.x, f - v.y, f - v.z);
}
template <typename T>
inline vec3<T> operator*(vec3<T> v, T f) {
    return vec3<T>(v.x * f, v.y * f, v.z * f);
}
template <typename T>
inline vec3<T> operator*(vec3<T> v, vec3<T> f) {
    return vec3<T>(v.x * f.x, v.y * f.y, v.z * f.z);
}
template <typename T>
inline vec3<T> operator*(T f, vec3<T> v) {
    return vec3<T>(f * v.x, f * v.y, f * v.z);
}
template <typename T>
inline vec3<T> operator/(vec3<T> v, T f) {
    return vec3<T>(v.x / f, v.y / f, v.z / f);
}
template <typename T>
inline vec3<T> operator/(T f, vec3<T> v) {
    return vec3<T>(f / v.x, f / v.y, f / v.z);
}
template <typename T>
inline vec3<T> operator/(vec3<T> v, vec3<T> f) {
    return vec3<T>(v.x / f.x, v.y / f.y, v.z / f.z);
}
template <typename T>
inline bool operator<(vec3<T> v, vec3<T> f) {
    return v.x < f.x && v.y < f.y && v.z < f.z;
}
template <typename T>
inline bool operator<(vec3<T> v, T f) {
    return v.x < f && v.y < f && v.z < f;
}
template <typename T>
inline bool operator>(vec3<T> v, vec3<T> f) {
    return v.x > f.x && v.y > f.y && v.z > f.z;
}
template <typename T>
inline bool operator>(vec3<T> v, T f) {
    return v.x > f && v.y > f && v.z > f;
}
template <typename T>
inline bool operator<=(vec3<T> v, vec3<T> f) {
    return v.x <= f.x && v.y <= f.y && v.z <= f.z;
}
template <typename T>
inline bool operator<=(vec3<T> v, T f) {
    return v.x <= f && v.y <= f && v.z <= f;
}
template <typename T>
inline bool operator>=(vec3<T> v, vec3<T> f) {
    return v.x >= f.x && v.y >= f.y && v.z >= f.z;
}
template <typename T>
inline bool operator>=(vec3<T> v, T f) {
    return v.x >= f && v.y >= f && v.z >= f;
}
template <typename T>
inline bool operator!=(vec3<T> v, vec3<T> f) {
    return f.x != v.x || f.y != v.y || f.z != v.z;
}
template <typename T>
inline bool operator==(vec3<T> v, vec3<T> f) {
    return f.x == v.x && f.y == v.y && f.z == v.z;
}
template <typename T>
inline vec3<T> mini(vec3<T> a, vec3<T> b) {
    return vec3<T>(mini<T>(a.x, b.x), mini<T>(a.y, b.y), mini<T>(a.z, b.z));
}
template <typename T>
inline vec3<T> maxi(vec3<T> a, vec3<T> b) {
    return vec3<T>(maxi<T>(a.x, b.x), maxi<T>(a.y, b.y), maxi<T>(a.z, b.z));
}
template <typename T>
inline vec3<T> floor(vec3<T> a) {
    return vec3<T>(floor<T>(a.x), floor<T>(a.y), floor<T>(a.z));
}
template <typename T>
inline vec3<T> ceil(vec3<T> a) {
    return vec3<T>(ceil<T>(a.x), ceil<T>(a.y), ceil<T>(a.z));
}
template <typename T>
inline vec2<T> abs(vec2<T> a) {
    return vec2<T>(abs<T>(a.x), abs<T>(a.y));
}
template <typename T>
inline vec3<T> abs(vec3<T> a) {
    return vec3<T>(abs<T>(a.x), abs<T>(a.y), abs<T>(a.z));
}
template <typename T>
inline T dotS(vec3<T> a, vec3<T> b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
template <typename T>
inline vec3<T> cCross(vec3<T> a, vec3<T> b) {
    return vec3<T>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
template <typename T>
inline vec3<T> cReflect(vec3<T> I, vec3<T> N) {
    return I - (T)2 * dotS(N, I) * N;
}
using dvec3 = vec3<double>;
using fvec3 = vec3<float>;
using bvec3 = vec3<bool>;
using ivec3 = vec3<int>;
using i8vec3 = vec3<int8_t>;
using i16vec3 = vec3<int16_t>;
using ivec3 = vec3<int32_t>;
using i32vec3 = vec3<int32_t>;
using i64vec3 = vec3<int64_t>;
using u8vec3 = vec3<uint8_t>;
using u16vec3 = vec3<uint16_t>;
using uvec3 = vec3<uint32_t>;
using u32vec3 = vec3<uint32_t>;
using u64vec3 = vec3<uint64_t>;

// specialization for float32 test to fvec3
CTOOLS_API inline bool valid(const fvec3& a) {
    return floatIsValid(a.x) && floatIsValid(a.y) && floatIsValid(a.z);
}
// specialization for fvec3
CTOOLS_API inline bool operator==(const fvec3& v, const fvec3& f) {
    return IS_FLOAT_EQUAL(f.x, v.x) && IS_FLOAT_EQUAL(f.y, v.y) && IS_FLOAT_EQUAL(f.z, v.z);
}
CTOOLS_API inline bool operator!=(const fvec3& v, const fvec3& f) {
    return IS_FLOAT_DIFFERENT(f.x, v.x) || IS_FLOAT_DIFFERENT(f.y, v.y) || IS_FLOAT_DIFFERENT(f.z, v.z);
}

/////////////////////////////////////////////////////////////////////////

template <typename T>
struct vec4 {
    T x = (T)0, y = (T)0, z = (T)0, w = (T)0;
    vec4() : x((T)0), y((T)0), z((T)0), w((T)0) {
    }
    template <typename U>
    vec4<T>(vec4<U> a) {
        x = (T)a.x;
        y = (T)a.y;
        z = (T)a.z;
        w = (T)a.w;
    }
    vec4(vec2<T> xy, vec2<T> zw) : x(xy.x), y(xy.y), z(zw.x), w(zw.y) {
    }
    vec4(vec3<T> xyz, float w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {
    }
    vec4(T xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {
    }
    vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {
    }
    vec4(std::string vec, char c = ';', vec4<T>* def = nullptr)  // may be in format "0.2f,0.3f,0.4f,0.8f"
    {
        if (def) {
            x = def->x;
            y = def->y;
            z = def->z;
            w = def->w;
        }
        std::vector<T> result = StringToNumberVector<T>(vec, c);
        const size_t s = result.size();
        if (s > 0)
            x = result[0];
        if (s > 1)
            y = result[1];
        if (s > 2)
            z = result[2];
        if (s > 3)
            w = result[3];
    }
    vec4(std::string vec, char c = ';', int n = 4, vec4<T>* def = nullptr)  // may be in format "0.2f,0.3f,0.4f,0.8f"
    {
        if (def) {
            x = def->x;
            y = def->y;
            z = def->z;
            w = def->w;
        } else {
            x = (T)0;
            y = (T)0;
            z = (T)0;
            w = (T)0;
        }
        std::vector<T> result = StringToNumberVector<T>(vec, c);
        const size_t s = result.size();
        if ((int)s != n) {
            if (s == 1) {
                x = result[0];
                y = result[0];
                z = result[0];
                w = result[0];
            } else if (s == 2) {
                x = result[0];
                y = result[0];
                z = result[1];
                w = result[1];
            } else if (s == 3) {
                x = result[0];
                y = result[1];
                z = result[2];
            }
        } else {
            if (s > 0)
                x = result[0];
            if (s > 1)
                y = result[1];
            if (s > 2)
                z = result[2];
            if (s > 3)
                w = result[3];
        }
    }
    T& operator[](const size_t& i) {
        return (&x)[i];
    }
    vec4<T> Offset(const T& vX, const T& vY, const T& vZ, const T& vW) const {
        return vec4<T>(x + vX, y + vY, z + vZ, w + vW);
    }
    void Set(const T& vX, const T& vY, const T& vZ, const T& vW) {
        x = vX;
        y = vY;
        z = vZ;
        w = vW;
    }
    vec4<T> operator-() const {
        return vec4<T>(-x, -y, -z, -w);
    }
    vec4<T> operator!() const {
        return vec4<T>(!(bool)x, !(bool)y, !(bool)z, !(bool)w);
    }
    vec2<T> xy() const {
        return vec2<T>(x, y);
    }
    vec3<T> xyz() const {
        return vec3<T>(x, y, z);
    }
    vec2<T> zw() const {
        return vec2<T>(z, w);
    }
    // https://en.cppreference.com/w/cpp/language/operator_incdec
    vec4<T>& operator++() {
        ++x;
        ++y;
        ++z;
        ++w;
        return *this;
    }  // pre inc
    vec4<T>& operator--() {
        --x;
        --y;
        --z;
        --w;
        return *this;
    }  // pre dec
    vec4<T> operator++(int) {
        vec4<T> tmp = *this;
        ++*this;
        return tmp;
    }  // post inc
    vec4<T> operator--(int) {
        vec4<T> tmp = *this;
        --*this;
        return tmp;
    }  // post dec
    void operator+=(const T& a) {
        x += a;
        y += a;
        z += a;
        w += a;
    }
    void operator+=(const vec4<T>& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
    }
    void operator-=(const T& a) {
        x -= a;
        y -= a;
        z -= a;
        w -= a;
    }
    void operator-=(const vec4<T>& v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
    }
    bool operator==(const T& a) {
        return (x == a) && (y == a) && (z == a) && (w == a);
    }
    bool operator==(const vec4<T>& v) {
        return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
    }
    bool operator!=(const T& a) {
        return (x != a) || (y != a) || (z != a) || (w != a);
    }
    bool operator!=(const vec4<T>& v) {
        return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
    }
    void operator*=(const T& a) {
        x *= a;
        y *= a;
        z *= a;
        w *= a;
    }
    void operator*=(const vec4<T>& v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
    }
    void operator/=(const T& a) {
        x /= a;
        y /= a;
        z /= a;
        w /= a;
    }
    void operator/=(const vec4<T>& v) {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
    }
    vec2<T> SizeLBRT() const {
        return vec2<T>(z - x, w - y);
    }  // Considere vec4 as a rect with LBRT for have size LBRT Mean => x = Left, y = Bottom, z = Right, w = Top
    vec2<T> pos() const {
        return xy();
    }
    vec2<T> size() const {
        return zw();
    }
    T length() const {
        return (T)sqrt(lengthSquared());
    }
    T lengthSquared() const {
        return x * x + y * y + z * z + w * w;
    }
    T normalize() {
        T _length = length();
        if (_length < (T)1e-5)
            return (T)0;
        T _invLength = (T)1 / _length;
        x *= _invLength;
        y *= _invLength;
        z *= _invLength;
        w *= _invLength;
        return _length;
    }
    vec4<T> GetNormalized() const {
        vec4<T> n = vec4<T>(x, y, z, w);
        n.normalize();
        return n;
    }
    bool emptyAND() const {
        return x == (T)0 && y == (T)0 && z == (T)0 && w == (T)0;
    }
    bool emptyOR() const {
        return x == (T)0 || y == (T)0 || z == (T)0 || w == (T)0;
    }
    T sum() const {
        return x + y + z + w;
    }
    T sumAbs() const {
        return abs<T>(x) + abs<T>(y) + abs<T>(z) + abs<T>(w);
    }
    std::string string(char c = ';') const {
        return toStr(x) + c + toStr(y) + c + toStr(z) + c + toStr(w);
    }
    T mini() const {
        return internal_mini<T>(x, internal_mini<T>(y, internal_mini<T>(z, w)));
    }
    T maxi() const {
        return internal_maxi<T>(x, internal_maxi<T>(y, internal_maxi<T>(z, w)));
    }
};

// https://en.cppreference.com/w/cpp/language/operator_incdec
template <typename T>
inline vec4<T>& operator++(vec4<T>& v) {
    ++v;
    return v;
}  // pre inc
template <typename T>
inline vec4<T>& operator--(vec4<T>& v) {
    --v;
    return v;
}  // pre dec
template <typename T>
inline vec4<T> operator++(vec4<T>& v, int) {
    vec4<T> a = v;
    ++a;
    return a;
}  // post inc
template <typename T>
inline vec4<T> operator--(vec4<T>& v, int) {
    vec4<T> a = v;
    --a;
    return a;
}  // post dec
template <typename T>
inline vec4<T> operator+(vec4<T> v, T f) {
    return vec4<T>(v.x + f, v.y + f, v.z + f, v.w + f);
}
template <typename T>
inline vec4<T> operator+(vec4<T> v, vec4<T> f) {
    return vec4<T>(v.x + f.x, v.y + f.y, v.z + f.z, v.w + f.w);
}
template <typename T>
inline vec4<T> operator-(vec4<T> v, T f) {
    return vec4<T>(v.x - f, v.y - f, v.z - f, v.w - f);
}
template <typename T>
inline vec4<T> operator-(T f, vec4<T> v) {
    return vec4<T>(f - v.x, f - v.y, f - v.z, f - v.w);
}
template <typename T>
inline vec4<T> operator-(vec4<T> v, vec4<T> f) {
    return vec4<T>(v.x - f.x, v.y - f.y, v.z - f.z, v.w - f.w);
}
template <typename T>
inline vec4<T> operator*(vec4<T> v, T f) {
    return vec4<T>(v.x * f, v.y * f, v.z * f, v.w * f);
}
template <typename T>
inline vec4<T> operator*(vec4<T> v, vec4<T> f) {
    return vec4<T>(v.x * f.x, v.y * f.y, v.z * f.z, v.w * f.w);
}
template <typename T>
inline vec4<T> operator/(vec4<T> v, T f) {
    return vec4<T>(v.x / f, v.y / f, v.z / f, v.w / f);
}
template <typename T>
inline vec4<T> operator/(vec4<T> v, vec4<T> f) {
    return vec4<T>(v.x / f.x, v.y / f.y, v.z / f.z, v.w / f.w);
}
template <typename T>
inline bool operator<(vec4<T> v, vec4<T> f) {
    return v.x < f.x && v.y < f.y && v.z < f.z && v.w < f.w;
}
template <typename T>
inline bool operator<(vec4<T> v, T f) {
    return v.x < f && v.y < f && v.z < f && v.w < f;
}
template <typename T>
inline bool operator>(vec4<T> v, vec4<T> f) {
    return v.x > f.x && v.y > f.y && v.z > f.z && v.w > f.w;
}
template <typename T>
inline bool operator>(vec4<T> v, T f) {
    return v.x > f && v.y > f && v.z > f && v.w > f;
}
template <typename T>
inline bool operator<=(vec4<T> v, vec4<T> f) {
    return v.x <= f.x && v.y <= f.y && v.z <= f.z && v.w <= f.w;
}
template <typename T>
inline bool operator<=(vec4<T> v, T f) {
    return v.x <= f && v.y <= f && v.z <= f && v.w <= f;
}
template <typename T>
inline bool operator>=(vec4<T> v, vec4<T> f) {
    return v.x >= f.x && v.y >= f.y && v.z >= f.z && v.w >= f.w;
}
template <typename T>
inline bool operator>=(vec4<T> v, T f) {
    return v.x >= f && v.y >= f && v.z >= f && v.w >= f;
}
template <typename T>
inline bool operator==(vec4<T> v, vec4<T> f) {
    return f.x == v.x && f.y == v.y && f.z == v.z && f.w == v.w;
}
template <typename T>
inline bool operator!=(vec4<T> v, vec4<T> f) {
    return f.x != v.x || f.y != v.y || f.z != v.z || f.w != v.w;
}
template <typename T>
inline vec4<T> mini(vec4<T> a, vec4<T> b) {
    return vec4<T>(mini<T>(a.x, b.x), mini<T>(a.y, b.y), mini<T>(a.z, b.z), mini<T>(a.w, b.w));
}
template <typename T>
inline vec4<T> maxi(vec4<T> a, vec4<T> b) {
    return vec4<T>(maxi<T>(a.x, b.x), maxi<T>(a.y, b.y), maxi<T>(a.z, b.z), maxi<T>(a.w, b.w));
}
template <typename T>
inline vec4<T> floor(vec4<T> a) {
    return vec4<T>(floor<T>(a.x), floor<T>(a.y), floor<T>(a.z), floor<T>(a.w));
}
template <typename T>
inline vec4<T> ceil(vec4<T> a) {
    return vec4<T>(ceil<T>(a.x), ceil<T>(a.y), ceil<T>(a.z), ceil<T>(a.w));
}
template <typename T>
inline vec4<T> abs(vec4<T> a) {
    return vec4<T>(abs<T>(a.x), abs<T>(a.y), abs<T>(a.z), abs<T>(a.w));
}
template <typename T>
inline vec4<T> sign(vec4<T> a) {
    return vec4<T>(a.x < (T)0 ? (T)-1 : (T)1, a.y < (T)0 ? (T)-1 : 1, a.z < (T)0 ? (T)-1 : (T)1, a.w < (T)0 ? (T)-1 : (T)1);
}
template <typename T>
inline vec4<T> sin(vec4<T> a) {
    return vec4<T>(sin<T>(a.x), sin<T>(a.y), sin<T>(a.z), sin<T>(a.w));
}
template <typename T>
inline vec4<T> cos(vec4<T> a) {
    return vec4<T>(cos<T>(a.x), cos<T>(a.y), cos<T>(a.z), cos<T>(a.w));
}
template <typename T>
inline vec4<T> tan(vec4<T> a) {
    return vec4<T>(tan<T>(a.x), tan<T>(a.y), tan<T>(a.z), tan<T>(a.w));
}
using dvec4 = vec4<double>;
using fvec4 = vec4<float>;
using bvec4 = vec4<bool>;
using ivec4 = vec4<int>;
using i8vec4 = vec4<int8_t>;
using i16vec4 = vec4<int16_t>;
using ivec4 = vec4<int32_t>;
using i32vec4 = vec4<int32_t>;
using i64vec4 = vec4<int64_t>;
using u8vec4 = vec4<uint8_t>;
using u16vec4 = vec4<uint16_t>;
using uvec4 = vec4<uint32_t>;
using u32vec4 = vec4<uint32_t>;
using u64vec4 = vec4<uint64_t>;

// specialization for float32 test to fvec4
inline bool valid(const fvec4& a) {
    return floatIsValid(a.x) && floatIsValid(a.y) && floatIsValid(a.z) && floatIsValid(a.w);
}

/////////////////////////////////////////////////////////////////////////
template <typename T>
struct rect  // bottom left to top right
{
    T x, y, w, h;
    T left, right, top, bottom;

    rect() {
        setRect((T)0, (T)0, (T)0, (T)0);
    }
    rect(T vX, T vY, T vW, T vH) {
        setRect(vX, vY, vW, vH);
    }
    rect(vec2<T> xy, vec2<T> zw) {
        setRect(xy.x, xy.y, zw.x, zw.y);
    }
    void setRect(vec2<T> xy, vec2<T> zw) {
        setRect(xy.x, xy.y, zw.x, zw.y);
    }
    void setRect(T vX, T vY, T vW, T vH) {
        x = vX;
        y = vY;
        w = vW;
        h = vH;
        left = vX;
        right = vX + vW;
        top = vY + vH;
        bottom = vY;
    }
    vec2<T> rightBottom() const {
        return vec2<T>(right, bottom);
    }
    vec2<T> rightTop() const {
        return vec2<T>(right, top);
    }
    vec2<T> leftBottom() const {
        return vec2<T>(left, bottom);
    }
    vec2<T> leftTop() const {
        return vec2<T>(left, top);
    }
    vec2<T> center() const {
        return vec2<T>((left + right) / (T)2, (top + bottom) / (T)2);
    }
    std::array<vec2<T>, 4> vertices() {
        std::array<vec2<T>, 4> buf;
        buf[0] = leftBottom();
        buf[1] = leftTop();
        buf[2] = rightTop();
        buf[3] = rightBottom();
        return buf;
    }
    std::array<vec2<T>, 4> texCoords(T scaleX, T scaleY) {
        std::array<vec2<T>, 4> buf;
        buf[0] = vec2<T>((T)0, (T)0);
        buf[1] = vec2<T>((T)scaleX, (T)0);
        buf[2] = vec2<T>(scaleX, scaleY);
        buf[3] = vec2<T>((T)0, scaleY);
        return buf;
    }
    void setWidth(T vw) {
        w = vw;
    }
    void setHeight(T vh) {
        h = vh;
    }
    void SnackLeft(T vleft) {
        x = vleft;
        w -= vleft;
        left = x;
    }
    void SnackRight(T vright) {
        w -= vright;
        right = w + x;
    }
    void SnackTop(T vtop) {
        h -= vtop;
        top = h + y;
    }
    void SnackBottom(T vbottom) {
        y = vbottom;
        h -= vbottom;
        bottom = y;
    }
    bool IsContainPoint(vec2<T> pt) {
        if (pt.x > left)
            if (pt.x < right)
                if (pt.y > bottom)
                    if (pt.y < top)
                        return true;
        return false;
    }
    bool IsIntersectedByLine(vec2<T> v0, vec2<T> v1)  // only for axis aligned box
    {
        // https://stackoverflow.com/a/18292964/3904977
        if ((v0.x <= left && v1.x <= left) || (v0.y <= bottom && v1.y <= bottom) || (v0.x >= right && v1.x >= right) || (v0.y >= top && v1.y >= top))
            return false;  // Completely outside.
        if (IS_FLOAT_EQUAL(v1.y, v0.y) && IS_FLOAT_EQUAL(v1.x, v0.x))
            return true;
        if (IS_FLOAT_DIFFERENT(v1.x, v0.x))  // avoid div by zero
        {
            float _m = (v1.y - v0.y) / (v1.x - v0.x);
            float _y = _m * (left - v0.x) + v0.y;
            if (_y >= bottom && _y <= top)
                return true;
            _y = _m * (right - v0.x) + v0.y;
            if (_y >= bottom && _y <= top)
                return true;
            if (IS_FLOAT_DIFFERENT(_m, 0.0f))  // avoid div by zero
            {
                float _x = (bottom - v0.y) / _m + v0.x;
                if (_x >= left && _x <= right)
                    return true;
                _x = (top - v0.y) / _m + v0.x;
                if (_x >= left && _x <= right)
                    return true;
            }
        }
        return false;
    }
    bool IsIntersectedByCircle(vec2<T> vPos, T vRadius)  // only for axis aligned box
    {
        T d = maxi<T>(abs<T>(center() - vPos) - Size() / (T)2, (T)0).lengthSquared();
        return d < vRadius * vRadius;
    }
    vec2<T> Size() {
        return vec2<T>(w, h);
    }
};
typedef rect<int> irect;
typedef rect<double> drect;
typedef rect<float> frect;

template <typename T>
inline rect<T> floor(const rect<T>& a) {
    return rect<T>(floor<T>(a.x), floor<T>(a.y), floor<T>(a.w), floor<T>(a.h));
}
template <typename T>
inline rect<T> ceil(const rect<T>& a) {
    return rect<T>(ceil<T>(a.x), ceil<T>(a.y), ceil<T>(a.w), ceil<T>(a.h));
}

template <typename T>
inline bool operator==(rect<T> v, rect<T> f) {
    return f.x == v.x && f.y == v.y && f.w == v.w && f.h == v.h;
}
template <typename T>
inline bool operator!=(rect<T> v, rect<T> f) {
    return f.x != v.x || f.y != v.y || f.w != v.w || f.h != v.h;
}

/////////////////////////////////////////////////////////////////////////
//// PLANE //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

template <typename T>
class plane {
public:
    vec3<T> n;
    T d;

public:
    plane() = default;
    plane(vec3<T> vp) : n(vp.GetNormalized()), d(dotS(vp, n)) {
    }
    plane(vec3<T> vp, vec3<T> vn) : n(vn), d(dotS(vp, n)) {
    }
    plane(vec3<T> a, vec3<T> b, vec3<T> c) {
        auto AB = b - a;
        auto AC = c - a;
        n = cCross(AC, AB).GetNormalized();
        d = dotS(a, n);
    }
    plane(vec3<T> vn, double vd) : n(vn), d(vd) {
    }
};

typedef plane<double> dplane;
typedef plane<float> fplane;

template <typename T>
inline bool get_plane_intersection(const plane<T>& a, const plane<T>& b, const plane<T>& c, vec3<T>& out_res) {
    vec3<T> m1 = vec3<T>(a.n.x, b.n.x, c.n.x);
    vec3<T> m2 = vec3<T>(a.n.y, b.n.y, c.n.y);
    vec3<T> m3 = vec3<T>(a.n.z, b.n.z, c.n.z);
    vec3<T> d = vec3<T>(a.d, b.d, c.d);

    vec3<T> u = cCross<T>(m2, m3);
    T denom = dotS<T>(m1, u);

    if (fabs(denom) < std::numeric_limits<T>::epsilon()) {
        // Planes don't actually intersect in a point
        // Throw exception maybe?
        return false;
    }

    vec3<T> v = cCross<T>(m1, d);
    out_res.x = dotS<T>(d, u) / denom;
    out_res.y = dotS<T>(m3, v) / denom;
    out_res.z = -dotS<T>(m2, v) / denom;

    return true;
}

template <typename T>
inline bool is_on_plane(const plane<T>& pln, const vec3<T>& p) {
    return (fabs(dotS<T>(pln.n, p) - pln.d) < std::numeric_limits<T>::epsilon());
}

/////////////////////////////////////////////////////////////
///////// BUFFERS ///////////////////////////////////////////
/////////////////////////////////////////////////////////////

CTOOLS_API void SetBuffer(char* vBuffer, size_t vBufferLen, const std::string& vStr);
CTOOLS_API void AppendToBuffer(char* vBuffer, size_t vBufferLen, const std::string& vStr);
CTOOLS_API void ResetBuffer(char* vBuffer);

/////////////////////////////////////////////////////////////
///////// AABB //////////////////////////////////////////////
/////////////////////////////////////////////////////////////

template <typename T>
struct AABB  // copy of b2AABB struct
{
    vec2<T> lowerBound;  ///< the lower left vertex
    vec2<T> upperBound;  ///< the upper right vertex

    AABB() : lowerBound((T)0), upperBound((T)0) {
    }
    AABB(vec2<T> vlowerBound, vec2<T> vUpperBound) : lowerBound(vlowerBound), upperBound(vUpperBound) {
    }
    AABB(vec4<T> vVec4)
    //: lowerBound(vlowerBound), upperBound(vUpperBound)
    {
        lowerBound.x = vVec4.x;
        lowerBound.y = vVec4.y;
        upperBound.x = vVec4.z;
        upperBound.y = vVec4.w;
    }
    AABB(std::string vec, char c)  // may be in format "0.2f,0.3f,0.4f,0.8f" left, bottom, right, top
    {
        std::vector<float> result = StringToNumberVector<float>(vec, c);
        const size_t s = result.size();
        if (s > 0)
            lowerBound.x = result[0];
        if (s > 1)
            lowerBound.y = result[1];
        if (s > 2)
            upperBound.x = result[2];
        if (s > 3)
            upperBound.y = result[3];
    }

#ifdef COCOS2D
    AABB(cocos2d::Rect rect) : lowerBound(rect.origin), upperBound(lowerBound + rect.size) {
    }
#endif

#ifdef USE_BOX2D
    AABB(const b2AABB& aabb) : lowerBound(aabb.lowerBound), upperBound(aabb.upperBound) {
    }
#endif

    /// Verify that the bounds are sorted.
    // bool IsValid() const;

    /// Add a vector to this vector.
    void operator+=(const vec2<T>& v) {
        lowerBound += v;
        upperBound += v;
    }

    /// Subtract a vector from this vector.
    void operator-=(const vec2<T>& v) {
        lowerBound -= v;
        upperBound -= v;
    }

    /// Multiply this vector by a scalar.
    void operator*=(T a) {
        lowerBound *= a;
        upperBound *= a;
    }

    /// Divide this vector by a scalar.
    void operator/=(T a) {
        lowerBound /= a;
        upperBound /= a;
    }

    /// Get the center of the AABB.
    vec2<T> GetCenter() const {
        return (lowerBound + upperBound) / (T)2;
    }

    /// Get the extents of the AABB (half-widths).
    vec2<T> GetExtents() const {
        return (upperBound - lowerBound) / (T)2;
    }

    /// Get the perimeter length
    T GetPerimeter() const {
        const float wx = upperBound.x - lowerBound.x;
        const float wy = upperBound.y - lowerBound.y;
        return (T)2 * (wx + wy);
    }

    /// Combine an AABB into this one.
    void Combine(const AABB<T>& aabb) {
        lowerBound = mini(lowerBound, aabb.lowerBound);
        upperBound = maxi(upperBound, aabb.upperBound);
    }

    /// Combine two AABBs into this one.
    void Combine(const AABB<T>& aabb1, const AABB<T>& aabb2) {
        lowerBound = mini(aabb1.lowerBound, aabb2.lowerBound);
        upperBound = maxi(aabb1.upperBound, aabb2.upperBound);
    }

    /// Combine a point into this one.
    void Combine(const vec2<T>& pt) {
        lowerBound.x = mini(lowerBound.x, pt.x);
        lowerBound.y = mini(lowerBound.y, pt.y);
        upperBound.x = maxi(upperBound.x, pt.x);
        upperBound.y = maxi(upperBound.y, pt.y);
    }

    /// Set vlowerBound at mini and vUpperBound at maxi
    void Set(vec2<T> vlowerBound, vec2<T> vUpperBound) {
        lowerBound.x = mini(vlowerBound.x, vUpperBound.x);
        lowerBound.y = mini(vlowerBound.y, vUpperBound.y);
        upperBound.x = maxi(vlowerBound.x, vUpperBound.x);
        upperBound.y = maxi(vlowerBound.y, vUpperBound.y);
    }

    /// Does this aabb contain the provided AABB.
    bool Contains(const AABB<T>& aabb) const {
        bool result = true;
        result &= lowerBound.x <= aabb.lowerBound.x;
        result &= lowerBound.y <= aabb.lowerBound.y;
        result &= aabb.upperBound.x <= upperBound.x;
        result &= aabb.upperBound.y <= upperBound.y;
        return result;
    }

    /// Does this aabb contain the provided vec2<T>.
    bool ContainsPoint(const vec2<T>& pt) const {
        bool result = true;
        result &= lowerBound.x <= pt.x;
        result &= lowerBound.y <= pt.y;
        result &= pt.x <= upperBound.x;
        result &= pt.y <= upperBound.y;
        return result;
    }

    bool Intersects(const AABB<T>& other) {
        bool result = true;
        result |= lowerBound.x <= other.lowerBound.x;
        result |= lowerBound.y <= other.lowerBound.y;
        result |= other.upperBound.x <= upperBound.x;
        result |= other.upperBound.y <= upperBound.y;
        return result;
    }
#ifdef USE_BOX2D
    b2AABB Tob2AABB() {
        b2AABB v;
        v.lowerBound = lowerBound.Tob2Vec2();
        v.upperBound = upperBound.Tob2Vec2();
        return v;
    }
#endif
    vec2<T> Size() {
        return vec2<T>(upperBound - lowerBound);
    }
};
typedef AABB<int> iAABB;
typedef AABB<double> dAABB;
typedef AABB<float> fAABB;

/// Add a float to a AABB.
template <typename T>
inline AABB<T> operator+(const AABB<T>& v, float f) {
    return AABB<T>(v.lowerBound + f, v.upperBound + f);
}

/// Add a AABB to a AABB.
template <typename T>
inline AABB<T> operator+(const AABB<T>& v, AABB<T> f) {
    return AABB<T>(v.lowerBound + f.lowerBound, v.upperBound + f.upperBound);
}

/// Substract a float from a AABB.
template <typename T>
inline AABB<T> operator-(const AABB<T>& v, float f) {
    return AABB<T>(v.lowerBound - f, v.upperBound - f);
}

/// Substract a AABB to a AABB.
template <typename T>
inline AABB<T> operator-(const AABB<T>& v, AABB<T> f) {
    return AABB<T>(v.lowerBound - f.lowerBound, v.upperBound - f.upperBound);
}

/// Multiply a float with a AABB.
template <typename T>
inline AABB<T> operator*(const AABB<T>& v, float f) {
    return AABB<T>(v.lowerBound * f, v.upperBound * f);
}

/// Multiply a AABB with a AABB.
template <typename T>
inline AABB<T> operator*(const AABB<T>& v, AABB<T> f) {
    return AABB<T>(v.lowerBound * f.lowerBound, v.upperBound * f.upperBound);
}

/// Divide a AABB by a float.
template <typename T>
inline AABB<T> operator/(const AABB<T>& v, float f) {
    return AABB<T>(v.lowerBound / f, v.upperBound / f);
}

/// Divide a AABB by a float.
template <typename T>
inline AABB<T> operator/(AABB<T>& v, float f) {
    return AABB<T>(v.lowerBound / f, v.upperBound / f);
}

/// Divide a AABB by a AABB.
template <typename T>
inline AABB<T> operator/(const AABB<T>& v, AABB<T> f) {
    return AABB<T>(v.lowerBound / f.lowerBound, v.upperBound / f.upperBound);
}

template <typename T>
inline vec4<T> vecFromAABB(AABB<T> aabb) {
    return vec4<T>(aabb.lowerBound.x, aabb.lowerBound.y, aabb.upperBound.x, aabb.upperBound.y);
}

/////////////////////////////////////////////////////////////
///////// AABBCC // version 3d de AABBCC/////////////////////
/////////////////////////////////////////////////////////////

template <typename T>
struct AABBCC  // copy of b2AABB struct
{
    vec3<T> lowerBound;  ///< the lower left vertex
    vec3<T> upperBound;  ///< the upper right vertex

    AABBCC() : lowerBound((T)0), upperBound((T)0) {
    }
    AABBCC(vec3<T> vlowerBound, vec3<T> vUpperBound)
    //: lowerBound(vlowerBound), upperBound(vUpperBound)
    {
        lowerBound.x = mini(vlowerBound.x, vUpperBound.x);
        lowerBound.y = mini(vlowerBound.y, vUpperBound.y);
        lowerBound.z = mini(vlowerBound.z, vUpperBound.z);
        upperBound.x = maxi(vlowerBound.x, vUpperBound.x);
        upperBound.y = maxi(vlowerBound.y, vUpperBound.y);
        upperBound.z = maxi(vlowerBound.z, vUpperBound.z);
    }

    /// Verify that the bounds are sorted.
    // bool IsValid() const;

    /// Add a vector to this vector.
    void operator+=(const vec3<T>& v) {
        lowerBound += v;
        upperBound += v;
    }

    /// Subtract a vector from this vector.
    void operator-=(const vec3<T>& v) {
        lowerBound -= v;
        upperBound -= v;
    }

    /// Multiply this vector by a scalar.
    void operator*=(T a) {
        lowerBound *= a;
        upperBound *= a;
    }

    /// Divide this vector by a scalar.
    void operator/=(T a) {
        lowerBound /= a;
        upperBound /= a;
    }

    /// Get the center of the AABB.
    vec3<T> GetCenter() const {
        return (lowerBound + upperBound) / (T)2;
    }

    /// Get the extents of the AABB (half-widths).
    vec3<T> GetExtents() const {
        return (upperBound - lowerBound) / (T)2;
    }

    /// Get the perimeter length
    T GetPerimeter() const {
        const float wx = upperBound.x - lowerBound.x;
        const float wy = upperBound.y - lowerBound.y;
        const float wz = upperBound.z - lowerBound.z;
        return (T)2 * (wx + wy + wz);
    }

    /// Combine an AABB into this one.
    void Combine(const AABBCC<T>& aabb) {
        lowerBound = mini(lowerBound, aabb.lowerBound);
        upperBound = maxi(upperBound, aabb.upperBound);
    }

    /// Combine two AABBs into this one.
    void Combine(const AABBCC<T>& aabb1, const AABBCC<T>& aabb2) {
        lowerBound = mini(aabb1.lowerBound, aabb2.lowerBound);
        upperBound = maxi(aabb1.upperBound, aabb2.upperBound);
    }

    /// Combine a point into this one.
    void Combine(const vec3<T>& pt) {
        lowerBound.x = mini(lowerBound.x, pt.x);
        lowerBound.y = mini(lowerBound.y, pt.y);
        lowerBound.z = mini(lowerBound.z, pt.z);
        upperBound.x = maxi(upperBound.x, pt.x);
        upperBound.y = maxi(upperBound.y, pt.y);
        upperBound.z = maxi(upperBound.z, pt.z);
    }

    /// Does this aabb contain the provided AABB.
    bool Contains(const AABBCC<T>& aabb) const {
        bool result = true;
        result &= lowerBound.x <= aabb.lowerBound.x;
        result &= lowerBound.y <= aabb.lowerBound.y;
        result &= lowerBound.z <= aabb.lowerBound.z;
        result &= aabb.upperBound.x <= upperBound.x;
        result &= aabb.upperBound.y <= upperBound.y;
        result &= aabb.upperBound.z <= upperBound.z;
        return result;
    }

    /// Does this aabb contain the provided vec2<T>.
    bool ContainsPoint(const vec3<T>& pt) const {
        bool result = true;
        result &= lowerBound.x <= pt.x;
        result &= lowerBound.y <= pt.y;
        result &= lowerBound.z <= pt.z;
        result &= pt.x <= upperBound.x;
        result &= pt.y <= upperBound.y;
        result &= pt.z <= upperBound.z;
        return result;
    }

    bool Intersects(const AABBCC<T>& other) const {
        bool result = true;
        result |= lowerBound.x <= other.lowerBound.x;
        result |= lowerBound.y <= other.lowerBound.y;
        result |= lowerBound.z <= other.lowerBound.z;
        result |= other.upperBound.x <= upperBound.x;
        result |= other.upperBound.y <= upperBound.y;
        result |= other.upperBound.z <= upperBound.z;
        return result;
    }

    const vec3<T> Size() const {
        return vec3<T>(upperBound - lowerBound);
    }
};
typedef AABBCC<double> dAABBCC;
typedef AABBCC<float> fAABBCC;

/// Add a float to a AABBCC<T>.
template <typename T>
inline AABBCC<T> operator+(const AABBCC<T>& v, float f) {
    return AABBCC<T>(v.lowerBound + f, v.upperBound + f);
}

/// Add a AABBCC<T> to a AABBCC<T>.
template <typename T>
inline AABBCC<T> operator+(const AABBCC<T>& v, AABBCC<T> f) {
    return AABBCC<T>(v.lowerBound + f.lowerBound, v.upperBound + f.upperBound);
}

/// Substract a float from a AABBCC<T>.
template <typename T>
inline AABBCC<T> operator-(const AABBCC<T>& v, float f) {
    return AABBCC<T>(v.lowerBound - f, v.upperBound - f);
}

/// Substract a AABBCC<T> to a AABBCC<T>.
template <typename T>
inline AABBCC<T> operator-(const AABBCC<T>& v, AABBCC<T> f) {
    return AABBCC<T>(v.lowerBound - f.lowerBound, v.upperBound - f.upperBound);
}

/// Multiply a float with a AABBCC<T>.
template <typename T>
inline AABBCC<T> operator*(const AABBCC<T>& v, float f) {
    return AABBCC<T>(v.lowerBound * f, v.upperBound * f);
}

/// Multiply a AABBCC<T> with a AABBCC<T>.
template <typename T>
inline AABBCC<T> operator*(const AABBCC<T>& v, AABBCC<T> f) {
    return AABBCC<T>(v.lowerBound * f.lowerBound, v.upperBound * f.upperBound);
}

/// Divide a AABBCC<T> by a float.
template <typename T>
inline AABBCC<T> operator/(const AABBCC<T>& v, float f) {
    return AABBCC<T>(v.lowerBound / f, v.upperBound / f);
}

/// Divide a AABBCC<T> by a float.
template <typename T>
inline AABBCC<T> operator/(AABBCC<T>& v, float f) {
    return AABBCC<T>(v.lowerBound / f, v.upperBound / f);
}

/// Divide a AABBCC<T> by a AABBCC<T>.
template <typename T>
inline AABBCC<T> operator/(const AABBCC<T>& v, AABBCC<T> f) {
    return AABBCC<T>(v.lowerBound / f.lowerBound, v.upperBound / f.upperBound);
}

/////////////////////////////////////////////////////////////
///////// QUATERNIONS ///////////////////////////////////////
/////////////////////////////////////////////////////////////

template <typename T>
struct quat {
    // x,y,z => axis
    // w => angle
    T x, y, z, w;
    quat() : x((T)0), y((T)0), z((T)0), w((T)1) {
    }
    quat(T xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {
    }
    quat(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {
    }
    T getTx() {
        return x * w;
    }
    T getTy() {
        return y * w;
    }
    T getTz() {
        return z * w;
    }
    void add(const quat<T>& vQuat) {
        x += vQuat.x;
        y += vQuat.y;
        z += vQuat.z;
        w += vQuat.w;
    }
    void sub(const quat<T>& vQuat) {
        x -= vQuat.x;
        y -= vQuat.y;
        z -= vQuat.z;
        w -= vQuat.w;
    }
    void mul(const quat<T>& vQuat) {
        const T tx = x, ty = y, tz = z, tw = w;
        x = tx * vQuat.w + ty * vQuat.z - tz * vQuat.y + tw * vQuat.x;
        y = -tx * vQuat.z + ty * vQuat.w + tz * vQuat.x + tw * vQuat.y;
        z = tx * vQuat.y - ty * vQuat.x + tz * vQuat.w + tw * vQuat.z;
        w = -tx * vQuat.x - ty * vQuat.y - tz * vQuat.z + tw * vQuat.w;
    }
    void conjugate(const quat<T>& vQuat) {
        x = -vQuat.x;
        y = -vQuat.y;
        z = -vQuat.z;
        w = vQuat.w;
    }
    void normalize() {
        assert(0);  // not supported by other types thant float and double
    }
    void scale(T s) {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
    }
};
typedef quat<float> fquat;
typedef quat<double> dquat;

/////////////////////////////////////////////////////////////
///////// variant //////////////////////////////////////////
/////////////////////////////////////////////////////////////
template <typename T>
class variant {
private:
    std::string inputtype;  // type of input data
    std::string datatype;   // real type corresponding to the data

    std::string string_value;
    bool bool_value = false;
    int int_value = 0;
    float float_value = 0.0f;
    double double_value = 0.0;
    long long_value = 0;
    uint32_t uint32_t_value = 0;
    // uint64_t uint64_t_value = 0;
    Color<T> color_value;
#ifdef USE_OPENGL
    texture texture_value;
#endif
    vec2<T> point_value;
    vec3<T> v3_value;
    vec4<T> rect_value;
    AABB<T> aabb_value;
    std::vector<float> vector_float_value;
    std::vector<double> vector_double_value;
    std::vector<std::string> vector_string_value;
    std::set<std::string> set_string_value;

public:
    variant() {
        bool_value = false;
        int_value = 0;
        float_value = 0.0f;
        double_value = 0.0;
        long_value = 0;
        uint32_t_value = 0;
    }
    variant(const int& v) {
        int_value = v;
        inputtype = "int";
        datatype = inputtype;
    }
    variant(const long& v) {
        long_value = v;
        inputtype = "long";
        datatype = inputtype;
    }
    // variant(const uint64_t& v) { uint64_t_value = v; inputtype = "uint64_t"; datatype = inputtype; }
    variant(const uint32_t& v) {
        uint32_t_value = v;
        inputtype = "uint32_t";
        datatype = inputtype;
    }
    variant(const float& v) {
        float_value = v;
        inputtype = "float";
        datatype = inputtype;
    }
    variant(const double& v) {
        double_value = v;
        inputtype = "double";
        datatype = inputtype;
    }
    variant(const std::string& v, const std::string& dt) {
        string_value = v;
        inputtype = "string";
        datatype = dt;
    }
    variant(const std::string& v) {
        string_value = v;
        inputtype = "string";
        datatype = inputtype;
    }
    variant(const bool& v) {
        bool_value = v;
        inputtype = "bool";
        datatype = inputtype;
    }
    variant(const Color<T>& c) {
        color_value = c;
        inputtype = "Color";
        datatype = inputtype;
    }
#ifdef USE_OPENGL
    variant(const texture& c) {
        texture_value = c;
        inputtype = "texture";
        datatype = inputtype;
    }
#endif
    variant(const vec2<T>& c) {
        point_value = c;
        inputtype = "vec2";
        datatype = inputtype;
    }
    variant(const vec3<T>& c) {
        v3_value = c;
        inputtype = "vec3";
        datatype = inputtype;
    }
    variant(const vec4<T>& c) {
        rect_value = c;
        inputtype = "vec4";
        datatype = inputtype;
    }
    variant(const AABB<T>& c) {
        aabb_value = c;
        inputtype = "AABB";
        datatype = inputtype;
    }
    variant(const std::vector<double>& c) {
        vector_double_value = c;
        inputtype = "vectorDouble";
        datatype = inputtype;
    }
    variant(const std::vector<float>& c) {
        vector_float_value = c;
        inputtype = "vectorFloat";
        datatype = inputtype;
    }
    variant(const std::vector<std::string>& c) {
        vector_string_value = c;
        inputtype = "vectorString";
        datatype = inputtype;
    }
    variant(const std::set<std::string>& c) {
        set_string_value = c;
        inputtype = "setString";
        datatype = inputtype;
    }

    std::string GetInputType() const {
        return inputtype;
    }
    std::string GetDataType() const {
        return datatype;
    }
    void setCustomDataType(const std::string& vDataType) {
        datatype = vDataType;
    }

    bool operator==(variant<T> v) {
        if (inputtype == v.inputtype) {
            if (inputtype == "vec4")
                return rect_value == v.rect_value;
            if (inputtype == "vec3")
                return v3_value == v.v3_value;
            if (inputtype == "vec2")
                return point_value == v.point_value;
            // if (inputtype == "AABB") == acreer pour AABB
            //	return aabb_value == v.aabb_value;
            if (inputtype == "bool")
                return bool_value == v.bool_value;
            if (inputtype == "float")
                return IS_FLOAT_EQUAL(float_value, v.float_value);
            if (inputtype == "double")
                return IS_DOUBLE_EQUAL(double_value, v.double_value);
            if (inputtype == "int")
                return int_value == v.int_value;
            if (inputtype == "long")
                return long_value == v.long_value;
            if (inputtype == "uint32_t")
                return uint32_t_value == v.uint32_t_value;
            return string_value == v.string_value;
        }
        return false;
    }

    /*uint64_t GetU64(bool *success = 0)
    {
        if (inputtype == "string")
        {
            uint64_t tmp = 0;

#ifdef MSVC
            int res = sscanf_s(string_value.c_str(), "%lu64", &tmp);
#else
            int res = sscanf(string_value.c_str(), "%lu64", &tmp);
#endif
            if (success)
            {
                if (res <= 0) *success = false;
                else *success = true;
            }

            //tmp = StringToNumber<size_t>(string_value);
            return tmp;
        }
        return uint64_t_value;
    }*/

    uint32_t GetU(bool* success = nullptr) const {
        if (inputtype == "string") {
            uint32_t tmp = 0;

#ifdef MSVC
            const int res = sscanf_s(string_value.c_str(), "%u", &tmp);
#else
            int res = sscanf(string_value.c_str(), "%u", &tmp);
#endif
            if (success) {
                *success = res > 0;
            }

            // tmp = StringToNumber<size_t>(string_value);
            return tmp;
        }
        return uint32_t_value;
    }

    std::string GetS(char c = ';', const char* prec = "%.6f") {
        if (inputtype == "vec4")
            return toStr(rect_value.x) + c + toStr(rect_value.y) + c + toStr(rect_value.z) + c + toStr(rect_value.w);
        if (inputtype == "vec3")
            return toStr(v3_value.x) + c + toStr(v3_value.y) + c + toStr(v3_value.z);
        if (inputtype == "vec2")
            return toStr(point_value.x) + c + toStr(point_value.y);
        if (inputtype == "AABB")
            return toStr(aabb_value.lowerBound.x) + c + toStr(aabb_value.lowerBound.y) + c + toStr(aabb_value.upperBound.x) + c + toStr(aabb_value.upperBound.y);
        if (inputtype == "bool")
            return (bool_value ? "true" : "false");
        if (inputtype == "float")
            return toStr(float_value);
        if (inputtype == "vectorFloat") {
            std::string str;
            for (auto f : vector_float_value) {
                if (!str.empty())
                    str += c;
                str += toStr(prec, f);
            }
            return str;
        }
        if (inputtype == "vectorDouble") {
            std::string str;
            for (auto f : vector_double_value) {
                if (!str.empty())
                    str += c;
                str += toStr(prec, f);
            }
            return str;
        }
        if (inputtype == "double")
            return toStr(double_value);
        if (inputtype == "int")
            return toStr(int_value);
        if (inputtype == "long")
            return toStr(long_value);
        if (inputtype == "uint32_t")
            return toStr(uint32_t_value);
        return string_value;
    }
    Color<T> GetColor(char c = ';') {
        if (inputtype == "string")
            return Color<T>(string_value, c);
        return color_value;
    }
#ifdef USE_OPENGL
    texture GetTexture() const {
        return texture_value;
    }
#endif
    vec2<T> GetV2(char c = ';') {
        if (inputtype == "string")
            return vec2<T>(string_value, c);
        else if (inputtype == "vectorString") {
        }
        return point_value;
    }
    vec3<T> GetV3(char c = ';') {
        if (inputtype == "string")
            return vec3<T>(string_value, c);
        else if (inputtype == "vectorString") {
        }
        return v3_value;
    }
    vec4<T> GetV4(char c = ';') {
        if (inputtype == "string")
            return vec4<T>(string_value, c, 4, 0);  //-V112
        else if (inputtype == "vectorString") {
        }
        return rect_value;
    }
    AABB<T> GetAABB(char c = ';') {
        if (inputtype == "string")
            return AABB<T>(string_value, c);
        return aabb_value;
    }
    std::vector<float> GetVectorFloat(char c = ';') const {
        if (inputtype == "string")
            return StringToNumberVector<float>(string_value, c);
        return vector_float_value;
    }
    std::vector<double> GetVectorDouble(char c = ';') const {
        if (inputtype == "string")
            return StringToNumberVector<double>(string_value, c);
        return vector_double_value;
    }
    std::vector<T> GetVectorType(char c = ';') {
        if (inputtype == "string")
            return StringToNumberVector<T>(string_value, c);
        return vector_float_value;
    }
    std::vector<std::string> GetVectorString(char c = ';') const {
        if (inputtype == "string")
            return splitStringToVector(string_value, c);
        return vector_string_value;
    }
    std::set<std::string> GetSetString(char c = ';') const {
        if (inputtype == "string")
            return splitStringToSet(string_value, c);
        return set_string_value;
    }
    float GetF(const char* vLocalToRetablish = nullptr) const {
        if (inputtype == "string") {
            std::setlocale(LC_NUMERIC, "C");
            auto res = (float)std::atof(string_value.c_str());
            if (vLocalToRetablish)
                std::setlocale(LC_NUMERIC, vLocalToRetablish);
            return res;
        }
        return float_value;
    }
    double GetD(const char* vLocalToRetablish = nullptr) const {
        if (inputtype == "string") {
            std::setlocale(LC_NUMERIC, "C");
            auto res = (double)std::atof(string_value.c_str());
            if (vLocalToRetablish)
                std::setlocale(LC_NUMERIC, vLocalToRetablish);
            return res;
        }
        return double_value;
    }
    int GetI(const char* vLocalToRetablish = nullptr) const {
        if (inputtype == "string") {
            std::setlocale(LC_NUMERIC, "C");
            auto res = std::atoi(string_value.c_str());
            if (vLocalToRetablish)
                std::setlocale(LC_NUMERIC, vLocalToRetablish);
            return res;
        }
        return int_value;
    }
    long GetL(const char* vLocalToRetablish = nullptr) const {
        if (inputtype == "string") {
            std::setlocale(LC_NUMERIC, "C");
            auto res = std::atol(string_value.c_str());
            if (vLocalToRetablish)
                std::setlocale(LC_NUMERIC, vLocalToRetablish);
            return res;
        }
        return long_value;
    }
    bool GetB() const {
        if (inputtype == "string") {
            if (string_value == "true" || string_value == "1")
                return true;
            else
                return false;
        } else
            return bool_value;
    }
};
typedef variant<float> fvariant;   // utile pour le type de renvoi des vec2,3,4 et AABB
typedef variant<double> dvariant;  // utile pour le type de renvoi des vec2,3,4 et AABB
typedef variant<size_t> uvariant;
typedef variant<int> ivariant;

/////////////////////////////////////////////////////////////
///////// SPECIALIZATION // VEC2 / VEC3 / VEC4 / QUAT ///////
/////////////////////////////////////////////////////////////

template <>
inline bool ct::vec2<float>::operator==(const float& a) {
    return (IS_FLOAT_EQUAL(x, a) && IS_FLOAT_EQUAL(y, a));
}
template <>
inline bool ct::vec2<float>::operator==(const ct::vec2<float>& v) {
    return (IS_FLOAT_EQUAL(x, v.x) && IS_FLOAT_EQUAL(y, v.y));
}
template <>
inline bool ct::vec2<float>::operator!=(const float& a) {
    return (IS_FLOAT_DIFFERENT(x, a) || IS_FLOAT_DIFFERENT(y, a));
}
template <>
inline bool ct::vec2<float>::operator!=(const ct::vec2<float>& v) {
    return (IS_FLOAT_DIFFERENT(x, v.x) || IS_FLOAT_DIFFERENT(y, v.y));
}

template <>
inline bool ct::vec2<double>::operator==(const double& a) {
    return (IS_DOUBLE_EQUAL(x, a) && IS_DOUBLE_EQUAL(y, a));
}
template <>
inline bool ct::vec2<double>::operator==(const ct::vec2<double>& v) {
    return (IS_DOUBLE_EQUAL(x, v.x) && IS_DOUBLE_EQUAL(y, v.y));
}
template <>
inline bool ct::vec2<double>::operator!=(const double& a) {
    return (IS_DOUBLE_DIFFERENT(x, a) || IS_DOUBLE_DIFFERENT(y, a));
}
template <>
inline bool ct::vec2<double>::operator!=(const ct::vec2<double>& v) {
    return (IS_DOUBLE_DIFFERENT(x, v.x) || IS_DOUBLE_DIFFERENT(y, v.y));
}

template <>
inline bool ct::vec3<float>::operator==(const float& a) {
    return (IS_FLOAT_EQUAL(x, a) && IS_FLOAT_EQUAL(y, a) && IS_FLOAT_EQUAL(z, a));
}
template <>
inline bool ct::vec3<float>::operator==(const ct::vec3<float>& v) {
    return (IS_FLOAT_EQUAL(x, v.x) && IS_FLOAT_EQUAL(y, v.y) && IS_FLOAT_EQUAL(z, v.z));
}
template <>
inline bool ct::vec3<float>::operator!=(const float& a) {
    return (IS_FLOAT_DIFFERENT(x, a) || IS_FLOAT_DIFFERENT(y, a) || IS_FLOAT_DIFFERENT(z, a));
}
template <>
inline bool ct::vec3<float>::operator!=(const ct::vec3<float>& v) {
    return (IS_FLOAT_DIFFERENT(x, v.x) || IS_FLOAT_DIFFERENT(y, v.y) || IS_FLOAT_DIFFERENT(z, v.z));
}

template <>
inline bool ct::vec3<double>::operator==(const double& a) {
    return (IS_DOUBLE_EQUAL(x, a) && IS_DOUBLE_EQUAL(y, a) && IS_DOUBLE_EQUAL(z, a));
}
template <>
inline bool ct::vec3<double>::operator==(const ct::vec3<double>& v) {
    return (IS_DOUBLE_EQUAL(x, v.x) && IS_DOUBLE_EQUAL(y, v.y) && IS_DOUBLE_EQUAL(z, v.z));
}
template <>
inline bool ct::vec3<double>::operator!=(const double& a) {
    return (IS_DOUBLE_DIFFERENT(x, a) || IS_DOUBLE_DIFFERENT(y, a) || IS_DOUBLE_DIFFERENT(z, a));
}
template <>
inline bool ct::vec3<double>::operator!=(const ct::vec3<double>& v) {
    return (IS_DOUBLE_DIFFERENT(x, v.x) || IS_DOUBLE_DIFFERENT(y, v.y) || IS_DOUBLE_DIFFERENT(z, v.z));
}

template <>
inline bool ct::vec4<float>::operator==(const float& a) {
    return (IS_FLOAT_EQUAL(x, a) && IS_FLOAT_EQUAL(y, a) && IS_FLOAT_EQUAL(z, a) && IS_FLOAT_EQUAL(w, a));
}
template <>
inline bool ct::vec4<float>::operator==(const ct::vec4<float>& v) {
    return (IS_FLOAT_EQUAL(x, v.x) && IS_FLOAT_EQUAL(y, v.y) && IS_FLOAT_EQUAL(z, v.z) && IS_FLOAT_EQUAL(w, v.w));
}
template <>
inline bool ct::vec4<float>::operator!=(const float& a) {
    return (IS_FLOAT_DIFFERENT(x, a) || IS_FLOAT_DIFFERENT(y, a) || IS_FLOAT_DIFFERENT(z, a) || IS_FLOAT_DIFFERENT(w, a));
}
template <>
inline bool ct::vec4<float>::operator!=(const ct::vec4<float>& v) {
    return (IS_FLOAT_DIFFERENT(x, v.x) || IS_FLOAT_DIFFERENT(y, v.y) || IS_FLOAT_DIFFERENT(z, v.z) || IS_FLOAT_DIFFERENT(w, v.w));
}

template <>
inline bool ct::vec4<double>::operator==(const double& a) {
    return (IS_DOUBLE_EQUAL(x, a) && IS_DOUBLE_EQUAL(y, a) && IS_DOUBLE_EQUAL(z, a) && IS_DOUBLE_EQUAL(w, a));
}
template <>
inline bool ct::vec4<double>::operator==(const ct::vec4<double>& v) {
    return (IS_DOUBLE_EQUAL(x, v.x) && IS_DOUBLE_EQUAL(y, v.y) && IS_DOUBLE_EQUAL(z, v.z) && IS_DOUBLE_EQUAL(w, v.w));
}
template <>
inline bool ct::vec4<double>::operator!=(const double& a) {
    return (IS_DOUBLE_DIFFERENT(x, a) || IS_DOUBLE_DIFFERENT(y, a) || IS_DOUBLE_DIFFERENT(z, a) || IS_DOUBLE_DIFFERENT(w, a));
}
template <>
inline bool ct::vec4<double>::operator!=(const ct::vec4<double>& v) {
    return (IS_DOUBLE_DIFFERENT(x, v.x) || IS_DOUBLE_DIFFERENT(y, v.y) || IS_DOUBLE_DIFFERENT(z, v.z) || IS_DOUBLE_DIFFERENT(w, v.w));
}

template <>
inline void ct::quat<float>::normalize() {
    float n = sqrt(x * x + y * y + z * z + w * w);
    if (IS_FLOAT_EQUAL(n, 0.0f)) {
        return;
    }
    x /= n;
    y /= n;
    z /= n;
    w /= n;
}

template <>
inline void ct::quat<double>::normalize() {
    double n = sqrt(x * x + y * y + z * z + w * w);
    if (IS_DOUBLE_EQUAL(n, 0.0)) {
        return;
    }
    x /= n;
    y /= n;
    z /= n;
    w /= n;
}

/////////////////////////////////////////////////////////////
///////// GetNewBufferFromList //////////////////////////////
/////////////////////////////////////////////////////////////

// Buffer a destroy apres utilisationBufferSize
// in : lst, offset
// out : return, BufferSize
template <typename T>
T* GetNewBufferFromList(std::list<T>& lst, int offsetBefore, int offsetAfter, int* BufferSize);

/////////////////////////////////////////////////////////////
///////// GetNewBufferFromMap ///////////////////////////////
/////////////////////////////////////////////////////////////

// Buffer a destroy apres utilisationBufferSize
// in : lst, offset
// out : return, BufferSize
template <typename T, typename P>
P* GetNewBufferFromMap(std::map<T, P>& mp, int offsetBefore, int offsetAfter, int* BufferSize);

/////////////////////////////////////////////////////////////
///////// DeleteObjectsAndClearPointerList //////////////////
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
///////// DeleteObjectsAndClearPointerList //////////////////
/////////////////////////////////////////////////////////////

template <typename T>
void DeleteObjectsAndClearPointerList(std::list<T*>& lst) {
    if (!lst.empty()) {
        for (typename std::list<T*>::iterator it = lst.begin(); it != lst.end(); ++it) {
            T* type = nullptr;
            type = *it;
            if (type != nullptr) {
                delete type;
                *it = 0;
            }
        }
        lst.clear();
    }
}

template <typename T>
void DeleteObjectsAndClearPointerVector(std::vector<T*>& vec) {
    if (!vec.empty()) {
        for (typename std::vector<T*>::iterator it = vec.begin(); it != vec.end(); ++it) {
            T* type = nullptr;
            type = *it;
            if (type != nullptr) {
                delete type;
                *it = 0;
            }
        }

        vec.clear();
    }
}

template <typename T>
std::string VectorToString(std::vector<T>& vec, char vCharDelimiter);
template <typename T>
std::string VectorVec2ToString(std::vector<vec2<T>>& vec, char vCharDelimiter);  // vec2<T>> give an error in osx... must be vec2<T> >
template <typename T>
std::string VectorVec3ToString(std::vector<vec3<T>>& vec, char vCharDelimiter);  // vec3<T>> give an error in osx... must be vec3<T> >
template <typename T>
std::string VectorVec4ToString(std::vector<vec4<T>>& vec, char vCharDelimiter);  // vec4<T>> give an error in osx... must be vec4<T> >

// return "vParamName=\"" + toStr(vValue) + "\";
template <typename T>
std::string ParamToXMLString(std::string vParamName, T vValue);

// return "vParamName=\"" + toStr(vValue) + "\" si vValue est different de vValueDiff;
template <typename T>
std::string ParamToXMLStringDiff(std::string vParamName, T vValue, T vValueDiff);
// Mix : Get value based on ratio and inf and sup limit // https://www.opengl.org/sdk/docs/man/html/mix.xhtml
// ex : mix(2.0f, 6.0f, 0.5f) => 4.0f

template <typename T>
vec2<T> mix(const vec2<T>& vInf, const vec2<T>& vSup, const vec2<T>& vRatio);
template <typename T>
vec3<T> mix(const vec3<T>& vInf, const vec3<T>& vSup, const vec3<T>& vRatio);
template <typename T>
vec4<T> mix(const vec4<T>& vInf, const vec4<T>& vSup, const vec4<T>& vRatio);

// Get ratio based on value and inf and sup limit
// ex : cRatio(2.0f, 6.0f, 4.0f) => 0.5f

template <typename T>
vec2<T> invMix(const vec2<T>& vInf, const vec2<T>& vSup, const vec2<T>& vValue);
template <typename T>
vec3<T> invMix(const vec3<T>& vInf, const vec3<T>& vSup, const vec3<T>& vValue);
template <typename T>
vec4<T> invMix(const vec4<T>& vInf, const vec4<T>& vSup, const vec4<T>& vValue);

// clamp
template <typename T>
vec2<T> clamp(const vec2<T>& vValue, const vec2<T>& vInf, const vec2<T>& vSup);
template <typename T>
vec3<T> clamp(const vec3<T>& vValue, const vec3<T>& vInf, const vec3<T>& vSup) {
    ct::vec3<T> vUniform = vValue;
    vUniform.x = ct::clamp(vUniform.x, vInf.x, vSup.x);
    vUniform.y = ct::clamp(vUniform.y, vInf.y, vSup.y);
    vUniform.z = ct::clamp(vUniform.z, vInf.z, vSup.z);
    return vUniform;
}
template <typename T>
vec4<T> clamp(const vec4<T>& vValue, const vec4<T>& vInf, const vec4<T>& vSup);
template <typename T>
vec2<T> clamp(const vec2<T>& vValue, T vInf, T vSup) {
    ct::vec2<T> vUniform = vValue;
    vUniform.x = ct::clamp(vUniform.x, vInf, vSup);
    vUniform.y = ct::clamp(vUniform.y, vInf, vSup);
    return vUniform;
}
template <typename T>
vec3<T> clamp(const vec3<T>& vValue, T vInf, T vSup) {
    ct::vec3<T> vUniform = vValue;
    vUniform.x = ct::clamp(vUniform.x, vInf, vSup);
    vUniform.y = ct::clamp(vUniform.y, vInf, vSup);
    vUniform.z = ct::clamp(vUniform.z, vInf, vSup);
    return vUniform;
}
template <typename T>
vec4<T> clamp(const vec4<T>& vValue, T vInf, T vSup);
template <typename T>
vec2<T> clamp(const vec2<T>& vValue);
template <typename T>
vec3<T> clamp(const vec3<T>& vValue);
template <typename T>
vec4<T> clamp(const vec4<T>& vValue);

// mod
template <typename T>
vec2<T> mod(const vec2<T>& vValue, const vec2<T>& vLim);
template <typename T>
vec3<T> mod(const vec3<T>& vValue, const vec3<T>& vLim);
template <typename T>
vec4<T> mod(const vec4<T>& vValue, const vec4<T>& vLim);
template <typename T>
vec2<T> mod(const vec2<T>& vValue, T vLim);
template <typename T>
vec3<T> mod(const vec3<T>& vValue, T vLim);
template <typename T>
vec4<T> mod(const vec4<T>& vValue, T vLim);

// ReRange value from range 0-MaxRange to range Sup-Inf and return new value
// 0 ----- Inf ----- value ---- Sup ---- MaxRange
template <typename T>
T cReRange(T vMaxRange, T vNewRangeInf, T vNewRangeSup, T vValue);

CTOOLS_API size_t ratioOfSizeT(size_t t, double r);

// format 2500000 to 2.5M by ex
CTOOLS_API std::string FormatNum(size_t vNum, int vDecimalCount);

/////////////////////////////////////////////////////////////
/// Specialisation et gestion des type complex de toStr /////
/////////////////////////////////////////////////////////////

template <typename T>
std::string toStr(vec2<T> v, char delimiter = ',') {
    return ct::toStr(&v.x, 2, delimiter);
}
template <typename T>
std::string toStr(vec3<T> v, char delimiter = ',') {
    return ct::toStr(&v.x, 3, delimiter);
}
template <typename T>
std::string toStr(vec4<T> v, char delimiter = ',') {
    return ct::toStr(&v.x, 4, delimiter);  //-V112
}

/////////////////////////////////////////////////////////////
///////// DeleteObjectsAndClearPointerList //////////////////
/////////////////////////////////////////////////////////////

template <typename T>
ct::rect<T> GetScreenRectWithSize(ct::vec2<T> vItemSize, ct::vec2<T> vMaxSize, bool vLogError = true) {
    ct::rect<T> rc;

    ct::fvec2 visibleSize = ct::fvec2((float)vMaxSize.x, (float)vMaxSize.y);
    if (visibleSize.x > 0.0f && visibleSize.y > 0.0f) {
        ct::fvec2 visibleOrigin;
        const ct::fvec2 texSize = ct::fvec2((float)vItemSize.x, (float)vItemSize.y);

        // float visibleRatio = visibleSize.x / visibleSize.y;
        const float refRatio = texSize.x / texSize.y;

        float newX = visibleSize.y * refRatio;
        float newY = visibleSize.x / refRatio;

        if (newX < visibleSize.x) {
            // pos
            rc.x = (T)(visibleOrigin.x + (visibleSize.x - newX) * 0.5f);
            rc.y = (T)visibleOrigin.y;

            // size
            rc.w = (T)newX;
            rc.h = (T)visibleSize.y;
        } else {
            // pos
            rc.x = (T)visibleOrigin.x;
            rc.y = (T)(visibleOrigin.y + (visibleSize.y - newY) * 0.5f);

            // size
            rc.w = (T)visibleSize.x;
            rc.h = (T)newY;
        }

        if constexpr (std::is_same<T, float>::value || std::is_same<T, double>::value) {
            rc = ct::floor<T>(rc);
        }

        const float newRatio = (float)rc.w / (float)rc.h;
        if (vLogError)
            if (IS_FLOAT_DIFFERENT(newRatio, refRatio))
                printf("GetScreenRectWithRatio : the new ratio is not the same as the ref ratio\n");
    }

    return rc;
}

template <typename T>
ct::rect<T> GetScreenRectWithRatio(float vRatio, ct::vec2<T> vMaxSize, bool vLogError = true) {
    ct::rect<T> rc;

    ct::fvec2 visibleSize = ct::fvec2((float)vMaxSize.x, (float)vMaxSize.y);
    if (visibleSize.x > 0.0f && visibleSize.y > 0.0f) {
        ct::fvec2 visibleOrigin;

        const float refRatio = vRatio;

        float newX = visibleSize.y * refRatio;
        float newY = visibleSize.x / refRatio;

        if (newX < visibleSize.x) {
            // pos
            rc.x = (T)(visibleOrigin.x + (visibleSize.x - newX) * 0.5f);
            rc.y = (T)visibleOrigin.y;

            // size
            rc.w = (T)newX;
            rc.h = (T)visibleSize.y;
        } else {
            // pos
            rc.x = (T)visibleOrigin.x;
            rc.y = (T)(visibleOrigin.y + (visibleSize.y - newY) * 0.5f);

            // size
            rc.w = (T)visibleSize.x;
            rc.h = (T)newY;
        }

        if constexpr (std::is_same<T, float>::value || std::is_same<T, double>::value) {
            rc = ct::floor<T>(rc);
        }

        const float newRatio = (float)rc.w / (float)rc.h;
        if (vLogError)
            if (IS_FLOAT_DIFFERENT(newRatio, refRatio))
                printf("GetScreenRectWithRatio : the new ratio is not the same as the ref ratio\n");
    }

    return rc;
}

/////////////////////////////////////////////////////////////
///////// EASY WEAK_PTR /////////////////////////////////////
/////////////////////////////////////////////////////////////

/*
#if 1
template <bool _Test, class _Ty = void>
using ct_enable_if_t = typename std::enable_if<_Test, _Ty>::type;

template <class _Yty, class _Ty>
struct ct_SP_pointer_compatible : std::is_convertible<_Yty*, _Ty*>::type {};
template <class _Uty, size_t _Ext>
struct ct_SP_pointer_compatible<_Uty[_Ext], _Uty[]> : std::true_type {};
template <class _Uty, size_t _Ext>
struct ct_SP_pointer_compatible<_Uty[_Ext], const _Uty[]> : std::true_type {};
template <class _Uty, size_t _Ext>
struct ct_SP_pointer_compatible<_Uty[_Ext], volatile _Uty[]> : std::true_type {};
template <class _Uty, size_t _Ext>
struct ct_SP_pointer_compatible<_Uty[_Ext], const volatile _Uty[]> : std::true_type {	};

template<typename T>
class cWeak : public std::weak_ptr<T>
{
    template<typename TArg>
    using uConstructible = typename std::enable_if<std::is_constructible<std::weak_ptr<T>, TArg>::value>::type;

    template<typename TArg>
    using uAssignable = typename std::enable_if<std::is_assignable<std::weak_ptr<T>&, TArg>::value, cWeak&>::type;

    template<typename TArg>
    using uConvertible = typename std::enable_if<std::is_convertible<std::weak_ptr<T>&, TArg>::value, cWeak&>::type;

public:
    constexpr cWeak() noexcept {}

    cWeak(const cWeak& _Other) noexcept : std::weak_ptr<T>(_Other) {}

    template <class T2, ct_enable_if_t<ct_SP_pointer_compatible<T2, T>::value, int> = 0>
    cWeak(const std::shared_ptr<T2>& _Other) noexcept : std::weak_ptr<T>(_Other) {}

    template <class T2, ct_enable_if_t<ct_SP_pointer_compatible<T2, T>::value, int> = 0>
    cWeak(const std::weak_ptr<T2>& _Other) noexcept : std::weak_ptr<T>(_Other) {}

    cWeak(std::weak_ptr<T>&& _Other) noexcept : std::weak_ptr<T>(_Other) {}

    template <class T2, ct_enable_if_t<ct_SP_pointer_compatible<T2, T>::value, int> = 0>
    cWeak(std::weak_ptr<T2>&& _Other) noexcept : std::weak_ptr<T>(_Other) {}

    bool valid() const noexcept
    {
        return !this->expired();
    }

    // if not expired, directly return a shared_ptr
    std::shared_ptr<T> lock() const noexcept
    {
        if (valid())
        {
            return lock();
        }
        return nullptr;
    }

    // weak = weak
    template<typename T2>
    uAssignable<const cWeak<T2>&> operator=(const cWeak<T2>& vWeak) noexcept
    {
        this->std::weak_ptr<T>::operator=(vWeak);
        return *this;
    }

    template<typename T2>
    uAssignable<const cWeak<T2>&> operator=(const std::weak_ptr<T2>& vWeak) noexcept
    {
        this->std::weak_ptr<T>::operator=(vWeak);
        return *this;
    }

    // weak = shared
    template<typename T2>
    uAssignable<const cWeak<T2>&> operator=(const std::shared_ptr<T2>& vShared) noexcept
    {
        this->std::weak_ptr<T>::operator=(vShared);
        return *this;
    }

    cWeak& operator=(const std::weak_ptr<T>& vWeak) noexcept
    {
        this->std::weak_ptr<T>::operator=(vWeak);
        return *this;
    }

    bool operator<(const std::weak_ptr<T>& vWeak) noexcept
    {
        return this->std::weak_ptr<T>::operator<(vWeak);
    }
    explicit operator bool() const noexcept
    {
        return ((!this->expired()) && (this->lock() != nullptr));
    }
};
template<typename T>
bool operator<(const cWeak<T>& vWeakA, const cWeak<T>& vWeakB) noexcept
{
    if (vWeakA.expired() || vWeakB.expired())
        return false;
    return (vWeakA.lock() < vWeakB.lock());
}
#else
template<typename T>
class cWeak
{
private:
    std::weak_ptr<T> m_WeakPtr;

public:
    constexpr cWeak() noexcept {}

    cWeak(const cWeak& _Other) noexcept : m_WeakPtr(_Other) {}

    template <class T2>
    cWeak(const std::shared_ptr<T2>& _Other) noexcept : m_WeakPtr(_Other) {}

    template <class T2>
    cWeak(const cWeak<T2>& _Other) noexcept : cWeak<T>(_Other) {}

    cWeak(cWeak<T>&& _Other) noexcept : m_WeakPtr(_Other) {}

    template <class T2>
    cWeak(cWeak<T2>&& _Other) noexcept : m_WeakPtr(_Other) {}

    bool valid() const noexcept
    {
        return !m_WeakPtr.expired();
    }

    // if not expired, directly return a shared_ptr
    std::shared_ptr<T> lock() noexcept
    {
        if (m_WeakPtr.valid())
        {
            return m_WeakPtr.lock();
        }
        return std::shared_ptr<T>();
    }

    cWeak& operator=(const cWeak& _Right) noexcept
    {
        cWeak(_Right).swap(m_WeakPtr);
        return *this;
    }

    template <class T2>
    cWeak& operator=(const cWeak<T2>& _Right) noexcept
    {
        cWeak(_Right).swap(m_WeakPtr);
        return *this;
    }

    cWeak& operator=(cWeak&& _Right) noexcept
    {
        cWeak(std::move(_Right)).swap(m_WeakPtr);
        return m_WeakPtr;
    }

    template <class T2>
    cWeak& operator=(cWeak<T2>&& _Right) noexcept
    {
        cWeak(std::move(_Right)).swap(m_WeakPtr);
        return m_WeakPtr;
    }

    template <class T2>
    cWeak& operator=(const std::shared_ptr<T2>& _Right) noexcept
    {
        cWeak(_Right).swap(m_WeakPtr);
        return m_WeakPtr;
    }

    void reset() noexcept
    {
        m_WeakPtr.reset();
    }

    void swap(cWeak& _Other) noexcept
    {
        m_WeakPtr.swap(_Other);
    }

    _NODISCARD bool expired() const noexcept
    {
        return m_WeakPtr.expired();
    }

    std::shared_ptr<T> lock() const noexcept
    {
        return m_WeakPtr.lock();
    }

    explicit operator bool() const noexcept
    {
        return ((!m_WeakPtr.expired()) && (m_WeakPtr.lock() != nullptr));
    }
};
#endif
*/

}  // namespace ct
