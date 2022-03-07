cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(OpenGLExample)

set(CMAKE_CXX_STANDARD 14)


unset(GLFW_LIB_DIR CACHE) # calls to force CMake to search for the library each time. 


set(GLFW_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/GLFW")

message(STATUS "finding libraries in " ${GLFW_LIB_DIR} )

find_library(libglfw 
            NAMES ${CMAKE_SHARED_LIBRARY_PREFIX}glfw${CMAKE_SHARED_LIBRARY_SUFFIX} 
            PATHS "${GLFW_LIB_DIR}" 
            HINTS "${GLFW_LIB_DIR}"
            DOC "GLFW library")

find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL GLX)
include_directories(${OPENGL_INCLUDE_DIRS})
if(OPENGL_FOUND)
    message("Found OpenGL in the current environment!")
else()
    message("Error: No OpenGL found.")
endif()

if (${libglfw} STREQUAL libglfw-NOTFOUND)
    message(FATAL_ERROR "libglfw not found!!")
else()
    message(STATUS "libglfw found!")
endif()

# include directories
include_directories("libs/" ${OPENGL_INCLUDE_DIRS} )

# Define the executable
add_executable(OpenGLExample src/main.cpp)

# dependency on the my_libary target defined in other subprojecttarget_link_libraries(my_executable PRIVATE my_library)
target_link_libraries(OpenGLExample ${libglfw} ${OPENGL_LIBRARIES})



