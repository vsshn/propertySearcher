#pragma once

#include <string_view>
#include <vector>

#include "Listing.h"

namespace ps {
class ListingsProviderIf {
 public:
  virtual ~ListingsProviderIf() = default;
  virtual std::vector<Listing> getListings(
      const std::string_view html) const = 0;
};
}  // namespace ps