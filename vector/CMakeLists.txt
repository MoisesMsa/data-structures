cmake_minimum_required(VERSION 3.5)
project (DRIVER_CANVAS VERSION 1.0.0 LANGUAGES CXX )



# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#=== FINDING PACKAGES ===#

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 11)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall -g" )
#set( PREPROCESSING_FLAGS  "-D DEBUG")
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}" )

#Include dir
include_directories( include )

#=== Main App ===
#Can manually add the sources using the set command as follows:
set(SOURCES src/main.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(vector ${SOURCES})
target_link_libraries(vector ${GTEST_LIBRARIES} pthread)
