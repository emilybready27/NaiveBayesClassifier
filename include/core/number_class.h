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
  
  std::vector<std::vector<int>> GetShadedCounts() const;
  
 private:
  int class_number_;
  int class_number_count_;
  std::vector<Image> images_;
  std::vector<std::vector<int>> shaded_counts_;

  void ConstructShadedCounts(int number_rows, int number_columns);
  void UpdateShadedCounts(const Image& image);
};

} // namespace naivebayes