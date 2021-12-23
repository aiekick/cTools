cmake_minimum_required(VERSION 3.22)

set(PROJECT ctools)
enable_language(C CXX)
project(${PROJECT} CXX)


option(USE_GL_VERSION_CHECKER "Use Gl Version Checker class" OFF)
option(USE_CONFIG_SYSTEM "Use Config Load/Save class" ON)
option(USE_GLFW_CLIPBOARD "Use Clipboard via GLFW3 (need glfW3)" OFF)
option(USE_SDL_CLIPBOARD "Use Clipboard via SDL2 (need SDL2)" OFF)
option(USE_TEST "Enable Tests" OFF)

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

if (USE_GLFW_CLIPBOARD)
	add_definitions(-DUSE_GLFW3)
elseif(USE_SDL_CLIPBOARD)
	add_definitions(-DUSE_SDL2)
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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
endif ()

add_library(${PROJECT} STATIC ${CTOOLS_SRC} ${CONFIG_SYSTEM_SRC} ${GLVERSIONCHECKER_SRC})

include_directories(.)

set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)

set(CTOOLS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(CTOOLS_LIBRARIES ${PROJECT} PARENT_SCOPE)
set(CTOOLS_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)

#############################################################
### TESTS ###################################################
#############################################################

if(USE_TEST)
enable_testing()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
set(LLVM_USE_CRT_DEBUG MTd CACHE STRING "" FORCE)
set(LLVM_USE_CRT_MINSIZEREL MT CACHE STRING "" FORCE)
set(LLVM_USE_CRT_RELEASE MT CACHE STRING "" FORCE)
set(LLVM_USE_CRT_RELWITHDEBINFO MT CACHE STRING "" FORCE)
set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmakeTargets")

endif()