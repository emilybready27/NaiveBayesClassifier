#include "core/model.h"

namespace naivebayes {

Model::Model() {
}

std::istream& operator>> (std::istream& input, Model& model) {
  model.file_reader_ = FileReader(input);
  std::vector<Image> images = model.file_reader_.GetImages();

  model.SortImagesByClassNumberCount(images);
  
  
  
  return input;
}

void Model::SortImagesByClassNumberCount(const std::vector<Image>& images) {
  // vector storing one vector of Images for each class number
  images_ = std::vector<std::vector<Image>>(10); // TODO: magic number
  // vector storing number of images in each class number
  class_number_counts = std::vector<int>(10); // TODO: magic number
  
  for (const Image& image : images) {
    int class_number = image.GetClassNumber();
    class_number_counts[class_number]++;
    images_[class_number].push_back(image);
  }
  
}

} // namespace naivebayes
