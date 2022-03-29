#pragma once

#include <fstream>
#include "number_class.h"

namespace naivebayes {

class FileWriter {
 public:
  FileWriter() = default;

  FileWriter(std::ostream& output,
             float k_laplace,
             int k_max_class_count,
             int total_class_count,
             int total_image_count,
             int row_count,
             int column_count,
             const std::vector<int>& class_number_counts,
             const std::vector<NumberClass>& number_classes,
             const std::vector<float>& prior_probs);
};

} // namespace naivebayes