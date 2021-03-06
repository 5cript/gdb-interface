# Version check
cmake_minimum_required(VERSION 3.9)

option(BUILD_SHARED "Build shared variant of library" OFF)

if(NOT "${CMAKE_CXX_STANDARD}")
	set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  endif()
endif()

# Project
project(dbgint VERSION 1.0.0 DESCRIPTION "a very basic gdb/lldb mi parser")

# Add files
file(GLOB sources "*.cpp"
				  "input/*.cpp"
				  "input/parser/*.cpp"
				  "input/raw/*.cpp"
				  "../twisted-spirit/rules/space.cpp"
)

# Add library
if (BUILD_SHARED)
	add_library(${PROJECT_NAME} SHARED ${sources})
else()
	add_library(${PROJECT_NAME} STATIC ${sources})
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

target_include_directories(${PROJECT_NAME} PRIVATE "..")

find_library(LTINY_PROCESS_LIBRARY tiny-process-library PATHS "../tiny-process-library/build")

target_link_libraries(${PROJECT_NAME} PRIVATE 
	"${LTINY_PROCESS_LIBRARY}"
)

# Compiler Options
set(DEBUG_OPTIONS -fexceptions -g -Wall -pedantic-errors -pedantic)
set(RELEASE_OPTIONS -fexceptions -O3 -Wall -pedantic-errors -pedantic -s -static-libstdc++ -static-libgcc)
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")