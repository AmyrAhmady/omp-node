cmake_minimum_required(VERSION 3.14)

project(sampgdk LANGUAGES C)

file(GLOB_RECURSE SOURCE_FILES ./*.c ./*.h)
add_library(sampgdk STATIC ${SOURCE_FILES})

# disable warning C4996
target_compile_definitions(sampgdk PRIVATE _CRT_SECURE_NO_WARNINGS SAMPGDK_AMALGAMATION)

target_include_directories(sampgdk PUBLIC ./)
