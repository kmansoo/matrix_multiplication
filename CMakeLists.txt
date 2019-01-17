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

#
# Add Compiler Option and Macro
#
add_definitions(-std=c++11)

# for OpenMP
set (CMAKE_CXX_FLAGS "-fPIC -Ofast -fopenmp")

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
find_package(OpenMP REQUIRED)

if (NOT OPENMP_FOUND)
  message(FATAL_ERRORO "OpenMP not found. You need to build and install OpenMV before compiling it.")
endif()

#
# Target Names
#
add_executable(mansoo_mat_mul src/mansoo_mat_mul.cxx)
add_executable(opencv_mat_mul src/opencv_mat_mul.cxx)

TARGET_LINK_LIBRARIES(mansoo_mat_mul
  pthread
)

target_link_libraries(opencv_mat_mul
    pthread
    ${OpenCV_LIBS}
)

#
# Make Libraries and Targets
#

# ADD_SUBDIRECTORY(dependency/opencv)

