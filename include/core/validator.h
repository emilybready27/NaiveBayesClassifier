#pragma once

#include <vector>
#include "image.h"

namespace naivebayes {

/**
 * Class used to judge the accuracy of Image class number predictions
 * using Naive Bayes.
 */
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
  
  /**
   * Updates its internal state based on the comparison of these two numbers.
   * @param expected_class_number int
   * @param actual_class_number int
   */
  void Compare(int expected_class_number, int actual_class_number);
  
  /**
   * Calculates scaled ratios for correct number of predictions to
   * total number of predictions, both between and within NumberClasses.
   * Returns the accuracy as a ratio between these two quantities.
   * @return float
   */
  float Validate();
  
  /**
   * Getters for Validator state.
   */
  const std::vector<Image>& GetImages() const;
  const std::vector<float>& GetAccuracies() const;
  float GetAccuracy() const;

 private:  
  /**
   * Vector of Images to validate.
   */
  std::vector<Image> images_;
  
  /**
   * Total number of images to validate.
   */
  int image_count_;
  
  /**
   * Vector of the number of images corresponding to each NumberClass.
   */
  std::vector<int> class_number_counts_;
  
  /**
   * Numerical estimate for the accuracy of the Model.
   */
  float accuracy_;
  
  /**
   * Vector of how accurate each NumberClass is.
   */
  std::vector<float> accuracies_;  
};

} // namespace naivebayes