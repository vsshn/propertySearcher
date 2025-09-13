#pragma once

#include <string_view>
#include <vector>

#include "Links.h"

namespace ps {

class LinksProviderIf {
 public:
  virtual ~LinksProviderIf() = default;
  virtual std::vector<Link> getLinks(const std::string_view baseUrl) const = 0;
};

}  // namespace ps