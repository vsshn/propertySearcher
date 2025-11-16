#include "RightmoveSimpleListingsProvider.h"

#include <spdlog/spdlog.h>

#include <iostream>
#include <ranges>

#include "parsers/JsonParser.h"

namespace ps {

namespace {

static constexpr std::string_view kScriptId = "__NEXT_DATA__";
static constexpr std::string_view kRightmoveUrl = "https://www.rightmove.co.uk";

uint16_t extractPrice(const auto& priceJson) {
  constexpr const double weekToMonthCoeff = 13. / 3.;
  const int16_t price = priceJson["amount"];
  const std::string frequency = priceJson["frequency"];
  if (frequency == "monthly") {
    return price;
  } else if (frequency == "weekly") {
    return static_cast<int16_t>(price * weekToMonthCoeff);
  }

  spdlog::error("Weird payment frequency: {}, cannot extract price", frequency);
  return 0;
}

}  // namespace

RightmoveSimpleListingsProvider::RightmoveSimpleListingsProvider(
    std::unique_ptr<CurlWrapperFactoryIf> curlWrapperFactory,
    JsonScriptGetter jsonGetter, StringToJsonConverter toJsonConverter)
    : curlWrapperFactory_(std::move(curlWrapperFactory)),
      curlWrapper_(curlWrapperFactory_->create()),
      getJsonScriptFromHtml_(std::move(jsonGetter)),
      convertStringToJson_(std::move(toJsonConverter)) {}

std::vector<Listing> RightmoveSimpleListingsProvider::getListings(
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
      getJsonOptional(propertiesJsonString.value(), convertStringToJson_);

  if (!propertiesJson) {
    return {};
  }

  const auto& properties =
      propertiesJson
          .value()["props"]["pageProps"]["searchResults"]["properties"];

  auto propertiesView =
      properties | std::ranges::views::transform([](const auto& property) {
        return Listing{.price = extractPrice(property["price"])};
      });

  std::vector<Listing> listings(propertiesView.begin(), propertiesView.end());

  return listings;
}

}  // namespace ps