#include "core/model.h"

namespace naivebayes {

Model::Model() {
}

std::istream& operator>> (std::istream& input, Model& model) {
  model.file_reader_ = FileReader(input);
  std::vector<Image> images = model.file_reader_.GetImages();
  
  return input;
}



} // namespace naivebayes
