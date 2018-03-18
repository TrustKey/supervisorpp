cmake_minimum_required(VERSION 3.5)
project(supervisorpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O0 -w")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

#if __APPLE__
        set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)
#endif

find_package(asio REQUIRED)
find_package(kashmir REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(restbed REQUIRED)

INCLUDE_DIRECTORIES(
        ${asio_INCLUDE}
        ${restbed_INCLUDE}
        ${kashmir_INCLUDE}
        dependency/StaticJSON/include
        dependency/args
        dependency/websocketpp
        ${OPENSSL_INCLUDE_DIR}
        )

set(SOURCE_FILES
        main.cpp
        Config.hpp
        SupervisorFacade.cpp
        SupervisorFacade.hpp
        dependency/StaticJSON/src/staticjson.cpp
        Supervisor.cpp Supervisor.hpp)

add_executable(supervisorpp ${SOURCE_FILES})
target_link_libraries(supervisorpp
        ${CMAKE_SOURCE_DIR}/dependency/restbed/build/librestbed.a
        ${OPENSSL_LIBRARIES}
        )