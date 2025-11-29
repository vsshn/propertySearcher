#include "RightmoveAllPageLinksGenerator.h"

#include <spdlog/spdlog.h>

#include <ranges>

#include "string_manip/StringManip.h"

namespace ps {

namespace {

constexpr std::string_view kSpanBeforeNumPages = "span>of <!-- -->";

int16_t getNumPages(const std::string_view html) {
  const std::optional<size_t> spanStartIdx =
      string_manip::findStartOfSubstringInString(html, kSpanBeforeNumPages);
  if (!spanStartIdx) {
    spdlog::error("Couldn't find span indicating number of pages");
    return 1;
  }

  const size_t numPagesStartIdx =
      spanStartIdx.value() + kSpanBeforeNumPages.size();

  const std::optional<size_t> numPagesEndIdx =
      string_manip::findStartOfSubstringInString(html, "</", numPagesStartIdx);

  if (!numPagesEndIdx) {
    spdlog::error("Couldn't find the end of the number of pages span");
    return 1;
  }

  const std::string numPagesStr = std::string(
      html.substr(numPagesStartIdx, numPagesEndIdx.value() - numPagesStartIdx));

  try {
    return std::stoi(numPagesStr);
  } catch (const std::exception& e) {
    spdlog::error("Couldn't convert number of pages string to int: {}",
                  e.what());
    return 1;
  }
}

}  // namespace

std::vector<std::string> RightmoveAllPageLinksGenerator::getLinksToAllPages(
    const WebPage& page) const {
  const int16_t numPages = getNumPages(page.html);

  auto resView = std::views::iota(0, numPages) |
                 std::ranges::views::transform([&page](int16_t pageIndex) {
                   return std::format("{}&index={}", page.link, pageIndex * 24);
                 });

  std::vector<std::string> result;
  result.reserve(numPages);

  for (auto&& s : resView) {
    result.emplace_back(std::move(s));
  }
  return result;
}

}  // namespace ps
