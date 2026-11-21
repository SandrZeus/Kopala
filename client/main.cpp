#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "kopala/v1/health.grpc.pb.h"

namespace kv1 = kopala::v1;

int main() {
  const std::string address = "127.0.0.1:50051";

  // TODO: mTLS
  std::shared_ptr<grpc::Channel> channel =
      grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
  std::unique_ptr<kv1::Health::Stub> stub = kv1::Health::NewStub(channel);

  grpc::ClientContext context;
  context.set_deadline(std::chrono::system_clock::now() +
                       std::chrono::seconds(2));

  kv1::CheckRequest request;
  kv1::CheckResponse response;
  grpc::Status status = stub->Check(&context, request, &response);

  if (!status.ok()) {
    std::cerr << "health check failed: " << status.error_message() << '\n';
    return 2;
  }

  std::cout << kv1::CheckResponse::ServingStatus_Name(response.status())
            << '\n';

  return 0;
}
