#pragma once

#include <vector>
#include "image.h"

namespace naivebayes {

class NumberClass {
 public: 
  NumberClass(int class_number);
  
  void AddImage(const Image& image);
  
  std::vector<Image> GetImages() const;
  
  void SetClassNumberCount(int count);
  
  int GetClassNumberCount() const;
  
  int GetClassNumber() const;
  
  void SetRowCount(int count);
  
  int GetRowCount() const;
  
  void SetColumnCount(int count);
  
  int GetColumnCount() const;
  
  void ComputeFeatureProbsShaded(float kLaplace);
  
  void ResetFeatureProbsShaded(float reset_value);
  
  void SetFeatureProbsShaded(const std::vector<std::vector<float>>& matrix);
  
  std::vector<std::vector<float>> GetFeatureProbsShaded() const;
  
 private:
  int class_number_;
  
  int class_number_count_;
  
  int row_count_;
  
  int column_count_;
  
  std::vector<Image> images_;
  
  std::vector<std::vector<float>> feature_probs_shaded_;
  
};

} // namespace naivebayes