cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0012 NEW)
cmake_policy(SET CMP0023 NEW)

enable_language(C CXX)

option(USE_GL_VERSION_CHECKER "Use Gl Version Checker class" OFF)
option(USE_CONFIG_SYSTEM "Use Config Load/Save class" ON)

file(GLOB CTOOLS_SRC 
	${CMAKE_CURRENT_SOURCE_DIR}/cTools.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/cTools.h
	${CMAKE_CURRENT_SOURCE_DIR}/Logger.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Logger.h
	${CMAKE_CURRENT_SOURCE_DIR}/FileHelper.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/FileHelper.h)
	
if(USE_CONFIG_SYSTEM)
file(GLOB CONFIG_SYSTEM_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/ConfigAbstract.h)
endif()

if(USE_GL_VERSION_CHECKER)
	file(GLOB GLVERSIONCHECKER_SRC
		${CMAKE_CURRENT_SOURCE_DIR}/GLVersionChecker.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}/GLVersionChecker.h)
endif()

if(UNIX)
	if(APPLE)
		add_definitions(-DAPPLE)
	else()
		add_definitions(-DLINUX)
	endif()
	add_definitions(-DUNIX)
elseif(WIN32)
	add_definitions(-DWIN32)
	if(MINGW)
		add_definitions(-DMINGW32)
		add_definitions(-DHAVE_STRTOK_R)
		add_definitions(-DHAVE___BUILTIN_FFS)
	endif()
endif()

if(MSVC)
    # Ignore 4055 for glad
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /IGNORE:4055")
	add_definitions(-D__STDC__)
	add_definitions(-DMSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra") ## -std=gnu++0x
endif ()

set(SOURCE ${CTOOLS_SRC})
if(USE_GL_VERSION_CHECKER)
	set(SOURCE ${SOURCE} ${GLVERSIONCHECKER_SRC})
endif()
if(USE_CONFIG_SYSTEM)
	set(SOURCE ${SOURCE} ${CONFIG_SYSTEM_SRC})
endif()
add_library(ctools STATIC ${SOURCE})

include_directories(.)

set_target_properties(ctools PROPERTIES LINKER_LANGUAGE CXX)

set(CTOOLS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(CTOOLS_LIBRARIES ctools PARENT_SCOPE)
set(CTOOLS_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)
