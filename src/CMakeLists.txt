# Definitions

add_definitions(-DBUILDING_NODE_EXTENSION=1 -DEXTERNAL_NAPI=1)

# Node

if (WIN32)
    set(NODE_FILE "libnode.lib")
else ()
    set(NODE_FILE "libnode.so.108")
endif ()

if (WIN32)
    set(SYS_PATH "win/${TARGET_BUILD_ARCH}")
else ()
    set(SYS_PATH "linux/${TARGET_BUILD_ARCH}")
endif ()

set(NODE_PATH "${PROJECT_SOURCE_DIR}/deps/node/lib/${SYS_PATH}")

include_directories(
    ${PROJECT_SOURCE_DIR}/deps/node/include/node
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
    set(LIBRARIES ${NODE_FILE} shlwapi dbghelp winmm)
else ()
    target_link_libraries(${PROJECT_NAME} ${NODE_PATH}/${NODE_FILE})

    set(LIBRARIES ${node} pthread dl m)

    set_target_properties(${PROJECT_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN/..:$ORIGIN/")

    set(CMAKE_CXX_FLAGS "-Wno-int-to-pointer-cast -Wno-attributes ${CMAKE_CXX_FLAGS}")
    set(CMAKE_C_FLAGS "-Wno-int-to-pointer-cast -Wno-attributes ${CMAKE_C_FLAGS}")

    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
endif ()

target_link_libraries(${PROJECT_NAME}
    ${LIBRARIES}
    OMP-CAPI
    OMP-SDK
    node-lib
    ghc_filesystem
    omp-node-sdk
)