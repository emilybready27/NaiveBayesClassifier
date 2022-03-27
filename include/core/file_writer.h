#pragma once

#include <fstream>
#include "number_class.h"

namespace naivebayes {

class FileWriter {
 public:
  FileWriter() = default;
  
  FileWriter(std::ostream& output,
             const std::vector<NumberClass>& number_classes,
             const std::vector<float>& prior_probs,
             int total_image_count,
             int row_count,
             int column_count);
};

//template<class T>
//std::string ToString(const std::vector<T>& vector);

} // namespace naivebayes