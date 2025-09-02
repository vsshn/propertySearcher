#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "links/RightmoveLinksProvider.h"
#include "tests/CurlWrapperMock.h"

namespace ps {
namespace {

using testing::Eq;

TEST(TestTest, Test) {
  auto mockCurlWrapper = std::make_unique<MockCurlWrapper>();
  EXPECT_CALL(*mockCurlWrapper, getHtmlFrom).Times(1);
  RightmoveLinksProvider linksProvider(std::move(mockCurlWrapper), {""});

  linksProvider.getLinks();
}

}  // namespace

}  // namespace ps