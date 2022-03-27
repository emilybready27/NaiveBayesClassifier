#include "core/model.h"

namespace naivebayes {

std::istream& operator>> (std::istream& input, Model& model) {
  model.file_reader_ = FileReader(input);
  std::vector<Image> images = model.file_reader_.GetImages();

  model.ConstructNumberClasses(images);
  
  return input;
}

void Model::ConstructNumberClasses(const std::vector<Image>& images) {
  // initialize number classes
  for (size_t i = 0; i < 10; i++) { // TODO: magic number
    number_classes_.emplace_back(i);
  }
  
  for (const Image& image : images) {
    int class_number = image.GetClassNumber();
    // add image to corresponding number class
    number_classes_[class_number].AddImage(image);
  }
}

std::vector<std::vector<Image>> Model::GetImages() const {
  std::vector<std::vector<Image>> images;
  for (const NumberClass& number_class : number_classes_) {
    images.push_back(number_class.GetImages());
  }
  return images;
}

std::vector<int> Model::GetClassNumberCounts() const {
  std::vector<int> class_number_counts;
  for (const NumberClass& number_class : number_classes_) {
    class_number_counts.push_back(number_class.GetCount());
  }
  return class_number_counts;
}

} // namespace naivebayes
