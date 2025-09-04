#pragma once

#include "LinksProviderIf.h"
#include "fetcher/CurlWrapperFactoryIf.h"
#include "fetcher/CurlWrapperIf.h"

namespace ps {

class RightmoveLinksProvider : public LinksProviderIf {
 public:
  explicit RightmoveLinksProvider(
      std::unique_ptr<CurlWrapperFactoryIf> curlWrapperFactory,
      std::vector<std::string> baseUrls);

  virtual std::vector<Link> getLinks() const override;

 private:
  std::unique_ptr<CurlWrapperFactoryIf> curlWrapperFactory_;
  std::unique_ptr<CurlWrapperIf> curlWrapper_;
  const std::vector<std::string> baseUrls_;
};

}  // namespace ps