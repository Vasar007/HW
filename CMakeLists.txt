cmake_minimum_required (VERSION 3.7)

project(HW)

if(WIN32)
    set (CMAKE_PREFIX_PATH "C:\\Qt\\5.10.1\\msvc2017_64\\")
endif()

find_package(Qt5 COMPONENTS Core Network REQUIRED)

# Set compiler options.
if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -Wpedantic -lpthread)
endif()

set (CMAKE_PREFIX_PATH "/usr/include/x86_64-linux-gnu/qt5")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include sub-projects.
add_subdirectory(Client)
add_subdirectory(Server)
