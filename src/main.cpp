#include <gflags/gflags.h>

#include <iostream>

#include "fetcher/CurlWrapper.h"
#include "listings/RightmoveListingsProvider.h"

DEFINE_string(base_url, "https://www.york.ac.uk/teaching/cws/wws/webpage1.html",
              "Base RightMove URL.");

int main(int argc, char **argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  gflags::ShowUsageWithFlags(argv[0]);
  auto curlWrapper = std::make_unique<ps::CurlWrapper>();
  auto listingsProvider = std::make_unique<ps::RightmoveListingsProvider>(
      std::move(curlWrapper), FLAGS_base_url);
  std::cout << listingsProvider->getListings().size() << std::endl;
}