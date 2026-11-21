cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME_ID kopala)
project(${PROJECT_NAME_ID} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_library(kopala_proto proto/kopala/v1/health.proto)
target_link_libraries(kopala_proto PUBLIC protobuf::libprotobuf gRPC::grpc++)
target_include_directories(kopala_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate(TARGET kopala_proto IMPORT_DIRS proto)

protobuf_generate(
    TARGET kopala_proto
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS proto
)

add_executable(proto_smoke tools/proto_smoke.cpp)
target_link_libraries(proto_smoke PRIVATE kopala_proto)

add_executable(kopala_agent agent/main.cpp)
target_link_libraries(kopala_agent PRIVATE kopala_proto)
