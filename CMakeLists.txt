# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.0)

# project name
project(lection1)

# creates the variable EXEC and sets it to hello
set(EXEC main)

# set the C++14 standard
#set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV)

# I../includes
#include_directories(includes)
include_directories(${OpenCV_INCLUDE_DIRS})

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*.cpp)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${EXEC} ${SOURCES} )

target_link_libraries(${EXEC} ${OpenCV_LIBRARIES})
