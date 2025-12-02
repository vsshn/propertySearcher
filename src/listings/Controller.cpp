#include "Controller.h"

#include <spdlog/spdlog.h>

#include <ranges>

namespace ps {

namespace {

void appendToVector(std::vector<Link>& vec, std::vector<Link>&& toAppend) {
  vec.reserve(vec.size() + toAppend.size());
  vec.insert(vec.end(), std::make_move_iterator(toAppend.begin()),
             std::make_move_iterator(toAppend.end()));
}

}  // namespace

Controller::Controller(
    std::unique_ptr<ListingsProviderIf> listingsProvider,
    std::unique_ptr<ListingFilterIf> listingFilter,
    std::unique_ptr<AllPageLinksGeneratorIf> allPageLinksGenerator,
    std::unique_ptr<CurlWrapperIf> curlWrapper)
    : listingsProvider_(std::move(listingsProvider)),
      listingFilter_(std::move(listingFilter)),
      allPageLinksGenerator_(std::move(allPageLinksGenerator)),
      curlWrapper_(std::move(curlWrapper)) {}

std::vector<Link> Controller::getAllInterestingLinks(
    const std::string_view baseUrl) const {
  std::optional<std::string> html = curlWrapper_->getHtmlFrom(baseUrl);
  if (!html) {
    spdlog::error("Couldn't get html from: {}", baseUrl);
    return {};
  }

  WebPage firstPage{.link = baseUrl, .html = html.value()};
  const std::vector<std::string> allPageLinks =
      allPageLinksGenerator_->getLinksToAllPages(firstPage);

  std::vector<Link> result;
  appendToVector(result, getAllInterestingLinksFromPage(firstPage.html));

  for (const auto& pageLink : allPageLinks | std::views::drop(1)) {
    std::optional<std::string> currentHtml = curlWrapper_->getHtmlFrom(baseUrl);
    if (!currentHtml) {
      spdlog::error("Couldn't get html from: {}", pageLink);
      continue;
    }
    appendToVector(result, getAllInterestingLinksFromPage(currentHtml.value()));
  }

  return result;
}

std::vector<Link> Controller::getAllInterestingLinksFromPage(
    const std::string_view pageHtml) const {
  // TODO
  return {};
}

}  // namespace ps