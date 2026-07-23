cmake_minimum_required(VERSION 3.5)
project(SimplePassword LANGUAGES CXX)

set(bin spass)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/generation.cpp)

add_executable(${bin} ${CXX_SOURCES})

target_include_directories(${bin} PRIVATE ${CMAKE_SOURCE_DIR}/include)
