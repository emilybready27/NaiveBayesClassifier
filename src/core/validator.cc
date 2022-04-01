#include "core/validator.h"

namespace naivebayes {

Validator::Validator(const std::vector<Image>& images,
                     int k_max_class_count) {
  images_ = images;
  accuracies_ = std::vector<>(k_max_class_count, 0);
}

void Validator::Validate() {
}

} // namespace naivebayes