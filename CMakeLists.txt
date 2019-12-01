cmake_minimum_required(VERSION 3.5.1)

set(LIBRARY_NAME "Helpers")

project(${LIBRARY_NAME} LANGUAGES C )

set(CMAKE_C_STANDARD 99)
if (NOT MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
endif()

# library info

set(PROJECT_DESCRIPTION "Helpers library for C applications")
set(PROJECT_HOMEPAGE_URL "https://armshine.net:3000/tosha/Helpers/")
set(PROJECT_BUGREPORT_PATH "https://armshine.net:3000/tosha/Helpers/issues")
set(LIBRARY_VERSION_MAJOR "0")
set(LIBRARY_VERSION_MINOR "0")
set(LIBRARY_VERSION_PATCH "1")
set(PROJECT_VERSION "${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH}")

set(LIBRARY_VERSION "${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH}")
set(LIBRARY_SOVERSION "${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}")

# cmake modules

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

include(GNUInstallDirs)
include(CheckSymbolExists)

# check if _GNU_SOURCE is available

if (NOT _GNU_SOURCE)
    check_symbol_exists(__GNU_LIBRARY__ "features.h" _GNU_SOURCE)

    if (NOT _GNU_SOURCE)
        unset(_GNU_SOURCE CACHE)
        check_symbol_exists(_GNU_SOURCE "features.h" _GNU_SOURCE)
    endif ()
endif ()

if (_GNU_SOURCE)
    add_definitions(-D_GNU_SOURCE)
endif ()

# directories and source

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INC_DIR})


set(SRC_FILES 
		${SRC_DIR}/h_str.c
		${SRC_DIR}/h_bin.c
		${SRC_DIR}/h_cpc.c
		${SRC_DIR}/h_lggr.c
        ${INC_DIR}/h_str.h
        ${INC_DIR}/h_bin.h
        ${INC_DIR}/h_cpc.h
        ${INC_DIR}/h_lggr.h
		)
# shared library

add_library(${LIBRARY_NAME} SHARED ${SRC_FILES})
if (NOT MSVC)
    set_target_properties(${LIBRARY_NAME} PROPERTIES
            COMPILE_OPTIONS -Wextra
            PUBLIC_HEADER "${INC_DIR}/h_bin.h;${INC_DIR}/h_cpc.h;${INC_DIR}/h_lggr.h;${INC_DIR}/h_str.h;${PROJECT_BINARY_DIR}/helpers-cfg.h"
            VERSION "${LIBRARY_VERSION}"
            SOVERSION "${LIBRARY_SOVERSION}")
endif()
if (WIN32)
    set_target_properties(${LIBRARY_NAME} PROPERTIES SUFFIX "-${LIBRARY_VERSION_MAJOR}.dll")
endif ()

# static library

option(BUILD_STATIC "Build static library." OFF)

if (BUILD_STATIC)
    add_library(library_name_static STATIC ${SRC_FILES})
    target_compile_definitions(library_name_static PUBLIC -DO_STATIC_LIBRARY)
    set_target_properties(library_name_static PROPERTIES
            OUTPUT_NAME ${LIBRARY_NAME})
endif ()

target_link_libraries(${LIBRARY_NAME} ${LIBS})

# build helpers-cfg.h file
configure_file(${INC_DIR}/helpers-cfg.h.in ${PROJECT_BINARY_DIR}/helpers-cfg.h)
set (CMAKE_EXTRA_INCLUDE_FILES ${PROJECT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR})
