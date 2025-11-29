#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace ps {

struct WebPage {
  const std::string_view link;
  const std::string_view html;
};

class AllPageLinksGeneratorIf {
 public:
  virtual ~AllPageLinksGeneratorIf() = default;

  /**
   * @brief Returns links to all pages given the first page
   *
   * @param webPage
   * @return std::vector<std::string>
   */
  virtual std::vector<std::string> getLinksToAllPages(
      const WebPage& webPage) const = 0;
};

}  // namespace ps