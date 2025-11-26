#include "HtmlParser.h"

#include <spdlog/spdlog.h>

#include <format>

#include "string_manip/StringManip.h"

namespace ps {

namespace {
static constexpr std::string_view scriptClosingTag = "</script>";

}  // namespace

std::optional<std::string> getJsonFromScriptWithId(
    const std::string_view scriptId, const std::string_view htmlBody) {
  const std::optional<const size_t> startIdx =
      string_manip::findStartOfSubstringInString(
          htmlBody, std::format("script id=\"{}\"", scriptId));

  if (!startIdx) {
    spdlog::error("Couldn't find script id: ", scriptId);
    return std::nullopt;
  }

  const std::optional<const size_t> beforeJsonStart =
      string_manip::findStartOfSubstringInString(htmlBody, ">",
                                                 startIdx.value());
  if (!beforeJsonStart) {
    spdlog::error(
        "Html is likely malformed, couldn't find closing bracket for scriptId: "
        "{}",
        scriptId);
    return std::nullopt;
  }

  const size_t jsonStart = beforeJsonStart.value() + 1;

  const std::optional<const size_t> jsonEnd =
      string_manip::findStartOfSubstringInString(htmlBody, scriptClosingTag,
                                                 jsonStart);

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