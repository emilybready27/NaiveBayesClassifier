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
  
 private:
  int class_number_;
  int class_number_count_;
  std::vector<Image> images_;
  std::vector<std::vector<int>> shaded_counts_;
  
};

} // namespace naivebayes