#include "CurlWrapper.h"

#include <string>
#include <spdlog/spdlog.h>

namespace ps
{

    namespace
    {
        static size_t writer(char *data, size_t size, size_t nmemb,
                             std::string *writerData)
        {
            if (writerData == nullptr)
                return 0;

            auto sz = size * nmemb;

            writerData->append(data, sz);

            return sz;
        }
    }

    CurlWrapper::CurlWrapper() : curl_(curl_easy_init())
    {
        if (!curl_)
        {
            throw std::runtime_error("Couldn't init curl");
        }
    }

    CurlWrapper::~CurlWrapper()
    {
        if (curl_)
        {
            curl_easy_cleanup(curl_);
        }
    }

    std::optional<std::string>
    CurlWrapper::getHtmlFrom(const std::string_view url)
    {
        std::string response;

        if (auto res = curl_easy_setopt(curl_, CURLOPT_URL, url); res != CURLE_OK)
        {
            spdlog::error("Failed to set url: {} with: {}", url, curl_easy_strerror(res));
            return std::nullopt;
        }
        if (auto res = curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, writer); res != CURLE_OK)
        {
            spdlog::error("Failed to set writer with: {}", curl_easy_strerror(res));
            return std::nullopt;
        }
        if (auto res = curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response); res != CURLE_OK)
        {
            spdlog::error("Failed to set response data with {}", curl_easy_strerror(res));
            return std::nullopt;
        }
        if (auto res = curl_easy_setopt(curl_, CURLOPT_USERAGENT, "Mozilla/5.0"); res != CURLE_OK)
        {
            spdlog::error("Failed to set user agent with {}", curl_easy_strerror(res));
            return std::nullopt;
        }

        if (CURLcode res = curl_easy_perform(curl_); res != CURLE_OK)
        {
            spdlog::error("Encountered an error: {} when fetching url {}", curl_easy_strerror(res), url);
            return std::nullopt;
        }

        return std::make_optional(response);
    }
}