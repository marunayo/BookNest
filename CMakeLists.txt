cmake_minimum_required(VERSION 3.26)
project(BookNest)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BookNest
        book.h
        bookController.cpp
        library.cpp
        library.h
        main.cpp
        memberController.cpp)
