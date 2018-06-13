project(graphAM C CXX)
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


add_definitions(-D__STDC_FORMAT_MACROS)
add_definitions(-DUSE_IMPORT_EXPORT)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")
SET(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -fprofile-arcs -ftest-coverage")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# ------------------------------------------------------------------------------
# find_libraries macro
# ------------------------------------------------------------------------------
macro(find_libraries)
    # find glog---------------------------------------------------------------------
    include("cmake/FindGlog.cmake")

    # find gflags-------------------------------------------------------------------
    include("cmake/FindGFlags.cmake")

    # find boost--------------------------------------------------------------------
    find_package(Boost COMPONENTS system filesystem)
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endmacro(find_libraries)

find_libraries()

# ------------------------------------------------------------------------------
# configure meta-info
# ------------------------------------------------------------------------------
set(_VERSION_MAJOR 0)
set(_VERSION_MINOR 9)
set(_VERSION_PATCH 0)

# ------------------------------------------------------------------------------
# generete libgrape_core
# ------------------------------------------------------------------------------
file(GLOB_RECURSE CORE_SRC_FILES "graph/*.cc")
add_library(graph_core SHARED ${CORE_SRC_FILES})

target_link_libraries(graph_core ${CMAKE_THREAD_LIBS_INIT} ${GLOG_LIBRARIES}
        ${GFLAGS_LIBRARIES} ${CMAKE_DL_LIBS} ${Boost_LIBRARIES})

set(APP_FILES sssp)

set_target_properties(graph_core PROPERTIES INSTALL_RPATH "$ORIGIN/lib:$ORIGIN/")
install(TARGETS graph_core DESTINATION ${GRAPE_INSTALL_HOME}/lib)

## ------------------------------------------------------------------------------
## link submodules
## ------------------------------------------------------------------------------

add_executable(graph-engine graph/main.cc)
target_link_libraries(graph-engine graph_core)
set_target_properties(graph-engine PROPERTIES LINK_FLAGS "-fPIC -rdynamic")
set_target_properties(graph-engine PROPERTIES INSTALL_RPATH "$ORIGIN/lib:$ORIGIN/")

# ------------------------------------------------------------------------------
# generete applications
# ------------------------------------------------------------------------------
#
foreach (f ${APP_FILES})
    file(GLOB APP_VARIANTS RELATIVE "${CMAKE_SOURCE_DIR}/app/${f}" "${CMAKE_SOURCE_DIR}/app/${f}/*.cc")
    foreach (vr ${APP_VARIANTS})
        string(REGEX MATCH "^(.*)\\.[^.]*$" dummy ${vr})
        set(APP_VARIANT_NAME ${CMAKE_MATCH_1})
        set(APP_LIB_NAME app_${APP_VARIANT_NAME})
        message(STATUS "Found application - " ${APP_VARIANT_NAME})
        add_library(${APP_LIB_NAME} SHARED ${CMAKE_SOURCE_DIR}/app/${f}/${vr})
        target_link_libraries(${APP_LIB_NAME} graph_core)
        set_target_properties(${APP_LIB_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
        set_target_properties(${APP_LIB_NAME} PROPERTIES INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")
        install(TARGETS ${APP_LIB_NAME} DESTINATION ${GRAPE_INSTALL_HOME}/lib)
    endforeach (vr ${APP_VARIANTS})
endforeach (f ${APP_FILES})

message("[GraphAM] will build in type: ${CMAKE_BUILD_TYPE}")
# ------------------------------------------------------------------------------
# format code
# ------------------------------------------------------------------------------
file(GLOB FILES_NEED_FORMAT "graph/*.cc" "graph/*.h" "graph/*/*.cc" "graph/*/*.h" "graph/*/*.h" "app/*/*.cc" "app/*/*.h")
add_custom_target(clformat
        COMMAND clang-format --style=Google -i ${FILES_NEED_FORMAT}
        COMMENT "Running clang-format"
        VERBATIM)