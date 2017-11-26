# Author: Tegan Burns
# Website: teganburns.com

cmake_minimum_required ( VERSION 3.8.2 )

# Use either one for DEBUGGING
#set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

PROJECT(natural_language C CXX)
include(FindProtobuf)

set( VERSION_MAJOR 1 )
set( VERSION_MINOR 0 )

include(ExternalProject)

# External gRPC
set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add( grpc
    GIT_REPOSITORY https://github.com/grpc/grpc
	UPDATE_COMMAND git submodule update --init
    #CONFIGURE_COMMAND "" # Disable all other steps
    #BUILD_COMMAND "make"
    #INSTALL_COMMAND ""
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)


# cpp
set ( natural_language_cpp "${PROJECT_SOURCE_DIR}/src/natural_language/natural_language.cpp" )

# hpp
set ( natural_language_hpp "${PROJECT_SOURCE_DIR}/src/natural_language/natural_language.hpp.in" )

# Dirs
set ( natural_language_dir "${PROJECT_SOURCE_DIR}/src/natural_language" )

# proto
set( proto_include_dir "${PROJECT_SOURCE_DIR}/src/proto" )


# REQUIRED
find_package( Protobuf REQUIRED )

# STATUS MESSAGES
message( STATUS "natural_language_hpp: ${natural_language_hpp}")

message( STATUS "protobuf_include_dirs: ${proto_include_dir}" )

message( STATUS "PROTOBUF_FOUND: ${PROTOBUF_FOUND}")
message( STATUS "PROTOBUF_PROTOC_LIBRARIES: ${PROTOBUF_PROTOC_LIBRARIES}")
message( STATUS "PROTOBUF_PROTOC_LIBRARY: ${PROTOBUF_PROTOC_LIBRARY}")
message( STATUS "PROTOBUF_PROTOC_EXECUTABLE: ${PROTOBUF_PROTOC_EXECUTABLE}")

# PROTOCOL BUFFERS
include_directories( ${proto_include_dir} )
protobuf_generate_cpp( PROTO_SRCS PROTO_HDRS ${proto_include_dir}/natural_language.proto )
message( STATUS "PROTO_SRCS: ${PROTO_SRCS}")
message( STATUS "PROTO_HDRS: ${PROTO_HDRS}")

#configure_file (
#    ${natural_language_hpp}
#    "${PROJECT_BINARY_DIR}/src/natural_language.hpp"
#)

include_directories ( 
    ${PROJECT_BINARY_DIR}
    ${natural_language_dir}
    ${EXTERNAL_INSTALL_LOCATION}/include
)

#link_directories(
#    ${EXTERNAL_INSTALL_LOCATION}/lib
#    ${PROTOBUF_PROTOC_LIBRARIES}
#)

#add_library( natural_language_proto ${PROTO_SRC} ${PROTO_HDRS} )
add_executable( natural_language ${natural_language_cpp} ${natural_language_hpp} ${PROTO_SRC} ${PROTO_HDRS} )
add_dependencies( natural_language grpc)
target_link_libraries ( natural_language curl )
target_link_libraries ( natural_language ${PROTOBUF_LIBRARIES} )


# ------------------------- #

#cmake_minimum_required(VERSION 3.0)
#project(GTestProject)

#include(ExternalProject)
#
#set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
#
#ExternalProject_Add(googletest
#    GIT_REPOSITORY https://github.com/google/googletest
#    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
#)
#
#include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
#link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

#add_executable(FirstTest main.cpp)
#add_dependencies(FirstTest googletest)
#target_link_libraries(FirstTest gtest gtest_main pthread)



