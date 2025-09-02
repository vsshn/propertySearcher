#pragma once

#include <vector>

#include "Links.h"

namespace ps {

class LinksProviderIf {
 public:
  virtual ~LinksProviderIf() = default;
  virtual std::vector<Link> getLinks() const = 0;
};

}  // namespace ps