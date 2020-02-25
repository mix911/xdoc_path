find_package(Boost 1.72.0)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${JSON_SPIRIT_INCLUDE_DIR})
include_directories(${TINY_XML_INCLUDE_DIR})
include_directories(${GTEST_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/../include)
include_directories(${CMAKE_SOURCE_DIR}/xdoc_path)

#set(BUILD_SHARED_LIBS Off)
#set(BUILD_SHARED_LIBS On)

#-DTINY_XML_LIB_DIR=D:\work\shared\MSVC2019\UPG\Externals_2019\tinyxml\x64\Debug
#-DGTEST_LIB_DIR=D:\work\shared\MSVC2019\UPG\Externals_2019\gtestlib\x64\Debug
#-DBOOST_LIB_DIR=D:\work\shared\MSVC2019\UPG\Externals_2019\boost\Debug-x64\lib
#-DJSON_SPIRIT_LIB_DIR=D:\work\shared\json_spirit\x64\Debug

link_directories(${TINY_XML_LIB_DIR})
link_directories(${GTEST_LIB_DIR})
link_directories(${BOOST_LIB_DIR})
link_directories(${JSON_SPIRIT_LIB_DIR})
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(tests main.cpp test_request_by_jpath.cpp test_get_value.cpp test_request_by_xpath.cpp)

target_link_libraries(tests debug xdoc_path.lib gtestlib.lib json_spirit_lib.lib tinyxml.lib)
target_link_libraries(tests optimized xdoc_path.lib gtestlib.lib json_spirit_lib.lib tinyxml.lib)
