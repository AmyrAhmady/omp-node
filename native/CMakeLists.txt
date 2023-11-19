cmake_minimum_required(VERSION 3.19)
project(omp-ipc-node LANGUAGES C CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

include(./deps/cmake-conan/conan.cmake)

function(GroupSourcesByFolder target)
    set(SOURCE_GROUP_DELIMITER "/")
    set(last_dir "")
    set(files "")

    get_target_property(sources ${target} SOURCES)

    foreach(file ${sources})
        file(RELATIVE_PATH relative_file "${CMAKE_CURRENT_SOURCE_DIR}" ${file})
        get_filename_component(dir "${relative_file}" PATH)
        if(NOT "${dir}" STREQUAL "${last_dir}")
            if(files)
                source_group("${last_dir}" FILES ${files})
            endif()
            set(files "")
        endif()
        set(files ${files} ${file})
        set(last_dir "${dir}")
    endforeach()

    if(files)
        source_group("${last_dir}" FILES ${files})
    endif()
endfunction()

include(FetchContent)

function(download_file url destination)

    message(STATUS "Downloading ${url}")
    file(DOWNLOAD
        ${url}
        ${destination}
        SHOW_PROGRESS
    )

endfunction(download_file)

find_program(NODE_PATH node)
execute_process(COMMAND ${NODE_PATH} -v OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NODE_VERSION)

if(NOT DEFINED NODE_VERSION OR NODE_VERSION STREQUAL "")
    message(FATAL_ERROR "Could't specify your system's node version")
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/node/node.lib")
    if (WIN32)
    add_definitions(
            -D_CRT_SECURE_NO_WARNINGS
            -DWIN32_LEAN_AND_MEAN
    )

    download_file(
        https://nodejs.org/download/release/${NODE_VERSION}/win-x64/node.lib
        ${CMAKE_SOURCE_DIR}/deps/node/node.lib
    )

    endif ()
endif()


if(NOT EXISTS "${CMAKE_SOURCE_DIR}/deps/node/node-${NODE_VERSION}")
    # Download node include headers

    download_file(
        https://nodejs.org/download/release/v16.17.0/node-${NODE_VERSION}-headers.tar.gz
        ${CMAKE_SOURCE_DIR}/deps/node/headers.tar.gz
    )

    execute_process(COMMAND
        ${CMAKE_COMMAND} -E
        tar xvzf "${CMAKE_SOURCE_DIR}/deps/node/headers.tar.gz"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/deps/node"
    )
endif()

# Add include directories to the project

include_directories(
    ${CMAKE_SOURCE_DIR}/deps/json
    ${CMAKE_SOURCE_DIR}/deps/napi
    ${CMAKE_SOURCE_DIR}/deps/node/node-${NODE_VERSION}/include/node
    ${PROJECT_SOURCE_DIR}
)

conan_cmake_run(REQUIRES nng/1.5.2
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

file(GLOB_RECURSE OMPIPCNODE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.c
)

add_library(${PROJECT_NAME} SHARED ${OMPIPCNODE_FILES})

if (WIN32)
    set(LIBRARIES shlwapi dbghelp winmm)
else ()
    set(LIBRARIES pthread dl m)
endif ()

if (WIN32)
    target_link_libraries(${PROJECT_NAME}
        ${LIBRARIES}
        CONAN_PKG::nng
        ${CMAKE_SOURCE_DIR}/deps/node/node.lib
    )
else ()

endif ()

GroupSourcesByFolder(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".node")
