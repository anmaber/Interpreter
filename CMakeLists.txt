cmake_minimum_required(VERSION 3.14)
project(interpreter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(plugin)

include_directories(inc)
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}  dl)
target_link_libraries(${PROJECT_NAME}  Interp4Move Interp4Set Interp4Pause)