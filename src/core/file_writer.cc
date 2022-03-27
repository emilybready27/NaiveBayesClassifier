#include "core/file_writer.h"
#include <iostream>
#include <vector>

namespace naivebayes {

FileWriter::FileWriter(std::ostream& output,
                       const std::vector<NumberClass>& number_classes,
                       const std::vector<float>& prior_probs,
                       float kLaplace,
                       int kNumberClasses,
                       int total_image_count,
                       int row_count,
                       int column_count) {
  output << "save" << std::endl << std::endl;
  
  output << kLaplace << std::endl;
  output << kNumberClasses << std::endl;
  output << total_image_count << std::endl;
  output << row_count << std::endl;
  output << column_count << std::endl << std::endl;
  
  for (NumberClass number_class : number_classes) {
    output << number_class.GetClassNumber() << std::endl;
    output << number_class.GetCount() << std::endl;
    
    if (number_class.GetCount() == 0) {
      output << std::endl;
      continue;
    }
    
    for (int i = 0; i < kNumberClasses; i++) {
      for (int j = 0; j < kNumberClasses; j++) {
        output << " " << number_class.GetFeatureProbsShaded()[i][j];
      }
      output << std::endl;
    }
    
    output << std::endl;
  }
}

//template<class T>
//std::string ToString(std::vector<T> vector) {
//  std::string str;
//  for (int i = 0; i < vector.size(); i++) {
//    str += std::to_string(vector[i]) + " ";
//  }
//  return str;
//}

} // namespace naivebayes