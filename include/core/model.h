#pragma once

#include "file_reader.h"

namespace naivebayes {

class Model {
 public: 
  Model();
  
  friend std::istream& operator>> (std::istream& in, Model& model);
  
 private:
  FileReader file_reader_;
  std::vector<std::vector<Image>> images_;
  std::vector<int> class_number_counts;
  
  void SortImagesByClassNumberCount(const std::vector<Image>& images);
  
};



} // namespace naivebayes