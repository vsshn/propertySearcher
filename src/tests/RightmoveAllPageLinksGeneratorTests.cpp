#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "links/RightmoveAllPageLinksGenerator.h"

namespace ps {

namespace {

using testing::ElementsAre;
using testing::Eq;
using testing::Return;
using testing::StrEq;
using testing::UnorderedElementsAre;

std::string getStringFromFile(const std::string_view fileName) {
  std::ifstream file(std::format("{}/{}", TEST_DATA_DIR, fileName));
  if (!file.is_open()) {
    throw std::runtime_error(
        std::format("Couldn't open the file: {}", fileName));
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  std::string content = buffer.str();

  return content;
}

TEST(RightmoveAllPageLinksGeneratorTests, Test) {
  auto htmlString = getStringFromFile("test_html/sample.html");

  RightmoveAllPageLinksGenerator linksGenerator;
  EXPECT_THAT(
      linksGenerator.getLinksToAllPages(
          WebPage{.html = htmlString, .link = "someUrl.com"}),
      ElementsAre(StrEq("someUrl.com&index=0"), StrEq("someUrl.com&index=24"),
                  StrEq("someUrl.com&index=48")));
}

}  // namespace

}  // namespace ps