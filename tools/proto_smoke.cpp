#include <iostream>

#include "kopala/v1/health.pb.h"

int main() {
  using kopala::v1::CheckResponse;

  CheckResponse resp;

  resp.set_status(CheckResponse::SERVING_STATUS_SERVING);

  std::cout << CheckResponse::ServingStatus_Name(resp.status()) << '\n';

  if (resp.status() != kopala::v1::CheckResponse::SERVING_STATUS_SERVING) {
    std::cerr << "status mismatch\n";

    return 1;
  }

  return 0;
}
