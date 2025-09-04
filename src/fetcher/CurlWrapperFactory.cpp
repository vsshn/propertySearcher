#include "fetcher/CurlWrapperFactory.h"

#include "fetcher/CurlWrapper.h"

namespace ps {

std::unique_ptr<CurlWrapperIf> CurlWrapperFactory::create() const {
  return std::make_unique<CurlWrapper>();
}

}  // namespace ps