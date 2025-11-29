#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "string_manip/StringManip.h"

namespace ps::string_manip {

namespace {

using testing::Eq;

TEST(TestStringManip, FindStartOfSubstringInString_FoundBeginningSingle) {
  const std::string_view stringToSearchIn = "test, this is a hello string.";
  const std::string_view toFind = "test";

  const std::optional<size_t> result =
      findStartOfSubstringInString(stringToSearchIn, toFind);

  ASSERT_TRUE(result.has_value());
  EXPECT_THAT(result.value(), Eq(0));
}

TEST(TestStringManip, FindStartOfSubstringInString_FoundBeginningMultiple) {
  const std::string_view stringToSearchIn = "test, this is a test string.";
  const std::string_view toFind = "test";

  const std::optional<size_t> result =
      findStartOfSubstringInString(stringToSearchIn, toFind);

  ASSERT_TRUE(result.has_value());
  EXPECT_THAT(result.value(), Eq(0));
}

TEST(TestStringManip, FindStartOfSubstringInString_FoundMiddleMultiple) {
  const std::string_view stringToSearchIn = "Test this is a test string. test";
  const std::string_view toFind = "test";

  const std::optional<size_t> result =
      findStartOfSubstringInString(stringToSearchIn, toFind);

  ASSERT_TRUE(result.has_value());
  EXPECT_THAT(result.value(), Eq(15));
}

TEST(TestStringManip, FindStartOfSubstringInString_NonFound) {
  const std::string_view stringToSearchIn = "test, this is a test string.";
  const std::string_view toFind = "test1";

  const std::optional<size_t> result =
      findStartOfSubstringInString(stringToSearchIn, toFind);

  ASSERT_THAT(result, Eq(std::nullopt));
}

}  // namespace
}  // namespace ps::string_manip