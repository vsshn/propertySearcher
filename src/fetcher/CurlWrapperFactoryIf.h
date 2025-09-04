#pragma once

#include "fetcher/CurlWrapperIf.h"
namespace ps {

class CurlWrapperFactoryIf {
 public:
  virtual ~CurlWrapperFactoryIf() = default;
  virtual std::unique_ptr<CurlWrapperIf> create() const = 0;
};

}  // namespace ps