#pragma once

#include "number_class.h"
#include "file_reader.h"
#include "file_writer.h"

namespace naivebayes {

class Model {
 public:
  Model();
  
  void Train();
  
  friend std::istream& operator>> (std::istream& in, Model& model);
  
  friend std::ostream& operator<< (std::ostream& out, Model& model);
  
  int GetTotalImageCount() const;
  
  std::vector<std::vector<Image>> GetImages() const;
  
  std::vector<int> GetClassNumberCounts() const;
  
  std::vector<float> GetPriorProbs() const;
  
  std::vector<std::vector<float>> GetFeatureProbsShaded(int class_number) const;
  
  
 private:
  /**
   * Used to read the input file stream into the Model.
   */
  FileReader file_reader_;
  
  /**
   * Used to write to an output file to save for later.
   */
  FileWriter file_writer_;
  
  const float kLaplace = 1.0;
  
  const int kClassCount = 10;
  
  int total_image_count_;
  
  int row_count_;
  
  int column_count_;
  
  /**
   * Stores a list of the 10 different classes of numbers.
   */
  std::vector<NumberClass> number_classes_;
  
  std::vector<float> prior_probs_;
  
  void ConstructSavedModel(const FileReader::FauxModel& faux_model);
  
  void ConstructNumberClasses(const std::vector<Image>& images);
  
  void ComputePriorProbs();
  
  void ComputeFeatureProbsShaded();
  
};



} // namespace naivebayes