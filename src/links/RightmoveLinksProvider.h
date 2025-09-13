#pragma once

#include "LinksProviderIf.h"
#include "fetcher/CurlWrapperFactoryIf.h"
#include "fetcher/CurlWrapperIf.h"

namespace ps {

class RightmoveLinksProvider : public LinksProviderIf {
 public:
  explicit RightmoveLinksProvider(
      std::unique_ptr<CurlWrapperFactoryIf> curlWrapperFactory);

  virtual std::vector<Link> getLinks(
      const std::string_view baseUrl) const override;

 private:
  std::unique_ptr<CurlWrapperFactoryIf> curlWrapperFactory_;
  std::unique_ptr<CurlWrapperIf> curlWrapper_;
};

}  // namespace ps