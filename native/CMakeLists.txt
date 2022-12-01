cmake_minimum_required(VERSION 3.19)
project(omp-ipc-node)

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

add_subdirectory(src)
