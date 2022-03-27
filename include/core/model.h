#pragma once

#include "file_reader.h"
#include "number_class.h"

namespace naivebayes {

class Model {
 public: 
  friend std::istream& operator>> (std::istream& in, Model& model);
  
  std::vector<std::vector<Image>> GetImages() const;
  std::vector<int> GetClassNumberCounts() const;
  
 private:
  /**
   * Used to read the input file stream into the Model.
   */
  FileReader file_reader_;
  
  /**
   * Stores a list of the 10 different classes of numbers.
   */
  std::vector<NumberClass> number_classes_;
  
  void ConstructNumberClasses(const std::vector<Image>& images);
};



} // namespace naivebayes