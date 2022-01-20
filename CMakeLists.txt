cmake_minimum_required(VERSION 3.19)
project(omp-node LANGUAGES C CXX VERSION 0.0.1)



if(WIN32)
    add_definitions(
            -D_CRT_SECURE_NO_WARNINGS
            -DWIN32_LEAN_AND_MEAN
    )
endif()



add_subdirectory(src)
