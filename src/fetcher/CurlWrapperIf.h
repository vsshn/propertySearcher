#pragma once

#include <string_view>
#include <string>
#include <optional>

namespace ps
{
    class CurlWrapperIf
    {
    public:
        virtual ~CurlWrapperIf() = default;

        virtual std::optional<std::string> getHtmlFrom(const std::string_view url) = 0;
    };
}