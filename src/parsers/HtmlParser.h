#pragma once

#include <optional>
#include <string>

namespace ps {

std::optional<std::string> getJsonFromScriptWithId(
    const std::string_view scriptId, const std::string_view htmlBody);

}  // namespace ps