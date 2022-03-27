#include "core/model.h"
#include <numeric>

namespace naivebayes {

std::istream& operator>> (std::istream& input, Model& model) {
  model.file_reader_ = FileReader(input);
  std::vector<Image> images = model.file_reader_.GetImages();

  model.ConstructNumberClasses(images);
  
  model.ComputePriorProbs();
  //model.ComputeFeatureProbs();
  
  return input;
}

void Model::ConstructNumberClasses(const std::vector<Image>& images) {
  // initialize number classes
  for (int i = 0; i < kNumberClasses; i++) {
    number_classes_.emplace_back(i);
  }
  
  for (const Image& image : images) {
    int class_number = image.GetClassNumber();
    // add image to corresponding number class
    number_classes_[class_number].AddImage(image);
  }
}

void Model::ComputePriorProbs() {
  std::vector<int> class_number_counts = GetClassNumberCounts();
  total_image_count_ = std::accumulate(class_number_counts.begin(),
                                       class_number_counts.end(), 0);
  
  for (const int class_number_count : class_number_counts) {
    prior_probs_.push_back(((float) class_number_count + kLaplace)
                           / (total_image_count_ + kNumberClasses * kLaplace));
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
std::vector<float> Model::GetPriorProbs() const {
  return prior_probs_;
}
std::vector<std::vector<float>> Model::GetFeatureProbs() const {
  return feature_probs_;
}

} // namespace naivebayes
