cmake_minimum_required(VERSION 3.5)

project(example)

include_directories(PROJECT_SOURCE_DIR PROJECT_SOURCE_DIR/../include)

aux_source_directory(. DIR_SRCS)

add_executable(test ${DIR_SRCS})

find_library(PATHMUDUO mymuduo PROJECT_SOURCE_DIR/../lib)
target_link_libraries(test mymuduo pthread)

