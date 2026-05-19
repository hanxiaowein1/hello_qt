cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)
set(LIBIGL_WITH_CGAL ON)
set(CMAKE_TOOLCHAIN_FILE "D:\\Library\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")
# set(CMAKE_PREFIX_PATH "D:\\OwnLibrary" ${CMAKE_PREFIX_PATH})
list(APPEND CMAKE_PREFIX_PATH "D:/OwnLibrary")

project(hello_qt)

# this is for export libary for external use
set(CMAKE_INSTALL_PREFIX "D:/OwnLibrary")

add_subdirectory(qt5_demo)
