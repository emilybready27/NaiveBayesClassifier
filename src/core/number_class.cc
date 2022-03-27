#include "core/number_class.h"

namespace naivebayes {

NumberClass::NumberClass(int class_number) {
  class_number_ = class_number;
  class_number_count_ = 0;
}

void NumberClass::AddImage(const Image& image) {
  images_.push_back(image);
  class_number_count_++;
  
  if (shaded_counts_.empty()) {
    ConstructShadedCounts(image.GetNumberRows(),
                          image.GetNumberColumns());
  }
  UpdateShadedCounts(image);
}

void NumberClass::ConstructShadedCounts(int number_rows, int number_columns) {
  for (int i = 0; i < number_rows; i++) {
    std::vector<int> shaded_counts_row(number_columns, 0);
    shaded_counts_.emplace_back(shaded_counts_row);
  }
}

void NumberClass::UpdateShadedCounts(const Image& image) {
  for (int i = 0; i < image.GetNumberRows(); i++) {
    for (int j = 0; j < image.GetNumberColumns(); j++) {
      int color = image.GetPixelColor(i, j);
      shaded_counts_[i][j] += color;
    }
  }
}

void NumberClass::ComputeFeatureProbsShaded(float kLaplace) {
  if (shaded_counts_.empty()) {
    feature_probs_shaded_ = std::vector<std::vector<float>>(0);
    return;
  }
  
  for (const std::vector<int>& shaded_counts_row : shaded_counts_) {
    std::vector<float> feature_probs_shaded_row;
      
    for (int shaded_count : shaded_counts_row) {
      float prob_shaded = (shaded_count + kLaplace)
                          / (class_number_count_ + (2 * kLaplace));
        
      feature_probs_shaded_row.push_back(prob_shaded);
    }
      
    feature_probs_shaded_.push_back(feature_probs_shaded_row);
  }
}

std::vector<Image> NumberClass::GetImages() const {
  return images_;
}

int NumberClass::GetCount() const {
  return class_number_count_;
}

int NumberClass::GetClassNumber() const {
  return class_number_;
}

std::vector<std::vector<int>> NumberClass::GetShadedCounts() const {
  return shaded_counts_;
}

std::vector<std::vector<float>> NumberClass::GetFeatureProbsShaded() const {
  return feature_probs_shaded_;
}

} // namespace naivebayes