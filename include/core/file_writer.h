#pragma once

#include <fstream>
#include "number_class.h"

namespace naivebayes {

/**
 * Builds the output of a Model.
 */
class FileWriter {
 public:
  /**
   * Default constructor.
   */
  FileWriter() = default;

  /**
   * Constructs the output of a Model given its state.
   * @param output std::ostream
   * @param k_laplace int
   * @param k_max_class_count int
   * @param total_class_count int
   * @param total_image_count int
   * @param row_count int
   * @param column_count int
   * @param class_number_counts std::vector<int>
   * @param number_classes std::vector<NumberClass>
   * @param prior_probs std::vector<float>
   */
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