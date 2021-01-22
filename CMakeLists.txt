cmake_minimum_required(VERSION 3.12)
project(c-opengl-bench)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"
        )

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(c-opengl-bench main.c)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(c-opengl-bench ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )