cmake_minimum_required(VERSION 2.8)

project(parser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("enable Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb3")    
endif()

add_executable(test_rtsp test_rtsp.cpp http_parser.c)
add_executable(test_http test.c http_parser.c)


