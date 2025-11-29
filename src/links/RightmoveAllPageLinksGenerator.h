#pragma once

#include <memory>

#include "AllPageLinksGeneratorIf.h"
#include "fetcher/CurlWrapperIf.h"

namespace ps {

class RightmoveAllPageLinksGenerator : public AllPageLinksGeneratorIf {
 public:
  /**
   * @brief Returns links to all pages given the first page
   * !! IMPORTANT!! Expects that the link to first page doesn't contain
   * "&index=0" for now.
   *
   * @param webPage
   * @return std::vector<std::string>
   */
  virtual std::vector<std::string> getLinksToAllPages(
      const WebPage& webPage) const override;
};

}  // namespace ps