#include "HtmlParser.h"

#include <spdlog/spdlog.h>

#include <format>

namespace ps {

namespace {
static constexpr std::string_view scriptClosingTag = "</script>";
}

std::optional<std::string> getJsonFromScriptWithId(
    const std::string_view scriptId, const std::string_view htmlBody) {
  const std::string toFind = std::format("script id=\"{}\"", scriptId);
  const size_t startIdx = htmlBody.find(toFind);
  if (startIdx == std::string::npos) {
    spdlog::error("Couldn't find a script with the id: {}", scriptId);
    return std::nullopt;
  }

  const size_t beforeJsonStart = htmlBody.find(">", startIdx);
  if (beforeJsonStart == std::string::npos) {
    spdlog::error(
        "Html is likely malformed, couldn't find closing bracket for scriptId: "
        "{}",
        scriptId);
    return std::nullopt;
  }

  size_t jsonStart = beforeJsonStart + 1;

  size_t jsonEnd = htmlBody.find(scriptClosingTag, jsonStart);
  if (jsonEnd < jsonStart or jsonEnd == std::string::npos) {
    spdlog::error(
        "Html is likely malformed, couldn't find closing tag for scriptId: "
        "{}",
        scriptId);
    return std::nullopt;
  }

  return std::make_optional(
      std::string(htmlBody.substr(jsonStart, jsonEnd - jsonStart)));
}

}  // namespace ps