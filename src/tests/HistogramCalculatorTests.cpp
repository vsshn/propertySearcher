#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <opencv2/opencv.hpp>

#include "image_processing/HistogramCalculator.h"

namespace ps {
namespace {

constexpr std::string_view fileFolder = "test_images";
constexpr std::string_view fileName1 = "download.jpeg";

using testing::ContainerEq;
using testing::SizeIs;

TEST(TestHistogramCalculator, TestDetermenistic) {
  cv::Mat img =
      cv::imread(std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, fileName1));

  auto hist1 = computeHSVHistogram(img);
  auto hist2 = computeHSVHistogram(img);
  EXPECT_THAT(hist1, ContainerEq(hist2));
}

TEST(TestHistogramCalculator, TestSize) {
  cv::Mat img =
      cv::imread(std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, fileName1));

  auto hist = computeHSVHistogram(
      img, HistParams{.hBins = 16, .sBins = 16, .vBins = 8});
  EXPECT_THAT(hist, SizeIs(16 * 16 * 8));
}

}  // namespace

}  // namespace ps