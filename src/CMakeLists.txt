# Definitions

add_definitions(-DBUILDING_NODE_EXTENSION=1 -DEXTERNAL_NAPI=1)

# Node

if (WIN32)
    set(NODE_FILE "libnode.dll")
else ()
    set(NODE_FILE "libnode.so.93")
endif ()

if (WIN32)
    set(SYS_PATH "win_${TARGET_BUILD_ARCH}")
else ()
    set(SYS_PATH "linux_${TARGET_BUILD_ARCH}")
endif ()

set(NODE_PATH "${PROJECT_SOURCE_DIR}/deps/node/lib/${SYS_PATH}")

include_directories(
    ${PROJECT_SOURCE_DIR}/deps/node/include/node
    ${PROJECT_SOURCE_DIR}/deps/omp-capi/include
    ${PROJECT_SOURCE_DIR}/deps/json
)

# Linking

link_directories(${NODE_PATH})

file(GLOB_RECURSE OMPNODE_FILES
    *.hpp
    *.cpp
)

add_library(${PROJECT_NAME} SHARED ${OMPNODE_FILES})

GroupSourcesByFolder(${PROJECT_NAME})

if (WIN32)
    set(LIBRARIES libnode shlwapi dbghelp winmm)
else ()
    target_link_libraries(${PROJECT_NAME} ${NODE_PATH}/libnode.so.93)

    set(LIBRARIES ${node} pthread dl m)
endif ()

target_link_libraries(${PROJECT_NAME}
    ${LIBRARIES}
    OMP-SDK
    node-lib
)