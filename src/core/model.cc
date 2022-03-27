#include "core/model.h"
#include "core/file_writer.h"
#include <numeric>

namespace naivebayes {

Model::Model() {
}

void Model::Train() {
  ComputePriorProbs();
  ComputeFeatureProbsShaded();
}

std::istream& operator>> (std::istream& input, Model& model) {
  model.file_reader_ = FileReader(input);
  
  if (model.file_reader_.IsSaveFile()) {
    const FileReader::FauxModel& faux_model = model.file_reader_.GetFauxModel();
    model.ConstructSavedModel(faux_model);
  } else {
    std::vector<Image> images = model.file_reader_.GetData();
    model.ConstructNumberClasses(images);
  }
  
  return input;
}

std::ostream& operator<< (std::ostream& output, Model& model) {
  model.file_writer_ = FileWriter(output,
                                model.number_classes_,
                                model.prior_probs_,
                                model.total_image_count_,
                                model.row_count_,
                                model.column_count_);
  return output;
}

void Model::ConstructSavedModel(const FileReader::FauxModel& faux_model) {
  total_image_count_ = faux_model.total_image_count_;
  row_count_ = faux_model.row_count_;
  column_count_ = faux_model.column_count_;
  number_classes_ = faux_model.number_classes_;
  prior_probs_ = faux_model.prior_probs_;
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
  
  row_count_ = number_classes_[0].GetRowCount();
  column_count_ = number_classes_[0].GetColumnCount();
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
    class_number_counts.push_back(number_class.GetClassNumberCount());
  }
  return class_number_counts;
}

std::vector<float> Model::GetPriorProbs() const {
  return prior_probs_;
}

std::vector<std::vector<float>>
Model::GetFeatureProbsShaded(int class_number) const {
  return number_classes_[class_number].GetFeatureProbsShaded();
}

} // namespace naivebayes
