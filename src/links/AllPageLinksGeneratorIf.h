#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace ps {

class AllPageLinksGeneratorIf {
 public:
  virtual ~AllPageLinksGeneratorIf() = default;

  virtual std::vector<std::string> getLinksToAllPages(
      const std::string_view firstPageLink) const = 0;
};

}  // namespace ps