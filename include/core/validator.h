#pragma once

#include <vector>
#include "image.h"

namespace naivebayes {

class Validator {
 public:
  /**
   * Default constructor.
   */
  Validator() = default; 
  
  /**
   * Constructs a Validator to test the calling Model's accuracy.
   * @param images std::vector<Image>
   * @param k_max_class_count int
   */
  Validator(const std::vector<Image>& images, int k_max_class_count);
  
  void Validate();

 private:
  /**
   * Vector of how accurate each NumberClass is.
   */
  std::vector<float> accuracies_;
  
  /**
   * Vector of Images to validate.
   */
  std::vector<Image> images_;
};

} // namespace naivebayes