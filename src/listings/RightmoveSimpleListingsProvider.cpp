#include "RightmoveSimpleListingsProvider.h"

#include <spdlog/spdlog.h>

#include <iostream>
#include <ranges>

#include "parsers/JsonParser.h"

namespace ps {

namespace {

std::vector<std::string> extractImageUrls(const auto& property) {
  const auto& images = property["images"];
  std::vector<std::string> result;
  result.reserve(images.size());
  for (const auto& imageUrlEl : images) {
    result.emplace_back(imageUrlEl["srcUrl"]);
  }

  return result;
}

uint8_t extractNumBedrooms(const auto& property) {
  return static_cast<uint8_t>(property["bedrooms"]);
}

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
    JsonScriptGetter jsonGetter, StringToJsonConverter toJsonConverter)
    : getJsonScriptFromHtml_(std::move(jsonGetter)),
      convertStringToJson_(std::move(toJsonConverter)) {}

std::vector<Listing> RightmoveSimpleListingsProvider::getListings(
    const std::string_view html) const {
  std::optional<std::string> propertiesJsonString =
      getJsonScriptFromHtml_(kScriptId, html);

  if (!propertiesJsonString) {
    spdlog::error(
        "Couldn't get json containing properties info from html provided");
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
        return Listing{.price = extractPrice(property["price"]),
                       .imageUrls = extractImageUrls(property),
                       .numBedrooms = extractNumBedrooms(property)};
      });

  std::vector<Listing> listings(propertiesView.begin(), propertiesView.end());

  return listings;
}

}  // namespace ps