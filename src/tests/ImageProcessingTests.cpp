#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <opencv2/opencv.hpp>

#include "image_processing/ImageProcessing.h"

namespace ps {
namespace {

constexpr std::string_view fileFolder = "test_images";
constexpr std::string_view fileName1 = "simple.jpeg";

constexpr std::string_view seagul1 = "seagul1.jpeg";
constexpr std::string_view seagul2 = "seagul2.png";
constexpr std::string_view seagul3 = "seagul3.png";
constexpr std::string_view northernLights = "northernLights.jpg";
constexpr std::string_view room1 = "room1.jpeg";
constexpr std::string_view room2 = "room2.jpeg";
constexpr std::string_view room3Different = "room3_different.jpeg";
constexpr std::string_view differentRoom = "differentRoom.jpeg";

using testing::ContainerEq;
using testing::Ge;
using testing::Le;
using testing::SizeIs;

TEST(TestHistogramCalculator, TestDetermenistic) {
  const cv::Mat img =
      cv::imread(std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, fileName1));

  const std::vector<float> hist1 = computeHSVHistogram(img);
  const std::vector<float> hist2 = computeHSVHistogram(img);
  EXPECT_THAT(hist1, ContainerEq(hist2));
}

TEST(TestHistogramCalculator, TestSize) {
  const cv::Mat img =
      cv::imread(std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, fileName1));

  const std::vector<float> hist = computeHSVHistogram(
      img, HistParams{.hBins = 16, .sBins = 16, .vBins = 8});
  EXPECT_THAT(hist, SizeIs(16 * 16 * 8));
}

TEST(TestImageProcessing, TestSimilarImagesGetSimilarCosine) {
  const cv::Mat img1 =
      cv::imread(std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, seagul1));

  const cv::Mat img2 =
      cv::imread(std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, seagul2));

  const std::vector<float> hist1 = computeHSVHistogram(img1);
  const std::vector<float> hist2 = computeHSVHistogram(img2);

  EXPECT_THAT(cosine(hist1, hist2), Ge(0.98));
}

TEST(TestImageProcessing, TestNotSoSimilarImagesGetSmallerCosine) {
  const std::vector<float> hist1 = computeHSVHistogram(
      std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, seagul1));

  const std::vector<float> hist2 = computeHSVHistogram(
      std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, seagul3));

  EXPECT_THAT(cosine(hist1, hist2), Le(0.7));
  EXPECT_THAT(cosine(hist1, hist2), Ge(0.3));
}

TEST(TestImageProcessing, TestDifferentImagesGetSmalCosine) {
  const std::vector<float> hist1 = computeHSVHistogram(
      std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, seagul1));

  const std::vector<float> hist2 = computeHSVHistogram(
      std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, northernLights));

  EXPECT_THAT(cosine(hist1, hist2), Le(0.2));
}

TEST(TestImageProcessing,
     TestSameRoomFromSlightlyDifferentPOVsGetsBiggerCosine) {
  const std::vector<float> hist1 = computeHSVHistogram(
      std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, room1));

  const std::vector<float> hist2 = computeHSVHistogram(
      std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, room2));

  EXPECT_THAT(cosine(hist1, hist2), Ge(0.6));
}

TEST(TestImageProcessing, TestSameRoomDifferentPOVsGetsSmallerCosine) {
  const std::vector<float> hist1 = computeHSVHistogram(
      std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, room1));

  const std::vector<float> hist2 = computeHSVHistogram(
      std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, room3Different));

  EXPECT_THAT(cosine(hist1, hist2), Le(0.5));
}

TEST(TestImageProcessing, TestDifferentRoomsGetSmallCosine) {
  const std::vector<float> hist1 = computeHSVHistogram(
      std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, room1));

  const std::vector<float> hist2 = computeHSVHistogram(
      std::format("{}/{}/{}", TEST_DATA_DIR, fileFolder, differentRoom));

  EXPECT_THAT(cosine(hist1, hist2), Le(0.3));
}

}  // namespace

}  // namespace ps