#include "core/number_class.h"

namespace naivebayes {

NumberClass::NumberClass(int class_number) {
  class_number_ = class_number;
  class_number_count_ = 0;
  row_count_ = 0;
  column_count_ = 0;
  ResetFeatureProbsShaded(0);
}

void NumberClass::AddImage(const Image& image) {
  // TODO: instead of saving the image to the class, save the image shade
  // for each pixel as a count of frequencies in a SINGLE matrix...
  images_.push_back(image);
  class_number_count_++;
  
  if (row_count_ == 0 && column_count_ == 0) {
    row_count_ = image.GetRowCount();
    column_count_ = image.GetColumnCount();
  }
}

void NumberClass::ComputeFeatureProbsShaded(float k_laplace) {
  // initialize each element with additive k_laplace constant in numerators
  ResetFeatureProbsShaded(k_laplace);
  
  // in this class, find total number of images where pixel i,j is shaded
  // and store this in feature_probs_shaded_ to complete the numerators
  for (const Image& image : images_) {
    for (int i = 0; i < row_count_; i++) {
      for (int j = 0; j < column_count_; j++) {
        // color has 0 = unshaded and 1 = shaded
        int color = image.GetPixelColor(i, j);
        feature_probs_shaded_[i][j] += static_cast<float>(color);
      }
    }
  }
  
  // divide each element of feature_probs_shaded_ by denominator
  float denominator = static_cast<float>(class_number_count_) + (2 * k_laplace);
  for (int i = 0; i < row_count_; i++) {
    for (int j = 0; j < column_count_; j++) {
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

std::vector<std::vector<float>> NumberClass::GetFeatureProbsShaded() const {
  return feature_probs_shaded_;
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

void NumberClass::SetRowCount(int count) {
  row_count_ = count;
}

int NumberClass::GetRowCount() const {
  return row_count_;
}

void NumberClass::SetColumnCount(int count) {
  column_count_ = count;
}

int NumberClass::GetColumnCount() const {
  return column_count_;
}

} // namespace naivebayes