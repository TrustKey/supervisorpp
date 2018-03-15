cmake_minimum_required(VERSION 3.5)
project(supervisorpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -w")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(asio REQUIRED)
find_package(kashmir REQUIRED)
#find_package(Boost COMPONENTS system REQUIRED)
find_package(restbed REQUIRED)

INCLUDE_DIRECTORIES(${restbed_INCLUDE}
        ${kashmir_INCLUDE}
        ${asio_INCLUDE}
        ${SOURCE_DIR})

set(SOURCE_FILES
        main.cpp)

add_executable(supervisorpp ${SOURCE_FILES} $<TARGET_OBJECTS:restbed>)