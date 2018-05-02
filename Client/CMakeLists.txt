cmake_minimum_required (VERSION 3.7)

project(Client)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


# Add source to this project's executable.
add_executable(${PROJECT_NAME}
    Client.h
    Client.cpp
    Main.cpp
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Network
)
