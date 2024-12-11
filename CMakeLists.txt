cmake_minimum_required(VERSION 3.30)

project(PanDa)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(test)
add_subdirectory(src)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

enable_testing()

