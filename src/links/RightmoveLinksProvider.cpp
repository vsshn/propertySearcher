#include "RightmoveLinksProvider.h"

namespace ps {

RightmoveLinksProvider::RightmoveLinksProvider(
    std::unique_ptr<CurlWrapperFactoryIf> curlWrapperFactory,
    const std::vector<std::string> baseUrls)
    : curlWrapperFactory_(std::move(curlWrapperFactory)),
      curlWrapper_(curlWrapperFactory_->create()),
      baseUrls_(std::move(baseUrls)) {}

std::vector<Link> RightmoveLinksProvider::getLinks() const {
  auto maybeString = curlWrapper_->getHtmlFrom("somewhere");
  if (maybeString) {
    return {Link{.url = maybeString.value()}};
  }

  return {};
}

}  // namespace ps