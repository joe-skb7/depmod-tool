cmake_minimum_required(VERSION 2.8)
set(PROJECT depmod)
project(${PROJECT})

include_directories(include)
set(HEADERS
	include/parser.h
	include/sorter.h)
set(SOURCES
	src/parser.cpp
	src/sorter.cpp
	src/main.cpp)

add_definitions(-Wall)
add_executable(${PROJECT} ${SOURCES} ${HEADERS})
install(TARGETS ${PROJECT} DESTINATION bin)
