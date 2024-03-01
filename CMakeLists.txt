cmake_minimum_required(VERSION 3.26)
project(Kuhn_Poker)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
    src/main.cpp
    src/Node.cpp
    src/Tree.cpp
)

add_executable(kuhnpoker ${SOURCE_FILES})

target_compile_options(kuhnpoker PRIVATE -O3)

target_compile_features(kuhnpoker PRIVATE cxx_std_20)

