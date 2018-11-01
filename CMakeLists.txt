#CMAKE TO MAKE A STATIC LIBRARY
#HEADER
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
set(TARGET_NAME FS)
project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 17)

#Installation directory 
get_filename_component(GTECH_DIR $ENV{GTECH_ROOT} ABSOLUTE)
set(GTECH_DIR_LIB ${GTECH_DIR}/3rd/lib/)
set(GTECH_DIR_INC ${GTECH_DIR}/3rd/include/)
set(GTECH_DIR_INC_FS ${GTECH_DIR}/3rd/include/FS)

#DIRECTORIES
get_filename_component(ROOT_DIR "." ABSOLUTE)
message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "ROOT_DIR: ${ROOT_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "-----------------------------")


add_executable(path_demo path_demo.cpp filesystem/path.h filesystem/resolver.h)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_BUILD_TYPE debug)
target_include_directories(path_demo PUBLIC
	${GTECH_DIR_INC})



file(MAKE_DIRECTORY ${GTECH_DIR_INC_FS})

execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/filesystem/fwd.h ${GTECH_DIR_INC_FS}) 
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/filesystem/path.h ${GTECH_DIR_INC_FS}) 
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/filesystem/resolver.h ${GTECH_DIR_INC_FS}) 
