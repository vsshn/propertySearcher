#pragma once

#include <ostream>
#include <string>
#include <vector>

namespace ps {

struct Listing {
  const std::vector<std::string> imageUrls;
  const uint16_t price{};
  const uint16_t numBedrooms{};
  const std::string url;
  bool operator<=>(const Listing&) const = default;
};

// PrintTo for GoogleTest
void PrintTo(const Listing& listing, std::ostream* os);

}  // namespace ps