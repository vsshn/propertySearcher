#include "JsonParser.h"

namespace ps {

nlohmann::json convertToJson(const std::string& jsonStr) {
  return nlohmann::json::parse(jsonStr);
}

}  // namespace ps