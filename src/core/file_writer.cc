#include "core/file_writer.h"
#include <iostream>
#include <vector>

namespace naivebayes {

FileWriter::FileWriter(std::ostream& output,
                       float k_laplace,
                       int k_max_class_count,
                       int total_class_count,
                       int total_image_count,
                       int row_count,
                       int column_count,
                       const std::vector<int>& class_number_counts,
                       const std::vector<NumberClass>& number_classes,
                       const std::vector<float>& prior_probs) {
  // used for indication of a save file
  output << "save" << std::endl;
  
  output << k_laplace << std::endl;
  output << k_max_class_count << std::endl;
  output << total_class_count << std::endl;
  output << total_image_count << std::endl;
  output << row_count << std::endl;
  output << column_count << std::endl;
  
  for (const int count : class_number_counts) {
    output << count << " ";
  }
  output << std::endl;
  
  for (const float prob : prior_probs) {
    output << prob << " ";
  }
  output << std::endl;
  
  for (const NumberClass& number_class : number_classes) {
    output << number_class.GetClassNumber() << std::endl;
    output << number_class.GetClassNumberCount() << std::endl;
    
    // save only feature probabilities of shaded because the feature
    // probabilities of unshaded are easy to derive, save space
    for (int i = 0; i < row_count; i++) {
      for (int j = 0; j < column_count; j++) {
        output << number_class.GetFeatureProbsShaded()[i][j] << " ";
      }
      output << std::endl;
    }
  }
}

} // namespace naivebayes