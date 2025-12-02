#include "listings/filters/ImageListingFilter.h"

namespace ps {

bool ImageListingFilter::filterListing(const Listing& listing) const {
  // TODO
  return listing.imageUrls.size() >= 5;
}

}  // namespace ps