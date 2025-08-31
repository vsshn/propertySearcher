#pragma once

#include "ListingsProviderIf.h"
#include "fetcher/CurlWrapperIf.h"

namespace ps {

class RightmoveListingsProvider : public ListingsProviderIf {
 public:
  explicit RightmoveListingsProvider(std::unique_ptr<CurlWrapperIf> curlWrapper,
                                     std::string baseUrl);

  virtual std::vector<Listing> getListings() const override;

 private:
  std::unique_ptr<CurlWrapperIf> curlWrapper_;
  const std::string baseUrl_;
};
}  // namespace ps