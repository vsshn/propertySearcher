#pragma once

#include <curl/curl.h>

#include "CurlWrapperIf.h"

namespace ps {

class CurlWrapper : public CurlWrapperIf {
 public:
  CurlWrapper();
  ~CurlWrapper() override;

  virtual std::optional<std::string> getHtmlFrom(
      const std::string_view url) override;

 private:
  CURL *curl_ = nullptr;
};
}  // namespace ps