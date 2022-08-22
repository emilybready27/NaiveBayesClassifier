#pragma once

#include <vector>
#include "image.h"

namespace naivebayes {

/**
 * Characterization of a number from 0 - 9 into its own class.
 */
class NumberClass {
 public: 
  /**
   * Constructs an empty NumberClass from its distinguishing class number
   * and the dimensions needed for a probability matrix.
   * @param class_number int
   * @param row_count int
   * @param column_count int
   */
  NumberClass(int class_number, int row_count, int column_count);
  
  /**
   * Inserts the given Image into the NumberClass.
   * @param image Image
   */
  void AddImage(const Image& image);
  
  /**
   * Fills the feature_probs_shaded_ matrix with the associated
   * feature probabilities in-place.
   * @param kLaplace float (smoothing constant)
   */
  void ComputeFeatureProbsShaded(float k_laplace);
  
  /**
   * Refills the feature_probs_shaded_ matrix uniformly with the given value.
   * @param reset_value float
   */
  void ResetFeatureProbsShaded(float reset_value);
  
  /**
   * Refills the feature_probs_shaded_ matrix with the given matrix.
   * @param matrix std::vector<std::vector<float>>
   */
  void SetFeatureProbsShaded(const std::vector<std::vector<float>>& matrix);
  
  /**
   * Getters and setters for other NumberClass state.
   */
  int GetClassNumber() const;
  void SetClassNumberCount(int count);
  int GetClassNumberCount() const;
  float GetFeatureProbsShaded(int row, int column) const;
  
 private:
  /**
   * Digit (0-9) the class represents.
   */
  int class_number_;
  
  /**
   * Number of Images with this particular class number.
   */
  int class_number_count_;
  
  /**
   * Number of rows in the Images.
   */
  int row_count_;
  
  /**
   * Number of columns in the Images.
   */
  int column_count_;
  
  /**
   * Matrix of the feature probabilities of shaded pixels given
   * that they belong to an Image with this particular class number.
   * Note that the feature probabilities of unshaded pixels is easily
   * derived as 1 - feature probabilities of shaded pixels.
   */
  std::vector<std::vector<float>> feature_probs_shaded_;
  
};

} // namespace naivebayes