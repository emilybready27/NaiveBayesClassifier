#include "core/validator.h"
#include <numeric>

namespace naivebayes {

Validator::Validator(const std::vector<Image>& images,
                     int k_max_class_count) {
  images_ = images;
  image_count_ = images.size();
  accuracy_ = 0.0;
  accuracies_ = std::vector<float>(k_max_class_count, 0.0);
  class_number_counts_ = std::vector<int>(k_max_class_count, 0);
}

void Validator::Compare(int expected_class_number, int actual_class_number) {
  int delta = expected_class_number - actual_class_number;
  
  // increment number of predictions
  class_number_counts_[expected_class_number]++;
    
  // increment number of correct predictions
  if (delta == 0) {
    accuracies_[expected_class_number]++;
    accuracy_++;
  }
}

float Validator::Validate() {
  // scale each frequency to get an accuracy estimate
  for (size_t i = 0; i < accuracies_.size(); i++) {
    if (class_number_counts_[i] != 0) {
      accuracies_[i] /= static_cast<float>(class_number_counts_[i]);
    }
  }
  
  accuracy_ /= static_cast<float>(image_count_);
  return accuracy_;
}

std::vector<Image> Validator::GetImages() const {
  return images_;
}

std::vector<float> Validator::GetAccuracies() const {
  return accuracies_;
}

float Validator::GetAccuracy() const {
  return accuracy_;
}

} // namespace naivebayes