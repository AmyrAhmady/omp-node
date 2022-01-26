# Definitions

add_definitions(-DBUILDING_NODE_EXTENSION=1 -DEXTERNAL_NAPI=1)

# Node

if (WIN32)
    set(NODE_FILE "libnode.dll")
else ()
    set(NODE_FILE "libnode.so.93")
endif ()

if (WIN32)
    set(SYS_PATH win32)
else ()
    set(SYS_PATH linux)
endif ()

set(NODE_PATH "${PROJECT_SOURCE_DIR}/deps/node/lib/Release/${SYS_PATH}")

# Dependencies

add_subdirectory(
        ${PROJECT_SOURCE_DIR}/deps/sdk deps/sdk
)

include_directories(
        ${PROJECT_SOURCE_DIR}/deps/node/include
        ${PROJECT_SOURCE_DIR}/deps/v8
        ${PROJECT_SOURCE_DIR}/deps/uv
)

# Linking

link_directories(${NODE_PATH})

file(GLOB_RECURSE OMPNODE_FILES
        *.hpp
        *.cpp
        )

add_library(${PROJECT_NAME} SHARED ${OMPNODE_FILES})

if (WIN32)
    set(LIBRARIES v8_libbase v8_libplatform libnode shlwapi dbghelp winmm)
else ()
    target_link_libraries(${PROJECT_NAME} ${NODE_PATH}/libnode.so.93)

    set(LIBRARIES ${node} pthread dl m)
endif ()

target_link_libraries(${PROJECT_NAME}
        ${LIBRARIES}
        SDK
        )