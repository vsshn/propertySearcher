#include <opencv2/opencv.hpp>
#include <optional>
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

std::vector<float> computeHSVHistogram(const std::string& path,
                                       HistParams params = HistParams{});

template <typename ElementType>
std::optional<ElementType> cosine(const std::vector<ElementType>& lhs,
                                  const std::vector<ElementType>& rhs) {
  double dotProduct = 0.0;
  double modLhs = 0.0;
  double modRhs = 0.0;
  int ln = lhs.size();
  int rn = rhs.size();
  if (ln != rn) {
    return std::nullopt;
  }

  for (int i = 0; i < ln; i++) {
    const ElementType lhsEl = lhs[i];
    const ElementType rhsEl = rhs[i];
    modLhs += lhsEl * lhsEl;
    modRhs += rhsEl * rhsEl;
    dotProduct += lhsEl * rhsEl;
  }

  return dotProduct / sqrt(modLhs * modRhs);
}

}  // namespace ps