#pragma once

#include "ListingsProviderIf.h"
#include "fetcher/CurlWrapperIf.h"

namespace ps {

class RightmoveListingsProvider : public ListingsProviderIf {
 public:
  explicit RightmoveListingsProvider(
      std::unique_ptr<CurlWrapperIf> curlWrapper);

  virtual std::vector<Listing> getListings(
      const std::string_view baseUrl) const override;

 private:
  std::unique_ptr<CurlWrapperIf> curlWrapper_;
};
}  // namespace ps