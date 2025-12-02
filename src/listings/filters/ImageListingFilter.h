#pragma once

#include "ListingFilterIf.h"

namespace ps {

/**
 * @brief A filter based on the analysis of the images in the listing,
 * specifically whether the images match a given prompt well.
 * Ex:
 *  prompt: "The flat interior is bright and spacious, with modern furniture and
 *           decor."
 *  response: if images match the prompt well enough -> pass the filter
 */
class ImageListingFilter : public ListingFilterIf {
 public:
  /**
   * @brief Returns whether the listing passes the filter
   *
   * @param listing
   * @return true if the images linked in the listing match the prompt well
   * enough, false otherwise
   */
  virtual bool filterListing(const Listing& listing) const override;
};

}  // namespace ps