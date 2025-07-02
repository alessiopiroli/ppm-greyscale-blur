cmake_minimum_required(VERSION 3.10)
project(ppm-greyscale-blur)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(SOURCES scripts/main.cpp)
add_executable(ppm-greyscale-blur ${SOURCES})

target_include_directories(ppm-greyscale-blur PRIVATE scripts)

if(OpenMP_CXX_FOUND)
    target_link_libraries(ppm-greyscale-blur OpenMP::OpenMP_CXX)
endif()