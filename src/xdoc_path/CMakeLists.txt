find_package(Boost)
#find_package(TinyXML2 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${JSON_SPIRIT_INCLUDE_DIR})
include_directories(${TINY_XML_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../include/xdoc_path)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

file(GLOB headers *.h)
add_library(xdoc_path STATIC xtiny_path.cpp xtiny_path.h jspirit_path.cpp jspirit_path.h)

add_definitions(-DEXPMODULE)

