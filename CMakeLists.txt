cmake_minimum_required(VERSION 3.20)
project(
  SimplePassword
  VERSION 0.1.1
  LANGUAGES CXX
)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Release
      CACHE STRING "Build type" FORCE
  )
endif()

set(bin spass)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GEN_DIR})

add_custom_command(
  OUTPUT ${GEN_DIR}/words_data.hpp
  COMMAND xxd -i words.txt ${GEN_DIR}/words_data.hpp
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/assets
  DEPENDS ${CMAKE_SOURCE_DIR}/assets/words.txt
  COMMENT "Generating words_data.hpp from words.txt via xxd"
)

set(CXX_SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/generation.cpp
                ${CMAKE_SOURCE_DIR}/src/default_word_list.cpp ${GEN_DIR}/words_data.hpp
)

add_executable(${bin} ${CXX_SOURCES})

target_include_directories(${bin} PRIVATE ${CMAKE_SOURCE_DIR}/include ${GEN_DIR})

install(TARGETS ${bin} DESTINATION bin)
