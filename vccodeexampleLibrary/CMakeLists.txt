cmake_minimum_required(VERSION 3.0.0)
project(libraryexample VERSION 0.1.0)

include(CTest)
enable_testing()

#add_library(libraryexample libraryexample.cpp) # for static library
add_library(libraryexample SHARED libraryexample.cpp) # for shared library

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
