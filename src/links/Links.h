#pragma once

#include <ostream>
#include <string>

namespace ps {

struct Link {
  std::string url;
  const bool operator<=>(const Link&) const = default;
};

// PrintTo for GoogleTest
inline void PrintTo(const Link& link, std::ostream* os) {
  *os << "Link{\"" << link.url << "\"}";
}

}  // namespace ps