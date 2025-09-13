#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <nlohmann/json.hpp>

#include "parsers/JsonParser.h"

namespace ps {
namespace {

using testing::Contains;
using testing::Eq;
using testing::IsTrue;
using testing::StrEq;
using testing::UnorderedElementsAre;

TEST(JsonParserTests, TestConvertToJson) {
  const std::string jsonStr = R"({"key":"value"})";
  nlohmann::json result = convertToJson(jsonStr);
  EXPECT_THAT(result["key"], StrEq("value"));
}

TEST(JsonParserTests, TestConvertToJsonNested) {
  const std::string jsonStr = R"({
  "key":"value",
  "key2" : {"key3": 3}
  })";
  nlohmann::json result = convertToJson(jsonStr);

  EXPECT_THAT(result["key"], StrEq("value"));
  EXPECT_THAT(result["key2"]["key3"], Eq(3));
}

TEST(JsonParserTests, TestConvertToJsonMalformedInput) {
  const std::string jsonStr = R"({"key":"value",3})";
  EXPECT_THROW(convertToJson(jsonStr), nlohmann::json::parse_error);

  const std::string jsonStr2 = R"({"key":sdf"value"})";
  EXPECT_THROW(convertToJson(jsonStr), nlohmann::json::parse_error);
}

}  // namespace

}  // namespace ps