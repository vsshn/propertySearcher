#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "links/RightmoveLinksProvider.h"
#include "parsers/HtmlParser.h"
#include "parsers/JsonParser.h"
#include "tests/CurlWrapperFactoryMock.h"
#include "tests/CurlWrapperMock.h"

namespace ps {

namespace {

static constexpr std::string_view kBaseUrl = "someUrl.com";

using testing::ByMove;
using testing::Eq;
using testing::Return;
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

TEST(RightmoveLinksProviderTest, Test) {
  auto htmlString = getStringFromFile("test_html/sample.html");

  auto mockCurlWrapper = std::make_unique<MockCurlWrapper>();
  EXPECT_CALL(*mockCurlWrapper, getHtmlFrom(kBaseUrl))
      .WillOnce(Return(htmlString));
  auto mockCurlWrapperFactory = std::make_unique<MockCurlWrapperFactory>();
  EXPECT_CALL(*mockCurlWrapperFactory, create)
      .WillRepeatedly(Return(ByMove(std::move(mockCurlWrapper))));
  RightmoveLinksProvider linksProvider(std::move(mockCurlWrapperFactory),
                                       getJsonFromScriptWithId, convertToJson);

  EXPECT_THAT(
      linksProvider.getLinks(kBaseUrl),
      UnorderedElementsAre(
          Link{.url = "https://www.rightmove.co.uk/properties/166517084#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/163505099#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/163808558#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/166578587#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/155893667#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/146655704#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/156807266#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/164747078#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/161394158#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/162376004#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/162265940#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/165794174#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/159387497#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/163473164#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/148711775#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/166630649#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/165628097#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/165639260#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/166432664#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/165412973#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/166866371#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/164458901#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/152985542#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/166604489#/"
                      "?channel=RES_LET"},
          Link{.url = "https://www.rightmove.co.uk/properties/165591833#/"
                      "?channel=RES_LET"}));
}

}  // namespace

}  // namespace ps