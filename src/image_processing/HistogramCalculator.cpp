#include "image_processing/HistogramCalculator.h"

namespace ps {

std::vector<float> computeHSVHistogram(const cv::Mat& img, HistParams params) {
  cv::Mat hsv;
  cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);

  const int histSize[] = {params.hBins, params.sBins, params.vBins};

  const float* ranges[] = {params.hRange, params.sRange, params.vRange};

  constexpr const int channels[] = {0, 1, 2};

  cv::Mat hist;
  cv::calcHist(&hsv, 1, channels, cv::Mat(), hist, 3, histSize, ranges);

  cv::normalize(hist, hist, 1.0, 0.0, cv::NORM_L1);

  hist = hist.reshape(1, 1);
  return std::vector<float>(hist.begin<float>(), hist.end<float>());
}

}  // namespace ps