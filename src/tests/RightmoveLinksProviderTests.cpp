#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "links/RightmoveLinksProvider.h"
#include "tests/CurlWrapperFactoryMock.h"
#include "tests/CurlWrapperMock.h"

namespace ps {
namespace {

using testing::ByMove;
using testing::Eq;
using testing::Return;

TEST(TestTest, Test) {
  auto mockCurlWrapper = std::make_unique<MockCurlWrapper>();
  auto mockCurlWrapperFactory = std::make_unique<MockCurlWrapperFactory>();
  EXPECT_CALL(*mockCurlWrapperFactory, create)
      .WillRepeatedly(Return(ByMove(std::move(mockCurlWrapper))));
  RightmoveLinksProvider linksProvider(std::move(mockCurlWrapperFactory));

  linksProvider.getLinks("");
}

}  // namespace

}  // namespace ps