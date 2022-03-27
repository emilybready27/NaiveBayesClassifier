#include "core/model.h"
#include "core/file_writer.h"
#include <numeric>

namespace naivebayes {

Model::Model() {
}

std::istream& operator>> (std::istream& input, Model& model) {
  model.file_reader_ = FileReader(input);
  std::vector<Image> images = model.file_reader_.GetImages();

  model.ConstructNumberClasses(images);
  
  model.ComputePriorProbs();
  model.ComputeFeatureProbsShaded();
  
  return input;
}

std::ostream& operator<< (std::ostream& output, Model& model) {
//  model.file_writer_ = FileWriter(output, "save");
  return output;
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
  
  row_count_ = images[0].GetNumberRows();
  column_count_ = images[0].GetNumberColumns();
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

void Model::ComputeFeatureProbsShaded() {
  for (NumberClass& number_class : number_classes_) {
    number_class.ComputeFeatureProbsShaded(kLaplace);
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

std::vector<std::vector<float>>
Model::GetFeatureProbsShaded(int class_number) const {
  if (number_classes_[class_number].GetFeatureProbsShaded().empty()) {
    std::vector<float> row(column_count_, 0.0);
    return std::vector<std::vector<float>>(row_count_, row);
  }
  return number_classes_[class_number].GetFeatureProbsShaded();
}

} // namespace naivebayes
