#include "HtmlParser.h"

#include <spdlog/spdlog.h>

#include <format>

namespace ps {

namespace {
static constexpr std::string_view scriptClosingTag = "</script>";

std::optional<size_t> helperFind(const std::string_view stringToSearchIn,
                                 const std::string_view toFind,
                                 size_t pos = 0) {
  const size_t resIdx = stringToSearchIn.find(toFind, pos);

  if (resIdx == std::string::npos) {
    return std::nullopt;
  }

  return resIdx;
}

}  // namespace

std::optional<std::string> getJsonFromScriptWithId(
    const std::string_view scriptId, const std::string_view htmlBody) {
  const std::optional<const size_t> startIdx =
      helperFind(htmlBody, std::format("script id=\"{}\"", scriptId));

  if (!startIdx) {
    spdlog::error("Couldn't find script id: ", scriptId);
    return std::nullopt;
  }

  const std::optional<const size_t> beforeJsonStart =
      helperFind(htmlBody, ">", startIdx.value());
  if (!beforeJsonStart) {
    spdlog::error(
        "Html is likely malformed, couldn't find closing bracket for scriptId: "
        "{}",
        scriptId);
    return std::nullopt;
  }

  const size_t jsonStart = beforeJsonStart.value() + 1;

  const std::optional<const size_t> jsonEnd =
      helperFind(htmlBody, scriptClosingTag, jsonStart);

  if (!jsonEnd or jsonEnd < jsonStart) {
    spdlog::error(
        "Html is likely malformed, couldn't find closing tag for scriptId: "
        "{}",
        scriptId);
    return std::nullopt;
  }

  return std::make_optional(
      std::string(htmlBody.substr(jsonStart, jsonEnd.value() - jsonStart)));
}

}  // namespace ps