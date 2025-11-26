#pragma once

#include <memory>

#include "AllPageLinksGeneratorIf.h"
#include "fetcher/CurlWrapperIf.h"

namespace ps {

class RightmoveAllPageLinksGenerator : public AllPageLinksGeneratorIf {
 public:
  explicit RightmoveAllPageLinksGenerator(
      std::unique_ptr<CurlWrapperIf> curlWrapper);

  virtual std::vector<std::string> getLinksToAllPages(
      const std::string_view firstPageLink) const override;

 private:
  const std::unique_ptr<CurlWrapperIf> curlWrapper_;
};

}  // namespace ps