#include "core/number_class.h"

namespace naivebayes {

NumberClass::NumberClass(int class_number, int row_count, int column_count) {
  class_number_ = class_number;
  row_count_ = row_count;
  column_count_ = column_count;
  class_number_count_ = 0;
  ResetFeatureProbsShaded(0);
}

void NumberClass::AddImage(const Image& image) {
  // feature_probs_shaded_ initially stores the frequencies of shaded pixels
  for (int i = 0; i < image.GetRowCount(); i++) {
    for (int j = 0; j < image.GetColumnCount(); j++) {
      // color has 0 = unshaded and 1 = shaded
      int color = image.GetPixelColor(i, j);
      feature_probs_shaded_[i][j] += static_cast<float>(color);
    }
  }
  
  class_number_count_++;
}

void NumberClass::ComputeFeatureProbsShaded(float k_laplace) {
  if (class_number_count_ <= 0) {
    return;
  }
  
  // divide each element of feature_probs_shaded_ by denominator
  float denominator = static_cast<float>(class_number_count_) + (2 * k_laplace);
  for (int i = 0; i < row_count_; i++) {
    for (int j = 0; j < column_count_; j++) {
      feature_probs_shaded_[i][j] += k_laplace;
      feature_probs_shaded_[i][j] /= denominator;
    }
  }
}

void NumberClass::ResetFeatureProbsShaded(float reset_value) {
  std::vector<std::vector<float>> new_matrix;
  for (int i = 0; i < row_count_; i++) {
    std::vector<float> row(column_count_, reset_value);
    new_matrix.emplace_back(row);
  }
  feature_probs_shaded_ = new_matrix;
}

void NumberClass::SetFeatureProbsShaded(
    const std::vector<std::vector<float>>& matrix) {
  
  ResetFeatureProbsShaded(0);
  for (int i = 0; i < row_count_; i++) {
    const std::vector<float>& row = matrix[i];
    feature_probs_shaded_[i] = row;
  }
}

float NumberClass::GetFeatureProbsShaded(int row, int column) const {
  return feature_probs_shaded_[row][column];
}

int NumberClass::GetClassNumber() const {
  return class_number_;
}

void NumberClass::SetClassNumberCount(int count) {
  class_number_count_ = count;
}

int NumberClass::GetClassNumberCount() const {
  return class_number_count_;
}

} // namespace naivebayes