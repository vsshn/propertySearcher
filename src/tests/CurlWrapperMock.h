#pragma once
#include <gmock/gmock.h>

#include "fetcher/CurlWrapperIf.h"

namespace ps {

class MockCurlWrapper : public CurlWrapperIf {
 public:
  MOCK_METHOD(std::optional<std::string>, getHtmlFrom,
              (const std::string_view url), (override));
};

}  // namespace ps