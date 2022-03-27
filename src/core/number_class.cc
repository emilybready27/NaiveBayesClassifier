#include "core/number_class.h"

namespace naivebayes {

NumberClass::NumberClass(int class_number) {
  class_number_ = class_number;
  class_number_count_ = 0;
}

void NumberClass::AddImage(const Image& image) {
  images_.push_back(image);
  class_number_count_++;
}

std::vector<Image> NumberClass::GetImages() const {
  return images_;
}

int NumberClass::GetCount() const {
  return class_number_count_;
}
int NumberClass::GetClassNumber() const {
  return class_number_;
}

} // namespace naivebayes