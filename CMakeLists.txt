project(SRG_LLVM_TUTORIAL)
cmake_minimum_required(VERSION 2.8.12)

#------------------------------------------------------------------------------
# FindLLVM
#------------------------------------------------------------------------------
# If building against a locally built version of LLVM this PATH should be
# something like /path/to/llvm/build/share/llvm/cmake
set(LLVM_DIR "" CACHE FILEPATH "Path to directory containing LLVMConfig.cmake")
find_package(LLVM REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")

if ( "${LLVM_PACKAGE_VERSION}" VERSION_LESS "3.5" )
    message(FATAL_ERROR "Need LLVM >=3.5")
endif()

#set(CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
#message(STATUS "Setting CMAKE_MODULE_PATH to ${CMAKE_MODULE_PATH}")
include_directories("${LLVM_INCLUDE_DIRS}")
add_definitions(${LLVM_DEFINITIONS})

#------------------------------------------------------------------------------
# Set compiler flags
#------------------------------------------------------------------------------
# This unfortunately doesn't add much
add_definitions(${LLVM_DEFINITIONS})

include(CheckCXXCompilerFlag)
macro(add_cxx_flag flag)
    CHECK_CXX_COMPILER_FLAG(${flag} FLAG_SUPPORTED)
    if(FLAG_SUPPORTED)
        add_definitions(${flag})
    else()
        message(FATAL_ERROR "${flag} flag is not supported by ${CMAKE_CXX_COMPILER}")
    endif()
endmacro()

# FIXME: Setting flags this way isn't very portable
add_cxx_flag(-fno-rtti) # Can't use LLVMSupport properly if we have rtti
add_cxx_flag(-std=c++11)

#------------------------------------------------------------------------------
# Handy macro to copy files matching a globbing pattern in the current source
# source directory to the current build directory
#------------------------------------------------------------------------------
macro(copy_files_to_build_dir GLOBS)
    file(GLOB ABSOLUTE_PATH_TO_FILES_TO_COPY ${ARGV})

    foreach(file ${ABSOLUTE_PATH_TO_FILES_TO_COPY})
        get_filename_component(filename ${file} NAME)
        configure_file(${filename} ${filename} COPYONLY)
    endforeach()
endmacro()

add_subdirectory(helloPass)

add_subdirectory(visualisationDemos)
add_subdirectory(stripDeadFunctionsDemo)
add_subdirectory(usingAnalyses)
add_subdirectory(usingIRBuilder)
