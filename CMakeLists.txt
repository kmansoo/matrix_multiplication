# CMake Version 
CMAKE_MINIMUM_REQUIRED (VERSION 3.8)

# Project Name
PROJECT(matrix_multiplication_performance_test)

#
# Configuration
#
# SET(CMAKE_VERBOSE_MAKEFILE ON)
#

option(USE_OPENCV         "Use OpenCV"  ON)
option(USE_OPENMP         "Use OpenMP"  ON)

#
# Add Compiler Option and Macro
#
add_definitions(-std=c++11)

# for release mode
SET(CMAKE_CXX_FLAGS "-fPIC -Ofast")
 
# set (CMAKE_CXX_FLAGS "-fPIC -Ofast -fopenmp")

# Set Build Directories
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

###########
# OpenCV
###########
if (USE_OPENCV)
  find_package( OpenCV REQUIRED )

  if (NOT OpenCV_FOUND)
    message(STATUS "OpenCV not found")
    set(USE_OPENCV OFF)
  else()
    message(STATUS "OpenCV found")

    add_definitions(-DOPENCV)

    include_directories( ${OpenCV_INCLUDE_DIRS} )
  endif()
endif()

###########
# OpenMP
###########
if (USE_OPENMP)
  find_package(OpenMP)

  if (NOT OPENMP_FOUND)
    message(STATUS "OpenMP not found. You might build and install OpenMV before compiling it if you want to use OpenMP.")
  else()
    add_definitions(-DUSE_OPENMP)
    string(CONCAT CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -fopenmp")
  endif()
endif()


##################
# Source
##################
file(GLOB SRC_FILES 
  src/*.cxx
  src/*.cpp
)

#
# Target Names
#
add_executable(test_mat_mul ${SRC_FILES})

target_link_libraries(test_mat_mul
    pthread
    ${OpenCV_LIBS}
)
