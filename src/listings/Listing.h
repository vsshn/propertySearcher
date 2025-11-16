#pragma once

#include <ostream>
#include <string>

namespace ps {

struct Listing {
  const uint16_t price{};
  const uint8_t numBedrooms{};
  const std::string url;
  const bool operator<=>(const Listing&) const = default;
};

// PrintTo for GoogleTest
inline void PrintTo(const Listing& listing, std::ostream* os) {
  *os << "Listing{" << listing.price << "}";
}

}  // namespace ps