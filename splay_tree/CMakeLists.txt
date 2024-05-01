cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("Splay-Tree")
# set(MYCOMPILE_FLAGS "-g -fsanitize=address")
# SET(CMAKE_C_FLAGS    "${CMAKE_C_FLAGS} ${MYCOMPILE_FLAGS}")
# SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${MYCOMPILE_FLAGS}")

file(GLOB SRC "src/*")

add_executable(dev-test ${SRC})
target_include_directories(dev-test PUBLIC "include")