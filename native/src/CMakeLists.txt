project(omp-ipc-node LANGUAGES C CXX VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

find_program(NODE_PATH node)
execute_process(COMMAND ${NODE_PATH} -v OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NODE_VERSION)

if(NOT DEFINED NODE_VERSION OR NODE_VERSION STREQUAL "")
    message(FATAL_ERROR "Could't specify your system's node version")
endif()

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

# Add include directories to the project

include_directories(
    ${PROJECT_SOURCE_DIR}/../deps/json
    ${PROJECT_SOURCE_DIR}/../deps/napi
    ${PROJECT_SOURCE_DIR}/../deps/node/node-${NODE_VERSION}/include/node
    ${PROJECT_SOURCE_DIR}
)

# Linking

conan_cmake_run(REQUIRES nng/1.5.2
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

file(GLOB_RECURSE OMPIPCNODE_FILES
    *.hpp
    *.h
    *.cpp
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
