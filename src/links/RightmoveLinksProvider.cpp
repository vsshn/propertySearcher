#include "RightmoveLinksProvider.h"

namespace ps {

RightmoveLinksProvider::RightmoveLinksProvider(
    std::unique_ptr<CurlWrapperFactoryIf> curlWrapperFactory)
    : curlWrapperFactory_(std::move(curlWrapperFactory)),
      curlWrapper_(curlWrapperFactory_->create()) {}

std::vector<Link> RightmoveLinksProvider::getLinks(
    const std::string_view baseUrl) const {
  std::vector<Link> links;
  return links;
}

}  // namespace ps