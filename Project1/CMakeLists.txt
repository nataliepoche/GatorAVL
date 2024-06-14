cmake_minimum_required(VERSION 3.28)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(build)
include_directories(src)
include_directories(test-io)
include_directories(test-io/expected-output-files)
include_directories(test-io/input-files)
include_directories(test-io/output-files)
include_directories(test-unit)

add_executable(Project1
        build/readme.md
        src/main.cpp
        test-io/expected-output-files/1.txt
        test-io/expected-output-files/2.txt
        test-io/expected-output-files/3.txt
        test-io/expected-output-files/4.txt
        test-io/expected-output-files/5.txt
        test-io/input-files/1.txt
        test-io/input-files/2.txt
        test-io/input-files/3.txt
        test-io/input-files/4.txt
        test-io/input-files/5.txt
        test-io/readme.md
        test-unit/catch.hpp
        test-unit/test.cpp
        readme.md
        src/AVL.h
        test-unit/test2.cpp
        test-unit/test2.cpp
)
