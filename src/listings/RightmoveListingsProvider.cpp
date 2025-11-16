#include "RightmoveListingsProvider.h"

namespace ps {

RightmoveListingsProvider::RightmoveListingsProvider(
    std::unique_ptr<CurlWrapperIf> curlWrapper)
    : curlWrapper_(std::move(curlWrapper)) {}

std::vector<Listing> RightmoveListingsProvider::getListings(
    const std::string_view baseUrl) const {
  return {Listing{.numBedrooms = 3, .price = 3000, .url = "Huh?"}};
}

}  // namespace ps