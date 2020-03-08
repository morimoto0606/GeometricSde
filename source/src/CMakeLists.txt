cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -fconcepts)
add_library(sde_geometrization STATIC main.cpp)

# declare external library
set(EIGEN /usr/include/eigen3)
include_directories(${EIGEN})

add_executable(sde_geometraization main.cpp)
target_link_libraries(sde_geometraization)

