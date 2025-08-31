#include "RightmoveListingsProvider.h"

namespace ps {

RightmoveListingsProvider::RightmoveListingsProvider(
    std::unique_ptr<CurlWrapperIf> curlWrapper, const std::string baseUrl)
    : curlWrapper_(std::move(curlWrapper)), baseUrl_(std::move(baseUrl)) {}

std::vector<Listing> RightmoveListingsProvider::getListings() const {
  return {Listing{.numBedrooms = 3, .price = 3000, .url = "Huh?"}};
}

}  // namespace ps