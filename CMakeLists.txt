cmake_minimum_required(VERSION 3.20)

set(LIBRARY_NAME "Helpers")

project(${LIBRARY_NAME} LANGUAGES C )

set(CMAKE_C_STANDARD 99)
if (NOT WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
endif()

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# library info

set(PROJECT_DESCRIPTION "Helpers library for C applications")
set(PROJECT_HOMEPAGE_URL "https://github.com/toshaTikhonov/Helpers.git")
set(PROJECT_BUGREPORT_PATH "https://github.com/toshaTikhonov/Helpers/issues")

set(LIBRARY_VERSION_MAJOR "0")
set(LIBRARY_VERSION_MINOR "3")
set(LIBRARY_VERSION_PATCH "0")

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

option(MEMORY_POOL_STATIC "Static pool memory." OFF)
if (MEMORY_POOL_STATIC)
    add_definitions(-DSTATIC_MEMORY_POOL)
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
        ${SRC_DIR}/h_memory.c
        ${SRC_DIR}/h_memmgr.c
        ${INC_DIR}/h_str.h
        ${INC_DIR}/h_bin.h
        ${INC_DIR}/h_cpc.h
        ${INC_DIR}/h_lggr.h
        ${INC_DIR}/h_memory.h
        ${INC_DIR}/h_memmgr.h
        )
# shared library

add_library(${LIBRARY_NAME} SHARED ${SRC_FILES})
if (NOT WIN32)
    set_target_properties(${LIBRARY_NAME} PROPERTIES
            COMPILE_OPTIONS -Wextra
            PUBLIC_HEADER "${INC_DIR}/h_bin.h;${INC_DIR}/h_cpc.h;${INC_DIR}/h_lggr.h;${INC_DIR}/h_str.h;${INC_DIR}/h_memory.h;${INC_DIR}/h_memmgr.h;${PROJECT_BINARY_DIR}/helpers-cfg.h"
            VERSION "${LIBRARY_VERSION}"
            SOVERSION "${LIBRARY_SOVERSION}")
endif()
if (WIN32)
set_target_properties(${LIBRARY_NAME} PROPERTIES SUFFIX "-${LIBRARY_VERSION}.dll")
endif ()
# static library

option(BUILD_STATIC "Build static library." OFF)

if (BUILD_STATIC)
    add_library(Helpers_static STATIC ${SRC_FILES})
    target_compile_definitions(Helpers_static PUBLIC -DO_STATIC_LIBRARY)
    set_target_properties(Helpers_static PROPERTIES
            OUTPUT_NAME ${LIBRARY_NAME})
endif ()

target_link_libraries(${LIBRARY_NAME} ${LIBS})

# build helpers-cfg.h file
configure_file(${INC_DIR}/helpers-cfg.h.in ${PROJECT_BINARY_DIR}/helpers-cfg.h)
set (CMAKE_EXTRA_INCLUDE_FILES ${PROJECT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR})

# documentation

option(BUILD_HELPERS_DOCUMENTATION "Build the documentation." OFF)
if (BUILD_HELPERS_DOCUMENTATION)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen.cfg)
        set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

        configure_file(${doxyfile_in} ${doxyfile} @ONLY)

        add_custom_target(doc
                COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile_in}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Generating documentation with Doxygen"
                VERBATIM)

    else ()
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif ()
endif ()

# tests

option(BUILD_HELPERS_TESTING "Build the testing tree." OFF) # because we don not use include(CTest)

if (BUILD_HELPERS_TESTING)
    include(FindCheck)
    find_package(Check)
    if (CHECK_FOUND)
        if (NOT WIN32 AND NOT APPLE)
            include(FindSubunit)
            find_package(Subunit REQUIRED)
        endif ()

        enable_testing()

        set(CMAKE_CTEST_COMMAND ctest -V)

        set(TST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
        set(LIBS ${LIBRARY_NAME} ${LIBS} ${CHECK_LIBRARIES})
        if (NOT WIN32)
            find_package(Threads REQUIRED)
            set(LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT} m)
        endif ()
        if (NOT APPLE)
            set(LIBS ${LIBS} rt)
        endif ()
        if (NOT WIN32 AND NOT APPLE)
            set(LIBS ${LIBS} ${SUBUNIT_LIBRARIES})
        endif ()

        set(TESTS helpers_test)

        configure_file(
                "${CMAKE_MODULE_PATH}/CTestCustom.cmake.in"
                "${CMAKE_CURRENT_BINARY_DIR}/CTestCustom.cmake"
                @ONLY)

        foreach (t ${TESTS})
            add_executable(${t} EXCLUDE_FROM_ALL ${TST_DIR}/${t}.c)
            target_include_directories(${t} PUBLIC ${TST_DIR} ${CHECK_INCLUDE_DIRS} ${SUBUNIT_INCLUDE_DIRS})
            target_link_libraries(${t} PUBLIC ${LIBS})
            add_test(NAME ${t}
                    WORKING_DIRECTORY ${TST_DIR}
                    COMMAND ${t})
        endforeach ()
    endif ()
endif ()

# install target

option(INSTALL_HEADER "Install the header files" ON) # Install header file or not

configure_file(lib${LIBRARY_NAME}.pc.in lib${LIBRARY_NAME}.pc @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${LIBRARY_NAME}.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

set(TARGETS ${LIBRARY_NAME})
if (BUILD_STATIC)
    set(TARGETS ${TARGETS} Helpers_static)
endif ()

if (INSTALL_HEADER)
    install(TARGETS ${TARGETS}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(FILES README.md
            DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT runtime)
else ()
    install(TARGETS ${TARGETS}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif ()

# uninstall target

if (NOT TARGET uninstall)
    configure_file(
            "${CMAKE_MODULE_PATH}/CMakeUninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)
    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif ()

# packaging

set(CPACK_PACKAGE_VERSION_MAJOR ${LIBRARY_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${LIBRARY_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${LIBRARY_VERSION_PATCH})

if (INSTALL_HEADER)
    set(PACKAGE_FILE_NAME
            "lib${CMAKE_PROJECT_NAME}-dev_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
else ()
    set(PACKAGE_FILE_NAME
            "lib${CMAKE_PROJECT_NAME}_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
endif ()
set(PACKAGE_IGNORED_FILES
        "${CMAKE_CURRENT_BINARY_DIR}/;/.git/;.gitignore;~$;${CPACK_SOURCE_IGNORE_FILES}")

set(CPACK_PACKAGE_NAME "libHelpers")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Helpers funcs library for C applications")
set(CPACK_GENERATOR "TGZ;DEB")
set(CPACK_PACKAGE_VERSION_MAJOR ${LIBRARY_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${LIBRARY_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${LIBRARY_VERSION_PATCH})

option(BUILD_RPM "Build a RPM for your system" OFF)
if (BUILD_RPM)
  set(CPACK_GENERATOR "TGZ")
  set(CPACK_RPM_PACKAGE_LICENSE "LGPL")
  set(CPACK_RPM_PACKAGE_URL "https://github.com/toshaTikhonov/Helpers/")
endif ()

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "support@armshine.net")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.4)")

set(CPACK_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME})
set(CPACK_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME})

set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME})
set(CPACK_SOURCE_IGNORE_FILES ${PACKAGE_IGNORED_FILES})

include(CPack)

add_custom_target(dist_helpers
        COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

message(STATUS "Build static library: ${BUILD_STATIC}")
message(STATUS "Build testing tree: ${BUILD_HELPERS_TESTING}")
message(STATUS "Install the header files: ${INSTALL_HEADER}")
message(STATUS "Build RPM package: ${BUILD_RPM}")
message(STATUS "Build documentation: ${BUILD_HELPERS_DOCUMENTATION}")
