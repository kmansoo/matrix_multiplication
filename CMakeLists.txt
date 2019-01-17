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
option(USE_RELEASE_MODE   "Use release mode for fast execution"  ON)

#
# Add Compiler Option and Macro
#
add_definitions(-std=c++11)

if (USE_RELEASE_MODE)
  set (CMAKE_CXX_FLAGS "-fPIC -Ofast")
endif()

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

#
# Target Names
#
add_executable(mansoo_mat_mul src/mansoo_mat_mul.cxx)
add_executable(opencv_mat_mul src/opencv_mat_mul.cxx)

TARGET_LINK_LIBRARIES(mansoo_mat_mul
  pthread
)

TARGET_LINK_LIBRARIES(opencv_mat_mul
  pthread
)

target_link_libraries(opencv_mat_mul
    ${OpenCV_LIBS} 
)

#
# Make Libraries and Targets
#

# ADD_SUBDIRECTORY(dependency/opencv)

