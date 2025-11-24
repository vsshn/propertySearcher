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
      UnorderedElementsAre(
          Listing{
              .price = 3095,
              .numBedrooms = 2,
              .imageUrls =
                  {"https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/223k/"
                   "222842/"
                   "166517084/222842_TCH231746_L_IMG_00_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/223k/"
                   "222842/"
                   "166517084/222842_TCH231746_L_IMG_07_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/223k/"
                   "222842/"
                   "166517084/222842_TCH231746_L_IMG_04_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/223k/"
                   "222842/"
                   "166517084/222842_TCH231746_L_IMG_05_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/223k/"
                   "222842/"
                   "166517084/222842_TCH231746_L_IMG_03_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/223k/"
                   "222842/"
                   "166517084/222842_TCH231746_L_IMG_01_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/223k/"
                   "222842/"
                   "166517084/222842_TCH231746_L_IMG_02_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/223k/"
                   "222842/"
                   "166517084/222842_TCH231746_L_IMG_06_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/223k/"
                   "222842/"
                   "166517084/222842_TCH231746_L_IMG_08_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/223k/"
                   "222842/"
                   "166517084/"
                   "222842_TCH231746_L_IMG_09_0000_max_476x317.jpeg"}},
          Listing{
              .price = 13649,
              .numBedrooms = 5,
              .imageUrls =
                  {"https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/8k/"
                   "7411/"
                   "163505099/7411_HNV180224_L_IMG_00_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/8k/"
                   "7411/"
                   "163505099/7411_HNV180224_L_IMG_01_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/8k/"
                   "7411/"
                   "163505099/7411_HNV180224_L_IMG_02_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/8k/"
                   "7411/"
                   "163505099/7411_HNV180224_L_IMG_03_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/8k/"
                   "7411/"
                   "163505099/7411_HNV180224_L_IMG_04_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/8k/"
                   "7411/"
                   "163505099/7411_HNV180224_L_IMG_05_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/8k/"
                   "7411/"
                   "163505099/7411_HNV180224_L_IMG_06_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/8k/"
                   "7411/"
                   "163505099/7411_HNV180224_L_IMG_07_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/8k/"
                   "7411/"
                   "163505099/7411_HNV180224_L_IMG_08_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/8k/"
                   "7411/"
                   "163505099/7411_HNV180224_L_IMG_09_0000_max_476x317.jpeg"}},
          Listing{
              .price = 13649,
              .numBedrooms = 5,
              .imageUrls =
                  {"https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/85k/"
                   "84235/"
                   "163808558/84235_RGS180093_L_IMG_00_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/85k/"
                   "84235/"
                   "163808558/84235_RGS180093_L_IMG_01_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/85k/"
                   "84235/"
                   "163808558/84235_RGS180093_L_IMG_02_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/85k/"
                   "84235/"
                   "163808558/84235_RGS180093_L_IMG_03_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/85k/"
                   "84235/"
                   "163808558/84235_RGS180093_L_IMG_04_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/85k/"
                   "84235/"
                   "163808558/84235_RGS180093_L_IMG_05_0000_max_476x317.jpeg",
                   "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/85k/"
                   "84235/"
                   "163808558/84235_RGS180093_L_IMG_06_0000_max_476x317.jpeg"}},
          Listing{.price = 11158,
                  .numBedrooms = 5,
                  .imageUrls = {
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_22_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_02_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_21_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_01_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_03_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_04_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_05_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_06_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_07_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_08_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_09_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_11_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_12_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_13_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_14_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_16_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_17_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_20_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_00_0000_max_476x317.jpeg",
                      "https://media.rightmove.co.uk:443/dir/crop/10:9-16:9/"
                      "50k/49006/165591833/"
                      "49006_HAL090081_L_IMG_23_0000_max_476x317.jpeg"}}));
}

}  // namespace

}  // namespace ps