#include <spdlog/spdlog.h>

#include <nlohmann/json.hpp>

namespace ps {

nlohmann::json convertToJson(const std::string& jsonStr);

template <typename JsonGetter>
std::optional<nlohmann::json> getJsonOptional(
    const std::string& jsonString, const JsonGetter& getJson) noexcept {
  try {
    return getJson(jsonString);
  } catch (nlohmann::json::parse_error exc) {
    spdlog::error("Couldn't parse json string: {}", jsonString);
  }

  return std::nullopt;
}

}  // namespace ps