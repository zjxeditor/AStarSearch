cmake_minimum_required(VERSION 3.10)
project(AStarSearch C)
set(CMAKE_C_STANDARD 11)

# Build type check
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
            "MinSizeRel" "RelWithDebInfo")
endif ()
if (CMAKE_BUILD_TYPE MATCHES RELEASE)
    add_definitions(-DNDEBUG)
endif ()

# Set the source files
set(AStar_SOURCE
        Source/Asearch.c
        Source/board.c
        Source/queue.c)

set(AStar_HEADERS
        Source/Asearch.h
        Source/base.h
        Source/board.h
        Source/queue.h)

include_directories(
        Source)

# Main library
add_library(astar SHARED
        ${AStar_SOURCE}
        ${AStar_HEADERS})
if (WIN32 AND MSVC)
    # Avoid a name clash when building on Visual Studio
    set_target_properties(astar PROPERTIES OUTPUT_NAME libastar)
endif ()


