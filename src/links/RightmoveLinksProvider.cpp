#include "RightmoveLinksProvider.h"

#include <spdlog/spdlog.h>

#include <iostream>
#include <ranges>

namespace ps {

namespace {

static constexpr std::string_view kScriptId = "__NEXT_DATA__";
static constexpr std::string_view kRightmoveUrl = "https://www.rightmove.co.uk";

template <typename JsonGetter>
std::optional<nlohmann::json> getJson(const std::string& jsonString,
                                      const JsonGetter& getJson) noexcept {
  try {
    return getJson(jsonString);
  } catch (nlohmann::json::parse_error exc) {
    spdlog::error("Couldn't parse json string: {}", jsonString);
  }

  return std::nullopt;
}

}  // namespace

RightmoveLinksProvider::RightmoveLinksProvider(
    std::unique_ptr<CurlWrapperFactoryIf> curlWrapperFactory,
    JsonScriptGetter jsonGetter, StringToJsonConverter toJsonConverter)
    : curlWrapperFactory_(std::move(curlWrapperFactory)),
      curlWrapper_(curlWrapperFactory_->create()),
      getJsonScriptFromHtml_(std::move(jsonGetter)),
      convertStringToJson_(std::move(toJsonConverter)) {}

std::vector<Link> RightmoveLinksProvider::getLinks(
    const std::string_view baseUrl) const {
  std::optional<std::string> html = curlWrapper_->getHtmlFrom(baseUrl);
  if (!html) {
    spdlog::error("Couldn't get html from: {}", baseUrl);
    return {};
  }

  std::optional<std::string> propertiesJsonString =
      getJsonScriptFromHtml_(kScriptId, html.value());

  if (!propertiesJsonString) {
    spdlog::error("Couldn't get json containing properties info from: {}",
                  baseUrl);
    return {};
  }

  std::optional<nlohmann::json> propertiesJson =
      getJson(propertiesJsonString.value(), convertStringToJson_);

  if (!propertiesJson) {
    return {};
  }

  const auto& properties =
      propertiesJson
          .value()["props"]["pageProps"]["searchResults"]["properties"];

  auto propertiesView =
      properties | std::ranges::views::transform([](const auto& property) {
        return Link{.url = std::format("{}{}", kRightmoveUrl,
                                       std::string(property["propertyUrl"]))};
      });

  std::vector<Link> links(propertiesView.begin(), propertiesView.end());

  return links;
}

}  // namespace ps