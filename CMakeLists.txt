project(GraphAM C CXX)
cmake_minimum_required(VERSION 2.8)

set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(CheckLibraryExists)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(${CMAKE_SOURCE_DIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")
SET(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -fprofile-arcs -ftest-coverage")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# -----------------------------------------------------------------------------
# find_libraries macro
# -----------------------------------------------------------------------------
macro(find_libraries)
    # find glog ---------------------------------------------------------------
    include("cmake/FindGlog.cmake")

    # find gflags ---------------------------------------------------------------
    include("cmake/FindGFlags.cmake")
endmacro(find_libraries)

find_libraries()

# -----------------------------------------------------------------------------
# generete libgraph_core
# -----------------------------------------------------------------------------
file(GLOB_RECURSE CORE_SRC_FILES "graph/*.cc")
add_library(graph_core SHARED ${CORE_SRC_FILES})

target_link_libraries(graph_core ${GLOG_LIBRARIES} ${GFLAGS_LIBRARIES})

add_executable(graph graph/main.cc)
target_link_libraries(graph graph_core)
set_target_properties(graph PROPERTIES LINK_FLAGS "-fPIC -rdynamic")

set(ALGO_FILES sssp)

# -----------------------------------------------------------------------------
# generete graph algorithm
# -----------------------------------------------------------------------------
foreach(f ${ALGO_FILES})
    file(GLOB ALGO_VARIANTS RELATIVE "${CMAKE_SOURCE_DIR}/algo/${f}" "${CMAKE_SOURCE_DIR}/algo/${f}/*.cc")
    foreach(vr ${ALGO_VARIANTS})
        string(REGEX MATCH "^(.*)\\.[^.]*$" dummy ${vr})
        set(ALGO_VARIANT_NAME ${CMAKE_MATCH_1})
        set(ALGO_LIB_NAME algo_${ALGO_VARIANT_NAME})
        message(STATUS "Found Algorithm - " ${ALGO_VARIANT_NAME})
        add_library(${ALGO_LIB_NAME} SHARED ${CMAKE_SOURCE_DIR}/algo/${f}/${vr})
        target_link_libraries(${ALGO_LIB_NAME} graph_core)
        set_target_properties(${ALGO_LIB_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
    endforeach(vr ${ALGO_VARIANTS})
endforeach(f ${ALGO_FILES})

# -----------------------------------------------------------------------------
# format code
# -----------------------------------------------------------------------------
file(GLOB FILES_NEED_FORMAT "graph/*.cc" "graph/*.h" "graph/*/*.cc" "graph/*/*.h" "algo/*/*.cc" "algo/*/*.h")
add_custom_target(clformat
        COMMAND clang-format --style=Google -i ${FILES_NEED_FORMAT}
        COMMENT "Runing clang-format"
        VERBATIM)