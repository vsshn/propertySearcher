#pragma once

#include <functional>
#include <nlohmann/json.hpp>
#include <optional>

#include "ListingsProviderIf.h"
#include "fetcher/CurlWrapperFactoryIf.h"
#include "fetcher/CurlWrapperIf.h"

namespace ps {

/**
 * @brief Class that provides listings from rightmove
 * by parsing the base page, without going into individual property pages.
 *
 */
class RightmoveSimpleListingsProvider : public ListingsProviderIf {
 public:
  using JsonScriptGetter = std::function<std::optional<std::string>(
      const std::string_view, const std::string_view)>;

  using StringToJsonConverter =
      std::function<nlohmann::json(const std::string& jsonStr)>;

  explicit RightmoveSimpleListingsProvider(
      std::unique_ptr<CurlWrapperFactoryIf> curlWrapperFactory,
      JsonScriptGetter jsonGetter, StringToJsonConverter toJsonConverter);

  virtual std::vector<Listing> getListings(
      const std::string_view baseUrl) const override;

 private:
  std::unique_ptr<CurlWrapperFactoryIf> curlWrapperFactory_;
  std::unique_ptr<CurlWrapperIf> curlWrapper_;

  JsonScriptGetter getJsonScriptFromHtml_;
  StringToJsonConverter convertStringToJson_;
};

}  // namespace ps