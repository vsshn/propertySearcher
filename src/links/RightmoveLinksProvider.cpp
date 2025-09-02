#include "RightmoveLinksProvider.h"

namespace ps {

RightmoveLinksProvider::RightmoveLinksProvider(
    std::unique_ptr<CurlWrapperIf> curlWrapper,
    const std::vector<std::string> baseUrls)
    : curlWrapper_(std::move(curlWrapper)), baseUrls_(std::move(baseUrls)) {}

std::vector<Link> RightmoveLinksProvider::getLinks() const {
  auto maybeString = curlWrapper_->getHtmlFrom("somewhere");
  if (maybeString) {
    return {Link{.url = maybeString.value()}};
  }

  return {};
}

}  // namespace ps