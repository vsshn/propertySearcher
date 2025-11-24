#include "Listing.h"

namespace ps {

namespace {

std::string join(const std::vector<std::string>& toJoin) {
  auto begin = toJoin.begin();
  auto end = toJoin.end();
  if (begin == end) {
    return "";
  }
  std::string result;
  result += *begin;
  begin++;

  for (auto it = begin; it != end; it++) {
    result += ", ";
    result += *it;
  }

  return result;
}

}  // namespace

// PrintTo for GoogleTest
void PrintTo(const Listing& listing, std::ostream* os) {
  *os << "Listing{.price = " << listing.price << ", ";
  *os << ".numBedrooms = " << static_cast<uint16_t>(listing.numBedrooms)
      << ", ";
  *os << ".url = " << listing.url << ", ";
  *os << ".imageUrls = [" << join(listing.imageUrls) << "]";
}

}  // namespace ps