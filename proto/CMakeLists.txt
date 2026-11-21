add_library(kopala_proto kopala/v1/health.proto)
target_link_libraries(kopala_proto PUBLIC protobuf::libprotobuf gRPC::grpc++)
target_include_directories(kopala_proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate(TARGET kopala_proto IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

protobuf_generate(
    TARGET kopala_proto
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
)
