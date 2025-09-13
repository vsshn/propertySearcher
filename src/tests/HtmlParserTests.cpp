#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "parsers/HtmlParser.h"

namespace ps {
namespace {

using testing::Eq;
using testing::IsTrue;
using testing::StrEq;

TEST(HtmlParserTests, TestGetJsonFromScriptWithId) {
  const std::string html = R"(
        <html><body>
            <script id="target" type="application/json">{"key":"value"}</script>
        </body></html>
    )";

  const std::string expectedString = R"({"key":"value"})";
  std::optional<std::string> res = getJsonFromScriptWithId("target", html);
  ASSERT_THAT(res.has_value(), IsTrue());
  EXPECT_THAT(res.value(), StrEq(expectedString));
}

TEST(HtmlParserTests, TestGetJsonFromScriptWithIdMalformedHtml) {
  const std::string html = R"(
        <html><body>
            <script id="target" type="application/json"{"key":"value"}
    )";

  const std::string expectedString = R"({"key":"value"})";
  std::optional<std::string> res = getJsonFromScriptWithId("target", html);
  EXPECT_THAT(res, Eq(std::nullopt));
}

TEST(HtmlParserTests,
     TestGetJsonFromScriptWithIdMalformedHtmlNoClosingBracket) {
  const std::string html = R"(
        <html><body>
            <script id="target" type="application/json"{"key":"value"}</script>
        </body></html>
    )";

  const std::string expectedString = R"({"key":"value"})";
  std::optional<std::string> res = getJsonFromScriptWithId("target", html);
  EXPECT_THAT(res, Eq(std::nullopt));
}

}  // namespace

}  // namespace ps