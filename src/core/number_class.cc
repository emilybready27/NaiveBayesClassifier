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

} // namespace naivebayes