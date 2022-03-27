#pragma once

#include <vector>
#include "image.h"

namespace naivebayes {

class NumberClass {
 public: 
  NumberClass(int class_number);
  
  void AddImage(const Image& image);
  
  std::vector<Image> GetImages() const;
  
  int GetCount() const;
  
  int GetClassNumber() const;
  
  int GetRowCount() const;
  
  int GetColumnCount() const;
  
  void ComputeFeatureProbsShaded(float kLaplace);
  
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