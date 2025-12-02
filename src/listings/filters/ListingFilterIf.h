#pragma once

#include "listings/Listing.h"

namespace ps {

/**
 * @brief Interface, representating a filter for listings
 *
 */
class ListingFilterIf {
 public:
  virtual ~ListingFilterIf() = default;

  /**
   * @brief Returns whether the listing passes the filter
   *
   * @param listing to be filtered
   * @return bool - true if the listing passes the filter, false otherwise
   */
  virtual bool filterListing(const Listing& listing) const = 0;
};

}  // namespace ps