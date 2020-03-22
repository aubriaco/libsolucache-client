cmake_minimum_required(VERSION 2.8)

## Use the variable PROJECT_NAME for changing the target name
set( PROJECT_NAME "solucache-client" )

## Set our project name
project(${PROJECT_NAME})


set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_options(-fPIC -O2 -w)

## Use all the *.cpp files we found under this folder for the project
FILE(GLOB SRCS "src/*.cpp")


#set(CMAKE_VERBOSE_MAKEFILE ON)
## Define the executable
add_library(${PROJECT_NAME} SHARED ${SRCS})


target_link_libraries(${PROJECT_NAME} solunet ssl crypto)


include_directories(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/include/")


install(TARGETS ${PROJECT_NAME}
        LIBRARY
          DESTINATION /usr/local/lib
          COMPONENT Libraries)
install(DIRECTORY ../include/ DESTINATION /usr/local/include)


add_executable("test-basic-client" "../tests/basic-client.cpp")
include_directories("test-basic-client" "${CMAKE_SOURCE_DIR}/../include/")
target_link_libraries("test-basic-client" solucache-client solusek ssl crypto)
