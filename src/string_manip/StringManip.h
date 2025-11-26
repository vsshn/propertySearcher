#pragma once

#include <optional>
#include <string_view>

namespace ps::string_manip {

/**
 * @brief Returns the index of the first occurrence of substring in the string
 * or nullopt if the substring doesn't occur
 *
 * @param stringToSearchIn  string to search in
 * @param toFind  string to find
 * @param pos starting position
 * @return std::optional<size_t> index of first occurrence
 */
std::optional<size_t> findStartOfSubstringInString(
    const std::string_view stringToSearchIn, const std::string_view toFind,
    size_t pos = 0);

}  // namespace ps::string_manip