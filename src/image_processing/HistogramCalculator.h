#include <opencv2/opencv.hpp>
#include <vector>

namespace ps {

struct HistParams {
  const int hBins = 16;
  const int sBins = 16;
  const int vBins = 8;

  const float hRange[2] = {0, 180};
  const float sRange[2] = {0, 256};
  const float vRange[2] = {0, 256};
};

std::vector<float> computeHSVHistogram(const cv::Mat& img,
                                       HistParams params = HistParams{});

}  // namespace ps