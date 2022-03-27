#include "core/model.h"
#include <numeric>

namespace naivebayes {

std::istream& operator>> (std::istream& input, Model& model) {
  model.file_reader_ = FileReader(input);
  std::vector<Image> images = model.file_reader_.GetImages();

  model.ConstructNumberClasses(images);
  
  model.ComputePriorProbs();
  model.ComputeFeatureProbs();
  
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
    float prob = (class_number_count + kLaplace)
                 / (total_image_count_ + (kNumberClasses * kLaplace));
    prior_probs_.push_back(prob);
  }
}

void Model::ComputeFeatureProbs() {
  for (const NumberClass& numberClass : number_classes_) {
    const std::vector<std::vector<int>> &shaded_counts =
        numberClass.GetShadedCounts();
    
    for (const auto & shaded_count_row : shaded_counts) {
      
      std::vector<float> feature_probs_1_row;
      std::vector<float> feature_probs_0_row;
      
      for (int shaded_count : shaded_count_row) {
        float prob_0 = (numberClass.GetCount() - shaded_count + kLaplace)
                       / (numberClass.GetCount() + (2 * kLaplace));
        feature_probs_0_row.push_back(prob_0);
        
        float prob_1 = (shaded_count + kLaplace)
                     / (numberClass.GetCount() + (2 * kLaplace));
        feature_probs_1_row.push_back(prob_1);
      }
      
      feature_probs_1_.emplace_back(feature_probs_1_row);
    }
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

std::vector<std::vector<float>> Model::GetFeatureProbs0() const {
  return feature_probs_0_;
}

std::vector<std::vector<float>> Model::GetFeatureProbs1() const {
  return feature_probs_1_;
}

} // namespace naivebayes
