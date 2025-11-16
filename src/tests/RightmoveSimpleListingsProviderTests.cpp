#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "listings/RightmoveSimpleListingsProvider.h"
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

TEST(RightmoveSimpleListingsProviderTests, Test) {
  auto htmlString = getStringFromFile("test_html/sample.html");

  auto mockCurlWrapper = std::make_unique<MockCurlWrapper>();
  EXPECT_CALL(*mockCurlWrapper, getHtmlFrom(kBaseUrl))
      .WillOnce(Return(htmlString));
  auto mockCurlWrapperFactory = std::make_unique<MockCurlWrapperFactory>();
  EXPECT_CALL(*mockCurlWrapperFactory, create)
      .WillRepeatedly(Return(ByMove(std::move(mockCurlWrapper))));
  RightmoveSimpleListingsProvider listingsProvider(
      std::move(mockCurlWrapperFactory), getJsonFromScriptWithId,
      convertToJson);

  EXPECT_THAT(
      listingsProvider.getListings(kBaseUrl),
      UnorderedElementsAre(Listing{.price = 3095}, Listing{.price = 13649},
                           Listing{.price = 13649}, Listing{.price = 13000},
                           Listing{.price = 13000}, Listing{.price = 13000},
                           Listing{.price = 13000}, Listing{.price = 12783},
                           Listing{.price = 12783}, Listing{.price = 12783},
                           Listing{.price = 12500}, Listing{.price = 12500},
                           Listing{.price = 12500}, Listing{.price = 12499},
                           Listing{.price = 12350}, Listing{.price = 12350},
                           Listing{.price = 12350}, Listing{.price = 12350},
                           Listing{.price = 11917}, Listing{.price = 11700},
                           Listing{.price = 11700}, Listing{.price = 11700},
                           Listing{.price = 11483}, Listing{.price = 11266},
                           Listing{.price = 11158}));
}

}  // namespace

}  // namespace ps