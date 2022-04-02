#include "core/validator.h"
#include <numeric>

namespace naivebayes {

Validator::Validator(const std::vector<Image>& images,
                     int k_max_class_count) {
  images_ = images;
  accuracies_ = std::vector<float>(k_max_class_count, 0.0);
  accuracy_ = 0.0;
  
  class_number_counts_ = std::vector<int>(k_max_class_count, 0);
  for (const Image& image : images_) {
    int class_number = image.GetClassNumber();
    expected_class_numbers_.push_back(class_number);
    class_number_counts_[class_number]++;
  }
}
void Validator::AddPrediction(int actual_class_number) {
  actual_class_numbers_.push_back(actual_class_number);
}

float Validator::Validate() {
  for (size_t i = 0; i < expected_class_numbers_.size(); i++) {
    int delta = expected_class_numbers_[i] - actual_class_numbers_[i];
    
    // increment number of correct predictions
    if (delta == 0) {
      accuracies_[expected_class_numbers_[i]] += 1;
      accuracy_ += 1;
    }
  }
  
  // scale each frequency to get an accuracy estimate
  for (size_t i = 0; i < accuracies_.size(); i++) {
    if (class_number_counts_[i] != 0) {
      accuracies_[i] /= static_cast<float>(class_number_counts_[i]);
    }
  }
  
  int image_count = std::accumulate(class_number_counts_.begin(),
                                    class_number_counts_.end(), 0);
  accuracy_ /= static_cast<float>(image_count);
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