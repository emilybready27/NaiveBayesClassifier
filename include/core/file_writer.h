#pragma once

#include <fstream>
#include "number_class.h"

namespace naivebayes {

class FileWriter {
 public:
  FileWriter() = default;
  
  FileWriter(std::ostream& output,
             const std::vector<NumberClass>& number_classes,
             int total_image_count,
             int row_count,
             int column_count);
};

} // namespace naivebayes