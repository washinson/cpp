cmake_minimum_required(VERSION 3.20)
project(hw1-long-alg)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)

add_subdirectory(tests)

include_directories(long-alg_lib)
add_subdirectory(long-alg_lib)

#add_executable(hw1-long-alg main.cpp)
add_executable(long-alg_run ${SOURCE_FILES})

target_link_libraries(long-alg_run long-alg_lib)