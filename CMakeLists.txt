# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(l1t-macros)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)


# Find ROOT (optional package)
#
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net)
if(ROOT_FOUND)
  message(STATUS "G4 Examples: ROOT found. --> iort_therapy example with ROOT enabled.") 
  # Uncomment this line if suitable (some customization may be needed)
  add_definitions(-DG4ANALYSIS_USE_ROOT)   
else()
  message(STATUS "G4 Examples: ROOT not found. --> iort_therapy example with ROOT disabled.") 
endif()

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include_directories(${PROJECT_SOURCE_DIR}/Event ${PROJECT_SOURCE_DIR}/Plotting ${PROJECT_SOURCE_DIR}/Tests ${PROJECT_SOURCE_DIR}/Utilities)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cxx)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*/*.h ${PROJECT_SOURCE_DIR}/*/*.C)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(l1t-macros ${sources} ${headers})
#target_link_libraries(MuonProject_rev2 ${ROOT_LIBRARIES} ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
#add_custom_target(B1 DEPENDS exampleB1)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
#install(TARGETS MuonProject_rev2 DESTINATION bin)


