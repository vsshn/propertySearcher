#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace ps {
class CurlWrapperIf {
 public:
  virtual ~CurlWrapperIf() = default;

  virtual std::optional<std::string> getHtmlFrom(
      const std::string_view url) = 0;
};
}  // namespace ps