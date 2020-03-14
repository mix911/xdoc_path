cmake_minimum_required(VERSION 3.0)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_PLATFORM_TYPES "Win32;x64")

include_directories("${shared}MSVC2019\\UPG\\Externals_2019\\boost\\${CMAKE_BUILD_TYPE}-${CMAKE_GENERATOR_PLATFORM}\\include\\boost-1_72")

add_library(xdoc_path.a
src/xdoc_path/xtiny_path.cpp
src/xdoc_path/jspirit_path.cpp)
