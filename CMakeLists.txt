cmake_minimum_required (VERSION 2.6)

project (OCV)
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
#message( OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS})
include_directories(utils)

set(SOURCES
 Comm.cpp
 ImageOpers.cpp
 main.cpp
)
add_executable(OCV ${SOURCES})
set_property(TARGET OCV PROPERTY CXX_STANDARD 11)
target_link_libraries(OCV ${OpenCV_LIBS})