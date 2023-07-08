cmake_minimum_required(VERSION 3.0)

set(PROJECT ctools)
enable_language(C CXX)
project(${PROJECT} CXX)

option(USE_GL_VERSION_CHECKER "Use Gl Version Checker class" OFF)
option(USE_CONFIG_SYSTEM "Use Config Load/Save class" ON)
option(USE_GLFW_CLIPBOARD "Use Clipboard via GLFW3 (need glfW3)" OFF)
option(USE_SDL_CLIPBOARD "Use Clipboard via SDL2 (need SDL2)" OFF)
option(USE_CTOOLS_TESTING "Enable Tests" OFF)
option(USE_TOOLS_SHARED_LIB  "Enable Ctools Shared Lib" OFF)

file(GLOB CTOOLS_SRC 
	${CMAKE_CURRENT_SOURCE_DIR}/src/cTools.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/cTools.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/Logger.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Logger.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/FileHelper.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/FileHelper.h)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX src FILES ${CTOOLS_SRC})
	
if(USE_CONFIG_SYSTEM)
	file(GLOB CONFIG_SYSTEM_SRC
		${CMAKE_CURRENT_SOURCE_DIR}/src/ConfigAbstract.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/src/ConfigAbstract.h)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX src FILES ${CONFIG_SYSTEM_SRC})
endif()

if(USE_GL_VERSION_CHECKER)
	file(GLOB GLVERSIONCHECKER_SRC
		${CMAKE_CURRENT_SOURCE_DIR}/src/GLVersionChecker.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}/src/GLVersionChecker.h)
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX src FILES ${GLVERSIONCHECKER_SRC})
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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif ()

if (USE_TOOLS_SHARED_LIB)
	set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
	set(USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE BOOL "" FORCE)
	add_library(${PROJECT} ${CTOOLS_SRC} ${CONFIG_SYSTEM_SRC} ${GLVERSIONCHECKER_SRC})
	target_compile_definitions(${PROJECT} INTERFACE BUILD_SHARED_LIBS)
	set_target_properties(${PROJECT} PROPERTIES	RUNTIME_OUTPUT_DIRECTORY "${FINAL_BIN_DIR}")
	set_target_properties(${PROJECT} PROPERTIES POSITION_INDEPENDENT_CODE ON)
	target_link_libraries(${PROJECT} ${GLAD_LIBRARIES} ${TINYXML2_LIBRARIES})
	if (USE_GLFW_CLIPBOARD)
		target_link_libraries(${PROJECT} glfw)
	elseif(USE_SDL_CLIPBOARD)
		target_link_libraries(${PROJECT} SDL2)
	endif()
else()
	set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
	set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "" FORCE)
	add_library(${PROJECT} STATIC ${CTOOLS_SRC} ${CONFIG_SYSTEM_SRC} ${GLVERSIONCHECKER_SRC})
endif()

include_directories(.)

set_target_properties(${PROJECT} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${GLAD_INCLUDE_DIR}
	${TINYXML2_INCLUDE_DIR}
)

set(${PROJECT}_Output_Name "${PROJECT}$<$<CONFIG:Debug>:d>")
set_target_properties(${PROJECT} PROPERTIES	OUTPUT_NAME "${${PROJECT}_Output_Name}")

set(CTOOLS_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src PARENT_SCOPE)
set(CTOOLS_LIBRARIES ${PROJECT} PARENT_SCOPE)
set(CTOOLS_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)

#############################################################
### TESTS ###################################################
#############################################################

if(USE_CTOOLS_TESTING)
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