#pragma once

#include <memory>

#include "AllPageLinksGeneratorIf.h"
#include "fetcher/CurlWrapperIf.h"

namespace ps {

class RightmoveAllPageLinksGenerator : public AllPageLinksGeneratorIf {
 public:
  virtual std::vector<std::string> getLinksToAllPages(
      const std::string_view firstPageHtml) const override;
};

}  // namespace ps