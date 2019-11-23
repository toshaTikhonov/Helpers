cmake_minimum_required(VERSION 3.5.1)

set(LIBRARY_NAME "Helpers")

project(${LIBRARY_NAME} LANGUAGES C )
message( STATUS ${LIBRARY_NAME})

set(LIB_DIR "..")
set(SRC_DIR ".")

set(SRC_FILES 
		${SRC_DIR}/h_str.c
		${SRC_DIR}/h_bin.c
		${SRC_DIR}/h_cpc.c
		)

add_library(${LIBRARY_NAME} STATIC ${SRC_FILES})

