cmake_minimum_required(VERSION 3.19)
project(omp-node LANGUAGES C CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    add_definitions(
            -D_CRT_SECURE_NO_WARNINGS
            -DWIN32_LEAN_AND_MEAN
    )
endif ()

add_subdirectory(deps/node)
add_subdirectory(deps/sdk)
add_subdirectory(src)
