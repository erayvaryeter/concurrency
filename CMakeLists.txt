﻿set(project_name concurrency)
cmake_minimum_required (VERSION 3.18)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" )
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
	set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS}")
else()
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" )
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
	set(CMAKE_STATIC_LINKER_FLAGS "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

project(${project_name} LANGUAGES CXX)

include(conan)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_VERBOSE_MAKEFILE TRUE)

conan_check(VERSION 1.16.0 REQUIRED)
conan_cmake_run(CONANFILE conanfile.py BASIC_SETUP CMAKE_TARGETS KEEP_RPATHS UPDATE)

set(include_files
	include/Semaphore.h
	include/Worker.h
	include/JobScheduler.h
)

set(source_files
	src/Semaphore.cpp
	src/Worker.cpp
	src/JobScheduler.cpp
	src/main.cpp
)

add_executable(${project_name}-cli ${include_files} ${source_files})