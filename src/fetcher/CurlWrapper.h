#pragma once

#include "CurlWrapperIf.h"

#include <curl/curl.h>

namespace ps
{

    class CurlWrapper : public CurlWrapperIf
    {
    public:
        CurlWrapper();
        ~CurlWrapper() override;

        virtual std::optional<std::string> getHtmlFrom(const std::string_view url) override;

    private:
        CURL *curl_ = nullptr;
    };
}