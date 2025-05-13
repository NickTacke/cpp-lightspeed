# Project setup
cmake_minimum_required(VERSION 3.10)
project(cpp-lightspeed CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the library
file(GLOB_RECURSE LIGHTSPEED_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)
add_library(cpp-lightspeed STATIC ${LIGHTSPEED_SOURCES})

# Specify the include directories for the library
target_include_directories(cpp-lightspeed
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
        $<INSTALL_INTERFACE:include> 
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/httplib>
)

# Link dependencies
find_package(OpenSSL REQUIRED)
target_link_libraries(cpp-lightspeed
    PUBLIC
        OpenSSL::SSL
        OpenSSL::Crypto
)
if(WIN32)
  target_link_libraries(cpp-lightspeed PRIVATE ws2_32 crypt32) # Usually PRIVATE for system libs
endif()

# Progress notification
message(STATUS "Configuring cpp-lightspeed library from: ${CMAKE_CURRENT_SOURCE_DIR}")