#include "StringManip.h"

#include <string>

namespace ps::string_manip {

std::optional<size_t> findStartOfSubstringInString(
    const std::string_view stringToSearchIn, const std::string_view toFind,
    size_t pos) {
  const size_t resIdx = stringToSearchIn.find(toFind, pos);

  if (resIdx == std::string::npos) {
    return std::nullopt;
  }

  return resIdx;
}

}  // namespace ps::string_manip