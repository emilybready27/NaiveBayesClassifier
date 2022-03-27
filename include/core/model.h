#pragma once

#include "file_reader.h"
#include "number_class.h"

namespace naivebayes {

class Model {
 public: 
  friend std::istream& operator>> (std::istream& in, Model& model);
  
  std::vector<std::vector<Image>> GetImages() const;
  
  std::vector<int> GetClassNumberCounts() const;
  
  std::vector<float> GetPriorProbs() const;
  
  std::vector<std::vector<float>> GetFeatureProbs() const;
  
 private:
  /**
   * Used to read the input file stream into the Model.
   */
  FileReader file_reader_;
  
  /**
   * Stores a list of the 10 different classes of numbers.
   */
  std::vector<NumberClass> number_classes_;
  
  const float kLaplace = 1.0;
  
  const int kNumberClasses = 10;
  
  int total_image_count_;
  
  std::vector<float> prior_probs_;
  
  std::vector<std::vector<float>> feature_probs_;
  
  void ConstructNumberClasses(const std::vector<Image>& images);
  
  void ComputePriorProbs();
};



} // namespace naivebayes