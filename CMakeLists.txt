cmake_minimum_required(VERSION 3.5)
project(
  SimplePassword
  VERSION 0.1.0
  LANGUAGES CXX
)

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
