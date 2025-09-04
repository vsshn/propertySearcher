#pragma once

#include "fetcher/CurlWrapperFactoryIf.h"
namespace ps {

class CurlWrapperFactory : public CurlWrapperFactoryIf {
  virtual std::unique_ptr<CurlWrapperIf> create() const override;
};

}  // namespace ps