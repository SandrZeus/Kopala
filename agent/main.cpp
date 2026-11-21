#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "kopala/v1/health.grpc.pb.h"

namespace kv1 = kopala::v1;

class HealthService final : public kv1::Health::Service {
public:
  grpc::Status Check(grpc::ServerContext *, const kv1::CheckRequest *,
                     kv1::CheckResponse *response) override {
    response->set_status(kv1::CheckResponse::SERVING_STATUS_SERVING);
    return grpc::Status::OK;
  }
};

int main() {
  const std::string address = "127.0.0.1:50051";

  HealthService service;

  grpc::ServerBuilder builder;
  // TODO: mTLS and bind to the VPN interface.
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
  if (!server) {
    std::cerr << "failed to start agent on " << address << '\n';
    return 1;
  }

  std::cout << "agent listening on " << address << '\n';
  server->Wait();
  return 0;
}
