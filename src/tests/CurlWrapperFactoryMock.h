#pragma once
#include <gmock/gmock.h>

#include "fetcher/CurlWrapperFactoryIf.h"

namespace ps {

class MockCurlWrapperFactory : public CurlWrapperFactoryIf {
 public:
  MOCK_METHOD(std::unique_ptr<CurlWrapperIf>, create, (), (const, override));
};

}  // namespace ps