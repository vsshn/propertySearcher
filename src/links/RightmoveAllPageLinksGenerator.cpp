#include "RightmoveAllPageLinksGenerator.h"

#include <spdlog/spdlog.h>

namespace ps {

namespace {

constexpr std::string_view kSpanBeforeNumPages = "span>of <!-- -->";

int16_t getNumPages(const std::string_view html) { return 0; }

}  // namespace

RightmoveAllPageLinksGenerator::RightmoveAllPageLinksGenerator(
    std::unique_ptr<CurlWrapperIf> curlWrapper)
    : curlWrapper_(std::move(curlWrapper)) {}

std::vector<std::string> RightmoveAllPageLinksGenerator::getLinksToAllPages(
    const std::string_view firstPageLink) const {
  std::optional<std::string> html = curlWrapper_->getHtmlFrom(firstPageLink);
  if (!html) {
    spdlog::error("Couldn't get html from: {}", firstPageLink);
    return {};
  }

  const int16_t numPages = getNumPages(html.value());

  return {std::vector<std::string>(numPages, std::string(firstPageLink))};
}

}  // namespace ps
