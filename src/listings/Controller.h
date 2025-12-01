#pragma once

#include <memory>
#include <string_view>
#include <vector>

#include "Listing.h"
#include "ListingsProviderIf.h"
#include "fetcher/CurlWrapperIf.h"
#include "links/AllPageLinksGeneratorIf.h"
#include "links/Links.h"

namespace ps {

class Controller {
 public:
  explicit Controller(
      std::unique_ptr<ListingsProviderIf> listingsProvider,
      std::unique_ptr<AllPageLinksGeneratorIf> allPageLinksGenerator,
      std::unique_ptr<CurlWrapperIf> curlWrapper);

  std::vector<Link> getAllInterestingLinks(
      const std::string_view baseUrl) const;

 private:
  std::vector<Link> getAllInterestingLinksFromPage(
      const std::string_view pageHtml) const;

  const std::unique_ptr<const ListingsProviderIf> listingsProvider_;
  const std::unique_ptr<const AllPageLinksGeneratorIf> allPageLinksGenerator_;
  const std::unique_ptr<CurlWrapperIf> curlWrapper_;
};

}  // namespace ps
